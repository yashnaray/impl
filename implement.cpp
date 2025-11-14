#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <functional>
#include <bits.h>

struct Seed {
    bool s0;
    unsigned int S0;
};


bool h(unsigned int i) {
    bool result = 0;
    for (int j = 0; j < 8; j += 2) {
        result ^= ((i >> j) & 1) & ((i >> (j + 1)) & 1);
    }
    return result;
}

bool dot_product(unsigned int s_vec, unsigned int i) {
    unsigned int val = s_vec & i;
    int count = 0;
    for (int j = 0; j < 32; j++) {
        if ((val >> j) & 1) {
            count++;
        }
    }
    return count % 2 != 0;
}

bool f(const Seed& s, unsigned int i) {
    return s.s0 ^ dot_product(s.S0, i) ^ h(i);
}

int xi(const Seed& s, unsigned int i) {
    return f(s, i) ? -1 : 1;
}

int count_zero_pairs(unsigned int n) {
    int count = 0;
    for (int i = 0; i < 7; ++i) {
        if (!((n >> i) & 1) && !((n >> (i + 1)) & 1)) {
            count++;
        }
    }
    return count;
}

std::vector<std::pair<int, int>> get_dyadic_cover(int a, int b) {
    std::vector<std::pair<int, int>> cover;
    int current = a;
    while (current <= b) {
        int k = 0;
        if (current > 0) {
            k = floor(log2(current));
        }
        
        int size = 1;
        if (current == 0) {
            size = pow(2, floor(log2(b - current + 1)));
        } else {
            while ((current % (size * 2)) == 0 && current + (size*2) <= b+1) {
                size *= 2;
            }
        }
        
        cover.push_back({current, current + size});
        current += size;
    }
    return cover;
}


int H3Interval(int alpha, int beta, const Seed& s) {
    int num_zero = 1;

    std::vector<std::pair<int, int>> cover = get_dyadic_cover(alpha, beta);

    long long total_sum = 0;

    for (const auto& interval : cover) {
        int start = interval.first;
        int end = interval.second;
        int size = end - start;
        int j = (size > 0) ? log2(size) : 0;

        double magnitude = pow(2, (double)j / 2.0);
        int sign = (j > 0) ? -1 : 1;
        if (num_zero % 2 != 0 && j > 0) {
             sign = -1;
        } else if (j > 0) {
             sign = 1;
        } else {
             sign = 1;
        }


        long long term = sign * magnitude * xi(s, start);
        total_sum += term;
    }

    return total_sum;
}

int main() {

    return 0;
}
