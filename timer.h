//
// Created by zumbi on 30/04/17.
//

#ifndef TRABALHOAED_TIMER_H
#define TRABALHOAED_TIMER_H
#include <sys/time.h>

/* The argument now should be a double (not a pointer to a double) */
#define GET_TIME(now) { \
   struct timeval t; \
   gettimeofday(&t, NULL); \
   now = t.tv_sec + t.tv_usec/1000000.0; \
}
#endif //TRABALHOAED_TIMER_H
