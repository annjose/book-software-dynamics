#include <stdio.h>
#include <stdint.h>
// #include <x86intrin.h>
#include <intrin.h>

static const int kIterations = 1000 * 1000 * 1000; // 1 billion iterations to account for lower resolution of cycle counter

int main()
{
    uint64_t cycleCountStart, cycleCountEnd;
    uint64_t sum = 0;

    cycleCountStart = __rdtsc();          // start cycle count
    for (int i = 0; i < kIterations; i++) // loop kIterations times
    {
        sum += 1; // do the operation we want to measure
    }
    cycleCountEnd = __rdtsc(); // stop cycle count

    uint64_t elapsedCycles = cycleCountEnd - cycleCountStart; // find the delta
    double cyclesPerIteration = (double) elapsedCycles / kIterations;       // cycle time as per the CPU cycle counter

    fprintf(stdout, "%d iterations, %llu cycles, %4.2f cycles per iteration \n", kIterations, elapsedCycles, cyclesPerIteration);

    // cycle time = (processor frequency * 10 to the power 9)
    // clock time = cycle time * number of cycles per iteration

    // On the Lenovo laptop with processor AMD Ryzen 7 with Radeon Graphics, 2 GHz 8 Core(s)
    double frequency = 2e9;     // 2 GHz or 2,000,000,000
    double cycleTimeSecs = 1 / frequency;
    double cycleTimeNanoSecs = cycleTimeSecs * 1e9;  // 1 second = 1 billion nano seconds

    double clockTime = cycleTimeNanoSecs * cyclesPerIteration;

    fprintf(stderr, "On AMD Ryzen 2GHz processor....\n");
    fprintf(stderr, "Cycle time = %4.9f sec (%4.1f nanosecs), clock time = %4.2f nsec", cycleTimeSecs, cycleTimeNanoSecs, clockTime);
}