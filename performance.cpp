// vim:set sw=4 et:

#include "secretary.h"
#include <time.h>

struct timer {
    timer() {
        clock_gettime(CLOCK_REALTIME, &t1);
    }

    double elapsed() {
        clock_gettime(CLOCK_REALTIME, &t2);
        return (t2.tv_sec - t1.tv_sec) + 1e-9 * (t2.tv_nsec - t1.tv_nsec);
    }

    struct timespec t1;
    struct timespec t2;
};

template <typename T>
double measure_time(size_t n, size_t ops) {
    permutation<T> p(n);
    timer t;
    while (ops--) p.next();
    return t.elapsed();
}

int main() {
    for (size_t n = 2; n <= 20; ++n) {
        size_t ops = 100000000;
        double
        t = measure_time<int>(n, ops);
        std::cout << "type=int n=" << n << " ops=" << ops << " time=" << t << " s time/op=" << (1e9 * t / ops) << "ns" << std::endl;
        t = measure_time<char>(n, ops);
        std::cout << "type=char n=" << n << " ops=" << ops << " time=" << t << " s time/op=" << (1e9 * t / ops) << "ns" << std::endl;
        t = measure_time<long long>(n, ops);
        std::cout << "type=longlong n=" << n << " ops=" << ops << " time=" << t << " s time/op=" << (1e9 * t / ops) << "ns" << std::endl;
    }
    return 0;
}
