#include <stdlib.h>
#include <stdio.h>

unsigned char tens_letters(unsigned char number) {
    int in_range, multiple_of_ten;
    switch (number) {
    case 10:
        return 3;
    case 0:
    case 50:
        return 4;
    case 20:
    case 30:
    case 40:
    case 60:
    case 90:
        return 5;
    case 70:
    case 80:
        return 6;
    default:
        in_range = number >= 0 && number <= 90;
        multiple_of_ten = number % 10 == 0;

        if (!in_range && multiple_of_ten) {
            fprintf(stderr, "tens_letters error: number = %hhu, "
                    "not in range[0, 90]\n", number);
        } else if (in_range && !multiple_of_ten) {
            fprintf(stderr,
                    "tens_letters error: number = %hhu, "
                    "not a multiple of 10\n", number);
        } else {
            fprintf(stderr,
                    "tens_letters error: number = %hhu, "
                    "not in range [0, 90] and not a multiple of 10\n", number);
        }
        exit(1);
    }
}


void common_divisors(unsigned int n, unsigned int m) {
    unsigned int max = n;
    if (m > n) {
        max = m;
    }

    printf("1");
    for (int divisor = 2; divisor <= max; divisor++) {
        if (n % divisor == 0 && m % divisor == 0) {
            printf(" %d", divisor);
        }
    }
    printf("\n");
}


unsigned int legal_keys(unsigned char depths, unsigned char macs) {
    unsigned int total_works = 0;
    for (int depth1 = 1; depth1 <= depths; depth1++) {
        for (int depth2 = 1; depth2 <= depths; depth2++) {
            for (int depth3 = 1; depth3 <= depths; depth3++) {
                for (int depth4 = 1; depth4 <= depths; depth4++) {
                    int works = 1;

                    works = works && (abs(depth1 - depth2) <= macs);
                    works = works && (abs(depth2 - depth3) <= macs);
                    works = works && (abs(depth3 - depth4) <= macs);

                    total_works += works;
                }
            }
        }
    }
    return total_works;
}


unsigned int periods_for_yield(double rate, double yield) {
    int neg_rate = rate < 0;
    int neg_yield = yield < 0;

    if (neg_rate || neg_yield || (rate == 0 && yield > 0)) {
        if (neg_rate && !neg_yield) {
            fprintf(stderr,
                    "periods_for_yield error: rate = %lf%% yield = %lf%%, "
                    "rate cannot be negative\n", rate, yield);
        } else if (!neg_rate && neg_yield) {
            fprintf(stderr,
                    "periods_for_yield error: rate = %lf%% yield = %lf%%, "
                    "yield cannot be negative\n", rate, yield);
        } else if (neg_rate && neg_yield) {
            fprintf(stderr,
                    "periods_for_yield error: rate = %lf%% yield = %lf%%, "
                    "rate and yield cannot be negative\n", rate, yield);
        } else {
            fprintf(stderr,
                    "periods_for_yield error: rate = %lf%% yield = %lf%%, "
                    "rate cannot be zero if yield is positive\n", rate, yield);
        }
        exit(1);
    }

    unsigned int period = 0;
    double initial_money = 1;
    double current_money = initial_money;
    double current_yield = 0;
    while (current_yield < yield) {
        current_money += rate * current_money;
        current_yield = (current_money - initial_money) / initial_money;
        period++;
    }
    return period;
}


void pattern(unsigned char side, unsigned char width, unsigned char height) {
    for (int section = 0; section < height; section++) {
        for (int row = 0; row < side; row++) {
            for (int space = 0; space < row; space++) {
                printf(" ");
            }

            for (int column = 0; column < width; column++) {
                printf("*");
                if (column < width - 1) {
                    for (int space = 0; space < side - 1; space++) {
                        printf(" ");
                    }
                }
            }

            printf("\n");
        }
    }
}
