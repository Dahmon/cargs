#include "args.h"
#include <stdio.h>


int main(int argc, char *argv[]) {
  int print = 0, count = 0, dry = 0;
  char *save = NULL;

  arg_opt opts[] = {
      {BOOLEAN, 'p', NULL, &print, 0},
      {STRING, 's', "save", &save, 0},
      {INT, 'c', "count", &count, 1},
      {BOOLEAN, '\0', "dry-run", &dry, 0},
  };

  parse_args(argc, argv, opts);

  printf("Parsed args: print: %d, count: %d, dry: %d, save: %s\n", print, count,
         dry, save);
}

int parse_args(int argc, char *argv[], arg_opt *opts) { 
  return 0;
}
