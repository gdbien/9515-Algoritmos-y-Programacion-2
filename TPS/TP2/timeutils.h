#ifndef TIMEUTILS_H
#define TIMEUTILS_H

#include <time.h>

/*
*  Dada una cadena en formato ISO-8601 devuelve una variable de tipo time_t
*  que representa un instante en el tiempo.
*/
time_t iso8601_to_time(const char* iso8601);

#endif
