#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sys/time.h>
#include <algorithm>
#include <iomanip>

using namespace std;

unsigned int checks;

int standard_binary_search(vector<int>& array, unsigned int array_size, int key) {
    int bot, mid, top;

    if (array_size == 0) {
        return -1;
    }

    bot = 0;
    top = array_size - 1;

    while (bot < top) {
        mid = top - (top - bot) / 2;
        ++checks;

        if (key < array[mid]) {
            top = mid - 1;
        } else {
            bot = mid;
        }
    }

    ++checks;

    if (key == array[top]) {
        return top;
    }
    return -1;
}

int boundless_binary_search(vector<int>& array, unsigned int array_size, int key) {
    unsigned int mid, bot;

    if (array_size == 0) {
        return -1;
    }

    bot = 0;
    mid = array_size;

    while (mid > 1) {
        ++checks;

        if (key >= array[bot + mid / 2]) {
            bot += mid++ / 2;
        }
        mid /= 2;
    }

    ++checks;

    if (key == array[bot]) {
        return bot;
    }

    return -1;
}

long long utime() {
    struct timeval now_time;
    gettimeofday(&now_time, NULL);
    return now_time.tv_sec * 1000000LL + now_time.tv_usec;
}

void execute(int (*algo_func)(vector<int>&, unsigned int, int), const char* algo_name, vector<int>& o_array, vector<int>& r_array, int max, int loop, int runs, int rnd, bool sequential) {
    long long stable = 0, value = 0, start, end, best = 0;
    unsigned int cnt, hit = 0, miss = 0;

    srand(rnd);

    for (int run = runs; run; --run) {
        checks = 0;
        hit = 0;
        miss = 0;

        if (sequential) {
            stable = 0;
            start = utime();

            for (cnt = 0; cnt < loop; cnt++) {
                value = algo_func(o_array, max, r_array[cnt]);
                stable += value;

                if (value >= 0) {
                    hit++;
                } else {
                    miss++;
                }
            }
        } else {
            start = utime();

            for (cnt = 0; cnt < loop; cnt++) {
                if (algo_func(o_array, max, r_array[cnt]) >= 0) {
                    hit++;
                } else {
                    miss++;
                }
            }
        }
        end = utime();

        if (best == 0 || end - start < best) {
            best = end - start;
        }
    }

    if (sequential) {
        cout << "| " << setw(30) << algo_name << " | " << setw(10) << max
             << " | " << setw(10) << hit << " | " << setw(10) << miss
             << " | " << setw(10) << checks << " | " << setw(10) << best / 1000000.0
             << " | " << setw(10) << stable << " |\n";
    } else {
        cout << "| " << setw(30) << algo_name << " | " << setw(10) << max
             << " | " << setw(10) << hit << " | " << setw(10) << miss
             << " | " << setw(10) << checks << " | " << setw(10) << best / 1000000.0 << " |\n";
    }
}

#define run(algo, o_array, r_array, max, loop, runs, rnd, sequential) execute(&algo, #algo, o_array, r_array, max, loop, runs, rnd, sequential)

int main(int argc, char** argv) {
    int max = 100000;
    int loop = 10000;
    int density = 10; // max * density should stay under 2 billion
    int runs = 1000;
    int rnd = time(nullptr);
    bool sequential = false;

    if (argc > 1) max = atoi(argv[1]);
    if (argc > 2) runs = atoi(argv[2]);
    if (argc > 3) loop = atoi(argv[3]);
    if (argc > 4) rnd = atoi(argv[4]);

    vector<int> o_array(max);
    vector<int> r_array(loop);

    if (static_cast<long long>(max) * static_cast<long long>(density) > 2000000000) {
        density = 2;
    }

    int val = 0;
    for (int cnt = 0; cnt < max; cnt++) {
        o_array[cnt] = (val += rand() % (density * 2));
    }

    int top = o_array[max - 1] + density;

    srand(rnd);
    for (int cnt = 0; cnt < loop; cnt++) {
        r_array[cnt] = rand() % top;
    }

    cout << "Benchmark: array size: " << max << ", runs: " << runs << ", repetitions: " << loop << ", seed: " << rnd << ", density: " << density << "\n\n";
    cout << "Even distribution with " << max << " 32-bit integers, random access\n\n";
    cout << "| " << setw(30) << "Name" << " | " << setw(10) << "Items"
         << " | " << setw(10) << "Hits" << " | " << setw(10) << "Misses"
         << " | " << setw(10) << "Checks" << " | " << setw(10) << "Time" << " |\n";
    cout << "| " << setw(30) << "----------" << " | " << setw(10) << "----------"
         << " | " << setw(10) << "----------" << " | " << setw(10) << "----------"
         << " | " << setw(10) << "----------" << " | " << setw(10) << "----------" << " |\n";

    run(standard_binary_search, o_array, r_array, max, loop, runs, rnd, sequential);
    run(boundless_binary_search, o_array, r_array, max, loop, runs, rnd, sequential);


    // uneven distribution
    for (int cnt = 0; cnt < max / 2; cnt++) {
        o_array[cnt] = cnt - cnt % 2;
    }
    top = o_array[max - 1] + 2;

    cout << "\n\nUneven distribution with " << max << " 32-bit integers, random access\n\n";
    cout << "| " << setw(30) << "Name" << " | " << setw(10) << "Items"
         << " | " << setw(10) << "Hits" << " | " << setw(10) << "Misses"
         << " | " << setw(10) << "Checks" << " | " << setw(10) << "Time" << " |\n";
    cout << "| " << setw(30) << "----------" << " | " << setw(10) << "----------"
         << " | " << setw(10) << "----------" << " | " << setw(10) << "----------"
         << " | " << setw(10) << "----------" << " | " << setw(10) << "----------" << " |\n";

    run(standard_binary_search, o_array, r_array, max, loop, runs, rnd, sequential);
    run(boundless_binary_search, o_array, r_array, max, loop, runs, rnd, sequential);

    return 0;
}
