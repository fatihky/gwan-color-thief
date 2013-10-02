// ============================================================================
// Modified entity.c
// ============================================================================

#include "gwan.h"
#include <string.h>
#include <stdio.h>
#include <malloc.h>

int main(int argc, char *argv[])
{
   xbuf_t *reply = (xbuf_t *)get_reply(argv)
        , *read_buf = (xbuf_t*)get_env(argv, READ_XBUF);
   char *entity   = (char*)get_env(argv, REQ_ENTITY)
      , *tmp , *file, *filename, *extention, *content_type;
   u32  cont_len  = (u32)  get_env(argv, CONTENT_LENGTH)
      , entity_offset = entity - read_buf->ptr
      , curr_entity_len = read_buf->len - entity_offset;

   if(curr_entity_len < cont_len)
   {
      xbuf_xcat(reply, "<br>Entity[%k] is missing %k unread bytes\n",
                cont_len, curr_entity_len);
      return 500;
   }

   tmp = strstr(entity, "filename=\"");
   filename = strstr(tmp, "\"\r\n");
     if(filename == NULL) return 400;
   filename = strndup(tmp + 10, (int)(filename - tmp - 10));
     if(!(filename[4])) return 400; // filename must contain least 5 chars. example: x.png
   extention = strchr(filename, '.');
     if(   ( extention == NULL )
        || ( strchr(&extention[1], '.') != NULL )
        || ( strchr(filename, '/') != NULL )
        || ( strchr(filename, '\\') != NULL )
        || ( strchr(filename, ':') != NULL )
       ) return 400;

   tmp = strstr(tmp, "Content-Type: ");
     if(strncmp(tmp + 14, "image/", 6) != 0) return 415; // 415: Unsupported Media Type
   content_type = file = strstr(tmp, "\r\n\r\n");
   content_type = strndup(tmp + 14, (int)(content_type - tmp -14));

   char *new_filename = malloc(256);
   char *wwwpath = (char*)get_env(argv, WWW_ROOT);
   u64 ms = getms();
   sprintf(new_filename, "%s/uploads/%llu%s", wwwpath, (unsigned long long)ms
                                            , extention);

   FILE *fp = fopen(new_filename, "wb");
   fwrite(file + 4, curr_entity_len, 1, fp);
   fflush(fp);
   fclose(fp);

   static char redir[] = "HTTP/1.1 302 Found\r\n"
      "Content-type:text/html\r\n"
      "Location: /?img/%llu%s\r\n\r\n"
      "<html><head><title>Redirect</title></head><body>"
      "Click <a href=\"?img/%llu%s\">here</a>.</body></html>";

   xbuf_xcat(get_reply(argv), redir, (unsigned long long)ms, extention
                                   , (unsigned long long)ms, extention);

   free(filename);     filename = NULL;
   free(new_filename); new_filename = NULL;
   free(content_type); content_type = NULL;

   return 302; // return an HTTP code (302:'Found')
}

// ============================================================================
// End of Source Code
// ============================================================================
