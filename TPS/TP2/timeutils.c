#define _XOPEN_SOURCE

#include "timeutils.h"

#define TIME_FORMAT "%FT%T%z"

time_t iso8601_to_time(const char* iso8601) {
    struct tm bktime = { 0 };
    strptime(iso8601, TIME_FORMAT, &bktime);
    return mktime(&bktime);
}
