#include "gwan.h"
#include <string.h>
#include <stdio.h>
#include <malloc.h>

int main(int argc, char *argv[])
{
  if(argc != 1) return 400;

  xbuf_t *reply = get_reply(argv);
  char *filepath = (char *)malloc(256)
     , *wwwpath = (char *)get_env(argv, WWW_ROOT)
     , *template_path, *image_url;

  sprintf(filepath, "%s/uploads/%s", wwwpath, argv[0]);

  if(fopen(filepath, "r") == NULL) return 404;

  template_path = malloc(256);
  image_url = malloc(30);

  sprintf(template_path, "%s/color_thief.html", wwwpath);
  sprintf(image_url, "/uploads/%s", argv[0]);

  xbuf_frfile(reply, template_path);
  xbuf_repl(reply, "<!--image_url-->", image_url);

  free(template_path); template_path = NULL;
  free(image_url);     image_url = NULL;
  free(filepath);      filepath = NULL;

  return 200;
}
