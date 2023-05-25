# simple benchmark header only

## USAGE :
 - START_BENCH : start the timer
 - LOG_BENCH   : log the time
 - PRINT_BENCH : print mean and std
 - PRINT_BENCH_PERIOD(t) : print every 't' iterations

## CONFIG
 - BENCH_LOG_SIZE  : set the log size (default : 128)
 - BENCH_PRECISION : set the time precision : s, ms, µs, ns (default : ms)
 - BENCH_PRINT_FORMAT : printf format for time (default : "%9.4lf")
 - BENCH_INIT : init variable
 - BENCH_NO_AUTO_INIT : disable init global variable

## DEPENDENCIES
 - math.h : sqrt()
 - time.h : clock_gettime()
