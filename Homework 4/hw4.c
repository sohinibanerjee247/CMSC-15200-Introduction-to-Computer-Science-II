#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "hw4.h"

/* calc_shift: returns difference between two chars */
unsigned char calc_shift(char a, char b) {
    return a - b;
}


char* flip_case(char* s) {
    unsigned int size = strlen(s);
    unsigned char shift = calc_shift('a', 'A');

    char* res = (char*)malloc((size + 1) * sizeof(char));
    for (unsigned int i = 0; i < size; i++) {
        if (s[i] >= 65 && s[i] <= 90) {
            res[i] = s[i] + shift;
        } else if (s[i] >= 97 && s[i] <= 122) {
            res[i] = s[i] - shift;
        } else {
            res[i] = s[i];
        }
    }
    res[size] = '\0';

    return res;
}


/* count_matches: returns number of pat matches in string */
unsigned int count_matches(unsigned int size_s, unsigned int size_p,
                           char* s, char* pat) {
    unsigned int total = 0;
    if (size_p <= size_s) {
        for (unsigned int i = 0; i <= size_s - size_p; i++) {
            int works = 1;
            for (unsigned int j = 0; j < size_p; j++) {
                if (s[i + j] != pat[j] && pat[j] != '?') {
                    works = 0;
                }
            }
            if (works) {
                total++;
            }
        }
    }
    return total;
}


char** matches(char* s, char* pat, unsigned int* nmatches) {
    unsigned int size_s = strlen(s);
    unsigned int size_p = strlen(pat);

    if (!size_p) {
        printf("matches ERROR - pattern must be non-zero length\n");
        exit(1);
    }

    unsigned int total = count_matches(size_s, size_p, s, pat);
    char** res = (char**)malloc(total * sizeof(char*));

    if (size_p <= size_s) {
        for (unsigned int i = 0; i < total; i++) {
            res[i] = (char*)malloc((size_p + 1) * sizeof(char));
        }

        unsigned int index = 0;
        for (unsigned int i = 0; i <= size_s - size_p; i++) {
            int works = 1;
            for (unsigned int j = 0; j < size_p; j++) {
                if (s[i + j] != pat[j] && pat[j] != '?') {
                    works = 0;
                }
            }
            if (works) {
                for (unsigned int j = 0; j < size_p; j++) {
                    res[index][j] = s[i + j];
                }
                res[index++][size_p] = '\0';
            }
        }
    }

    *nmatches = total;
    return res;
}


/* calc_total_size: calculates total characters across string array */
unsigned int calc_total_size(char** strings, unsigned int num_strings) {
    unsigned int total_size = 0;
    for (unsigned int i = 0; i < num_strings; i++) {
        total_size += strlen(strings[i]);
    }
    return total_size;
}


char* concat_strings(char** strings, unsigned int num_strings, char delim) {
    unsigned int total_size = calc_total_size(strings, num_strings);

    char* res = (char*)malloc((total_size + num_strings) * sizeof(char));
    unsigned int current = 0;
    for (unsigned int i = 0; i < num_strings; i++) {
        unsigned int temp_size = strlen(strings[i]);

        for (unsigned int j = 0; j < temp_size; j++) {
            res[current++] = strings[i][j];
        }
        if (i == num_strings - 1) {
            res[current++] = '\0';
        } else {
            res[current++] = delim;
        }
    }

    return res;
}


struct measurement add_measurements(struct measurement m1,
                                    struct measurement m2) {
    if (strcmp(m1.units, m2.units)) {
        fprintf(stderr, "add_measurements ERROR - units must match\n");
        exit(1);
    }

    if (m1.exponent != m2.exponent) {
        fprintf(stderr, "add_measurements ERROR - exponents must match\n");
        exit(1);
    }

    struct measurement res;
    res.value = m1.value + m2.value;
    res.units = strdup(m1.units);
    res.exponent = m1.exponent;
    return res;
}


struct measurement scale_measurement(struct measurement m, double lambda) {
    struct measurement res;
    res.value = m.value * lambda;
    res.units = strdup(m.units);
    res.exponent = m.exponent;
    return res;
}


struct measurement multiply_measurements(struct measurement m1,
        struct measurement m2) {
    if (strcmp(m1.units, m2.units)) {
        fprintf(stderr, "multiply_measurements ERROR - units must match\n");
        exit(1);
    }

    struct measurement res;
    res.value = m1.value * m2.value;
    res.units = strdup(m1.units);
    res.exponent = m1.exponent + m2.exponent;
    return res;
}


char* measurement_tos(struct measurement m) {
    char result[100];
    sprintf(result, "%lf %s^%u", m.value, m.units, m.exponent);
    return strdup(result);
}


struct measurement convert_units(struct conversion* conversions,
                                 unsigned int n_conversions,
                                 struct measurement m,
                                 char* to) {
    struct measurement res;
    res.units = strdup(to);
    res.exponent = m.exponent;

    int works = 0;
    for (unsigned int i = 0; i < n_conversions; i++) {
        if (!strcmp(conversions[i].from, m.units)
                && !strcmp(conversions[i].to, to)) {
            res.value = pow(pow(m.value, 1.0 / m.exponent)
                            * conversions[i].mult_by, m.exponent);
            works = 1;

        } else if (!strcmp(conversions[i].to, m.units)
                   && !strcmp(conversions[i].from, to)) {
            res.value = pow(pow(m.value, 1.0 / m.exponent)
                            / conversions[i].mult_by, m.exponent);
            works = 1;
        }
    }

    if (!works) {
        fprintf(stderr, "convert_units ERROR - %s conversion not found\n", to);
        exit(1);
    }

    return res;
}