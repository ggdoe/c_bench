#include <time.h>
#include <math.h>

/*  simple benchmark header only

-- USAGE : 
    START_BENCH : start the timer
    LOG_BENCH   : log the time
    PRINT_BENCH : print mean and std
    PRINT_BENCH_PERIOD(t) : print every 't' iterations

-- CONFIG 
    BENCH_LOG_SIZE  : set the log size (default : 128)
    BENCH_PRECISION : set the time precision : s, ms, µs, ns (default : ms)
    BENCH_PRINT_FORMAT : printf format for time (default : "%9.4lf")
    BENCH_INIT : init variable
    BENCH_NO_AUTO_INIT : disable init global variable

-- DEPENDENCIES
    math.h : sqrt()
    time.h : clock_gettime()
*/

#ifndef BENCH_LOG_SIZE
#define BENCH_LOG_SIZE 128
#endif
#ifndef BENCH_PRECISION
#define BENCH_PRECISION ms
#endif
#ifndef BENCH_PRINT_FORMAT
#define BENCH_PRINT_FORMAT "%9.4lf"
#endif

#define BENCH_CAT_HELPER(x, y) x##y
#define BENCH_CAT(x, y) BENCH_CAT_HELPER(x, y)
#define BENCH_STR_HELPER(x) #x
#define BENCH_STR(x) BENCH_STR_HELPER(x)
#define BENCH_PREC__ BENCH_CAT(BENCH_, BENCH_PRECISION)
#define BENCH_s  1.
#define BENCH_ms 1e3
#define BENCH_µs 1e6
#define BENCH_ns 1e9
#define BENCH_us BENCH_µs

#define BENCH_INIT  uint64_t bench_itetation = 0;           \
                    double bench_times[BENCH_LOG_SIZE];     \
                    struct timespec bench_start, bench_end;

#define START_BENCH clock_gettime(CLOCK_MONOTONIC_RAW, &bench_start);

#define LOG_BENCH   clock_gettime(CLOCK_MONOTONIC_RAW, &bench_end);                        \
                    double sec = (double)(bench_end.tv_sec  - bench_start.tv_sec)          \
                               + (double)(bench_end.tv_nsec - bench_start.tv_nsec) * 1e-9; \
                    bench_times[bench_itetation % BENCH_LOG_SIZE] = sec * BENCH_PREC__;    \
                    bench_itetation++;

#define PRINT_BENCH {                                                            \
                        double mean = 0.;                                        \
                        double std = 0.;                                         \
                        for(int i = 0; i < BENCH_LOG_SIZE; i++){                 \
                            mean += bench_times[i];                              \
                            std  += bench_times[i] * bench_times[i];             \
                        }                                                        \
                        mean /= BENCH_LOG_SIZE;                                  \
                        std /= BENCH_LOG_SIZE;                                   \
                        std = sqrt(std - mean*mean);                             \
                        printf("bench time : " BENCH_PRINT_FORMAT                \
                               " " BENCH_STR(BENCH_PRECISION)                    \
                               " (± "BENCH_PRINT_FORMAT")\t- iteration : %lu\n", \
                               mean, std, bench_itetation);                      \
                    }

#define PRINT_BENCH_PERIOD(t) if(bench_itetation % t == 0) PRINT_BENCH

#ifndef BENCH_NO_AUTO_INIT
    BENCH_INIT
#endif
