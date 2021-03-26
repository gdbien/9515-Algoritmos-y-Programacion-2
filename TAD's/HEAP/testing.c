#include "testing.h"
#include <stdio.h>

#define ANSI_COLOR_LGH_RED     "\x1b[1m\x1b[31m"
#define ANSI_COLOR_LGH_GREEN   "\x1b[1m\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

static int _failure_count;

void real_print_test(const char* mensaje, bool ok,
		     const char* file, int line, const char* failed_expr) {
    if (ok) {
			printf("%s..." ANSI_COLOR_LGH_GREEN "OK\n", mensaje);
    } else {
			printf("%s:" ANSI_COLOR_LGH_RED "ERROR\n"  "%s:%d: %s\n",mensaje, file, line, failed_expr);
    }
		printf(ANSI_COLOR_RESET);
    fflush(stdout);
    _failure_count += !ok;
}

int failure_count() {
    return _failure_count;
}
