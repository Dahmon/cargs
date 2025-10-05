#include "../include/cargs.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  int print = 1, count = 0, dry = 0;
  const char *save = NULL;

  arg_opt opts[] = {
    { BOOLEAN, 'p', NULL, &print, 0 },
    { STRING, 's', "save", &save, 1 },
    { INT, 'c', "count", &count, 1 },
    { BOOLEAN, '\0', "dry-run", &dry, 0 },
    { END, '\0', NULL, NULL, 0 }
  };

  parse_args(argc, argv, opts);

  printf("Parsed args: print: %d, count: %d, dry: %d, save: %s\n", print, count,
         dry, save);
}
