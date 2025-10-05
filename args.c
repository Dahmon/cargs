#include "args.h"
#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]) {
  int print = 1, count = 0, dry = 0;
  // Immutable pointer to a mutable string
  const char *save = NULL;

  arg_opt opts[] = {
    { BOOLEAN, 'p', NULL, &print, 0 },
    { STRING, 's', "save", &save, 0 },
    { INT, 'c', "count", &count, 1 },
    { BOOLEAN, '\0', "dry-run", &dry, 0 },
    { END, '\0', NULL, NULL, 0 }
  };

  parse_args(argc, argv, opts);

  printf("Parsed args: print: %d, count: %d, dry: %d, save: %s\n", print, count,
         dry, save);
}


int is_alpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void parse_short_opt(args *args, arg_opt *opts) {
  char *arg = args->argv[args->pos];
  arg_opt *arg_opt = NULL;

  while (opts->type != END) {
    if (opts->arg_short == '\0' || opts->arg_short != arg[1]) {
      opts++;
      continue;
    }

    arg_opt = opts;
    opts++;
  }

  if (arg_opt == NULL || arg_opt) {
    printf("invalid short opt: %s\n", arg);
    return;
  }

  printf("valid short opt: %s\n", arg);
}

void parse_long_opt(args *args, arg_opt *opts) {
  char *arg = args->argv[args->pos];
  arg_opt *arg_opt = NULL;

  while (opts->type != END) {
    if (opts->arg_long == NULL || strcmp(opts->arg_long, arg + 2) != 0) {
      opts++;
      continue;
    }

    arg_opt = opts;
    opts++;
  }

  if (arg_opt == NULL) {
    printf("invalid long opt: %s\n", arg);
    return;
  }

  printf("valid long opt: %s\n", arg);
}

int parse_args(int argc, char *argv[], arg_opt *opts) {
  args args = { 0, argc - 1, argv + 1 };

  while (args.pos<args.argc) {
    const char *arg = args.argv[args.pos];

    if (arg[0] == '-' && arg[1] == '-')
      parse_long_opt(&args, opts);
    if (arg[0] == '-' && is_alpha(arg[1]))
      parse_short_opt(&args, opts);

    args.pos++;
  }


  return 0;
}
