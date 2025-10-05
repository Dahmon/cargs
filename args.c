#include "args.h"
#include <_string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

int is_alpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int is_opt(char *arg) {
  return arg[0] == '-' || arg[0] == '-' || arg[1] == '-';
}

void get_value(args *args, arg_opt *opt) {
  if (opt->value == NULL) return;

  int has_val = args->pos + 1 < args->argc;

  if (opt->type == BOOLEAN && !has_val && !opt->value_required) {
    *(int *)opt->value = 1;
    return;
  }

  if (opt->value_required && (!has_val || is_opt(args->argv[args->pos + 1]))) {
    printf("Missing required value for option: %s\n", args->argv[args->pos]);
    return;
  }

  if (!has_val) return;

  char *val = args->argv[args->pos + 1];
  char c = val[0];
  int len = strlen(val);

  if (has_val) {
    switch (opt->type) {
      case STRING:
        *(char **)opt->value = val;
        break;
      case INT:
        *(int *)opt->value = atoi(val);
        break;
      case BOOLEAN:
        if (len > 1) {
          printf("boolean value is too long: %s\n", val);
          return;
        }
        if (c == '1' || c == 'y' || c == 'Y')
          *(int *)opt->value = 1;
        else if (c == '0' || c == 'n' || c == 'N')
          *(int *)opt->value = 0;
        else {
          printf("invalid boolean value: %s\n", val);
          return;
        }
      default:
        break;
    }

    args->pos++;
  }
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

  if (arg_opt == NULL) return;
  get_value(args, arg_opt);
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

  if (arg_opt == NULL) return;
  get_value(args, arg_opt);
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
