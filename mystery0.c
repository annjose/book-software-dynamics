#include <stdio.h>
#include <stdint.h>
#include <x86intrin.h>

int main() {
    uint64_t cycleCountStart = _rdtsc();
    
    int s = 1;

    uint64_t cycleCountEnd = _rdtsc();

    int64_t elapsed = cycleCountEnd - cycleCountStart;
    
    printf("%lu cycles", elapsed);
}