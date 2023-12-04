#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


int64_t gcd(int64_t a, int64_t b){
    if (b == 0) {
        return a;
    }
    return gcd(b, a%b);
}

int64_t bin_pow(int64_t base, int64_t p) {
    int64_t res = 1;
    while (p) {
        if (p & 1) {
            res = (res * base);
        }
        base = (base * base);
        p /= 2;
    }
    return res;
}

int64_t bin_pow_modulo(int64_t base, int64_t p, int64_t mod) {
    int64_t res = 1;
    while (p) {
        if (p & 1) {
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        p /= 2;
    }
    return res;
}
#define FERMA_ITERATIONS 100
bool ferma(int64_t x){
    if (x == 2) {
        return true;
    }
    for (int i = 0; i < FERMA_ITERATIONS; i++) {
        int64_t a = (rand() % (x - 2)) + 2; // Pick a random numver [2..n-2]
        if (gcd(a, x) != 1) {
            return false;
        }
        if (bin_pow_modulo(a, x - 1, x) != 1) {
            return false;
        }
    }
    return true;
}

bool is_prime_naive(int64_t x) {
    for (int64_t i = 2; i < x; ++i) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

// need to call free
bool* sieve_of_eratosthenes(int64_t size) {
    bool* sieve = (bool*)malloc(size * sizeof(bool));
    for (int64_t i = 0; i < size; ++i) {
        sieve[i] = false;
    }
    sieve[1] = true;
    for (int64_t i = 2; i < size; ++i) {
        if (!sieve[i]) {
            for (int64_t j = 2 * i; j < size; j += i) {
                sieve[j] = true;
            }
        }
    }
    return sieve;
}

bool is_prime_sqrt(int64_t x) {
    for (int64_t i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

#define N_ITERATIONS 10000
#define NUMBER_LIMITS 100000
int main()
{
    srand(time(NULL));
    clock_t t;
    double owerall_time_taken = 0;
    printf("Started naive prime checker\n");
    int64_t check_values[N_ITERATIONS];
    for (int i = 0; i  < N_ITERATIONS; ++i) {
        check_values[i] = rand() % NUMBER_LIMITS;
    }
    for (int i = 0; i < N_ITERATIONS; ++i) {
        int64_t value = check_values[i]; // this value we will check in Prime test
        t = clock(); // hi-res clock counter
        is_prime_naive(value);
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        owerall_time_taken += time_taken;
    }
    printf("%d iterations, executed in %f seconds\n", N_ITERATIONS, owerall_time_taken);
    printf("Started sqrt prime checker\n");
    owerall_time_taken = 0;
    for (int i = 0; i < N_ITERATIONS; ++i) {
        int64_t value = check_values[i]; // this value we will check in Prime test
        t = clock(); // hi-res clock counter
        is_prime_sqrt(value);
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        owerall_time_taken += time_taken;
    }
    printf("%d iterations, executed in %f seconds\n", N_ITERATIONS, owerall_time_taken);
    printf("Started ferma prime checker\n");
    owerall_time_taken = 0;
    for (int i = 0; i < N_ITERATIONS; ++i) {
        int64_t value = check_values[i]; // this value we will check in Prime test
        t = clock(); // hi-res clock counter
        ferma(value);
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        owerall_time_taken += time_taken;
    }
    printf("%d iterations, executed in %f seconds\n", N_ITERATIONS, owerall_time_taken);
    printf("Lets increase number limits\nStarted sqrt prime checker\n");
    for (int i = 0; i  < N_ITERATIONS; ++i) {
        check_values[i] = (RAND_MAX * (int64_t)rand() + (int64_t)rand()) % ((int64_t)NUMBER_LIMITS * NUMBER_LIMITS * NUMBER_LIMITS);
    }
    owerall_time_taken = 0;
    for (int i = 0; i < N_ITERATIONS; ++i) {
        int64_t value = check_values[i]; // this value we will check in Prime test
        t = clock(); // hi-res clock counter
        is_prime_sqrt(value);
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        owerall_time_taken += time_taken;
    }
    printf("%d iterations, executed in %f seconds\n", N_ITERATIONS, owerall_time_taken);
    printf("Started ferma prime checker\n");
    owerall_time_taken = 0;
    for (int i = 0; i < N_ITERATIONS; ++i) {
        int64_t value = check_values[i]; // this value we will check in Prime test
        t = clock(); // hi-res clock counter
        ferma(value);
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        owerall_time_taken += time_taken;
    }
    printf("%d iterations, executed in %f seconds\n", N_ITERATIONS, owerall_time_taken);
}

