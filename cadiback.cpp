// clang-format off

static const char * usage =

"usage: cadiback [ <option> ] [ <dimacs> ]\n"
"\n"
"where '<option>' is one of the following\n"
"\n"
"  -h       print this command line option summary\n"
"  -q       disable all messages\n"
"  -v       increase verbosity\n"
"\n"
"and '<dimacs>' is a SAT instances for which the backbones literals are\n"
"determined and then printed.\n"

;

// clang-format on

#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "cadical.hpp"

static int verbosity;
static const char *path;
static bool close_file;
static FILE *file;

static void die (const char *, ...) __attribute__ ((format (printf, 1, 2)));
static void msg (const char *, ...) __attribute__ ((format (printf, 1, 2)));

static void msg (const char *fmt, ...) {
  if (verbosity < 0)
    return;
  fputs ("c ", stdout);
  va_list ap;
  va_start (ap, fmt);
  vprintf (fmt, ap);
  va_end (ap);
  fputc ('\n', stdout);
  fflush (stdout);
}

static void die (const char *fmt, ...) {
  fputs ("cadiback: error: ", stderr);
  va_list ap;
  va_start (ap, fmt);
  vfprintf (stderr, fmt, ap);
  va_end (ap);
  fputc ('\n', stderr);
  exit (1);
}

static CaDiCaL::Solver *solver;

int main (int argc, char **argv) {
  msg ("CaDiCaL BackBone Analyzer CadiBack");
  for (int i = 1; i != argc; i++) {
    const char *arg = argv[i];
    if (!strcmp (arg, "-h")) {
      fputs (usage, stdout);
      exit (0);
    } else if (*arg == '-')
      die ("invalid option '%s' (try '-h')", arg);
    else if (path)
      die ("multiple file arguments '%s' and '%s'", path, arg);
    else
      path = arg;
  }
  if (!path)
    path = "<stdin>", file = stdin, assert (!close_file);
  else if (!(file = fopen (path, "r")))
    die ("can not read '%s'", path);
  else
    close_file = 1;
  solver = new CaDiCaL::Solver ();
  if (close_file)
    fclose (file);
  delete solver;
  return 0;
}
