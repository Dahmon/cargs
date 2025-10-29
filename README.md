# c args

A basic command line argument parser, it supports string, int, and boolean
values and ignores anything invalid. That's it.

This was created as a learning exercise, using [`argparse`](https://github.com/cofyc/argparse) as inspiration.

## Roadmap

- [x] Basic arguments parsing
- [ ] Help/usage messages
- [ ] Accept nameless ending argument
- [ ] Compound options (`-ab` instead of `-a -b`)
- [ ] Tests

## Example

```c
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
```
