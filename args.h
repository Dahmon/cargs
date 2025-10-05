#if !defined(C_ARGS_H)
#define C_ARGS_H

typedef enum {
  BOOLEAN,
  STRING,
  INT,
} opt_type;

typedef struct {
  opt_type type;
  char arg_short; // \0 for none
  char *arg_long; // NULL for none
  void *value;
  int value_required;
} arg_opt;

int parse_args(int argc, char *argv[], arg_opt *opts);

#endif
