# simple benchmark header only

## usage : 
 - `BENCH_START` : start the timer
 - `BENCH_LOG`   : log the time, increase iteration counter
 - `BENCH_MEAN(*m)` : get mean
 - `BENCH_MEAN_STD(*m,*s)` : get mean and stdev
 - `BENCH_LAST`  : get last logged time
 - `BENCH_PRINT` : print mean and stdev
 - `BENCH_PRINT_PERIOD(t)` : print every '*t*' iterations
 - `BENCH_PERIOD(t)` : evaluate to **true** '*t*' iterations
 - `BENCH_RESET` : reset iteration counter

*warning, mean and stdev are incorrect until the array is filled once.*

## config :
 - `BENCH_LOG_SIZE`  : set the log size (default : **128**)
 - `BENCH_PRECISION` : set the time precision : **s**, **ms**, **µs**, **ns** (default : **ms**)
 - `BENCH_PRINT_FORMAT` : printf format for time (default : "*%9.4lf*")
 - `BENCH_INIT` : init necessary variables
 - `BENCH_NO_AUTO_INIT` : disable init globals variables

## dependencies :
 - `math.h` : *sqrt()*, define `BENCH_NO_SQRT` to disable and get ***variance*** instead of ***stdev***, or define your own *sqrt* in `__BENCH_SQRT__`
 - `time.h` : *clock_gettime()*

### example :

```c
#define BENCH_LOG_SIZE 256
#define BENCH_PRECISION µs
#define BENCH_NO_AUTO_INIT
#include "bench.h"

void func()
{
    BENCH_INIT
    for(int i = 0; i < nb_repeat; i++){
        BENCH_START
        function_to_bench();
        BENCH_LOG
        BENCH_PRINT_PERIOD(16)
    }
    BENCH_PRINT
    printf("%lf\n", BENCH_LAST);

    double mean;
    BENCH_MEAN(&mean);
}
```
