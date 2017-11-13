#ifndef TIME_H
#define TIME_H

#define _XOPEN_SOURCE

#include <time.h>

#define TIME_FORMAT "%FT%T%z"

/*
    Dada una cadena en formato ISO-8601 devuelve una variable de tipo time_t
    que representa un instante en el tiempo.
*/
time_t iso8601_to_time(const char* iso8601);

#endif
