#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hw4.h"

/* print_string_array: prints string array with commas */
void print_string_array(char** s, unsigned int len) {
    if (len >= 1) {
        for (unsigned int i = 0; i < len - 1; i++) {
            printf("%s, ", s[i]);
        }
        printf("%s", s[len - 1]);
    }
    printf("\n");
}


/* free_string_array: frees memory for each string in array */
void free_string_array(char** s, unsigned int len) {
    for (unsigned int i = 0; i < len; i++) {
        free(s[i]);
    }
    free(s);
}


/* print_measurement: prints measurement with proper format */
void print_measurement(struct measurement m) {
    printf("%lf %s^%u\n", m.value, m.units, m.exponent);
}


/* flip_case_print_free: print/free for flip_case */
void flip_case_print_free(char* s, char* expect, char* res) {
    printf("string: %s\n", s);
    printf("expect: %s\n", expect);
    printf("result: %s\n", res);
    printf("\n");
    free(res);
}


/* evidence_flip_case: test flip_case */
void evidence_flip_case() {
    printf("*** testing flip_case\n");

    char* s1 = "Hello World";
    flip_case_print_free(s1, "hELLO, wORLD", flip_case(s1));

    char* s2 = "Abwy6734b53h4u5";
    flip_case_print_free(s2, "aBWY6734B53H4U5", flip_case(s2));

    char* s3 = "";
    flip_case_print_free(s3, "", flip_case(s3));
}


/* matches_print_free: print/free for matches */
void matches_print_free(char* s, char* pat, char* expect,
                        char** res, unsigned int nmatches) {
    printf("string: %s, pattern: %s\n", s, pat);
    printf("expect: %s\n", expect);
    printf("result: ");
    print_string_array(res, nmatches);
    printf("\n");
    free_string_array(res, nmatches);
}


/* evidence_matches: test matches */
void evidence_matches() {
    printf("*** testing matches\n");

    unsigned int nmatches;

    char* s1 = "the thing is there, then?";
    char* pat1 = "the";
    matches_print_free(s1, pat1, "the, the, the",
                       matches(s1, pat1, &nmatches), nmatches);

    char* s2 = "Abet a botanist to bet a bit";
    char* pat2 = "b?t";
    matches_print_free(s2, pat2, "bet, bot, bet, bit",
                       matches(s2, pat2, &nmatches), nmatches);

    char* s3 = "hello world";
    char* pat3 = "?";
    matches_print_free(s3, pat3, "h, e, l, l, o,  , w, o, r, l, d",
                       matches(s3, pat3, &nmatches), nmatches);

    char* s4 = "ththe";
    char* pat4 = "th?";
    matches_print_free(s4, pat4, "tht, the",
                       matches(s4, pat4, &nmatches), nmatches);

    char* s5 = "cat";
    char* pat5 = "cats";
    matches_print_free(s5, pat5, "",
                       matches(s5, pat5, &nmatches), nmatches);

    /*char* s6 = "dogs";
    char* pat6 = "";
    matches_print_free(s6, pat6, "ERROR - pattern must be non-zero length",
                       matches(s6, pat6, &nmatches), nmatches);*/

    char* s7 = "cats";
    char* pat7 = "cats";
    matches_print_free(s7, pat7, "cats",
                       matches(s7, pat7, &nmatches), nmatches);
}


/* concat_strings_print_free: print/free for concat_strings */
void concat_strings_print_free(char** strings, unsigned int num_strings,
                               char delim, char* res, char* expect) {
    printf("delim: %c, strings: ", delim);
    print_string_array(strings, num_strings);
    printf("expect: %s\n", expect);
    printf("result: %s\n", res);
    printf("\n");
    free(res);
}


/* evidence_concat_strings: test concat_strings */
void evidence_concat_strings() {
    printf("*** testing concat_strings\n");

    char* strings1[] = {"ABC", "DEF"};
    concat_strings_print_free(strings1, 2, '1',
                              concat_strings(strings1, 2, '1'), "ABC1DEF");

    char* strings2[] = {"10", "200", "3000"};
    concat_strings_print_free(strings2, 3, ' ',
                              concat_strings(strings2, 3, ' '), "10 200 3000");

    char* strings3[] = {"", "", ""};
    concat_strings_print_free(strings3, 3, '!',
                              concat_strings(strings3, 3, '!'), "!!");
}


/* add_mult_print_free: print/free for add/multiply_measurements */
void add_mult_print_free(struct measurement m1, struct measurement m2,
                         struct measurement res, char* expect) {
    printf("m1: ");
    print_measurement(m1);
    printf("m2: ");
    print_measurement(m2);
    printf("expect: %s\n", expect);
    printf("result: ");
    print_measurement(res);
    printf("\n");
    free(res.units);
}


/* evidence_add_measurements: test add_measurements */
void evidence_add_measurements() {
    printf("*** testing add_measurements\n");

    struct measurement m1 = {1, "mi", 1};
    struct measurement m2 = {2, "mi", 1};
    add_mult_print_free(m1, m2, add_measurements(m1, m2), "3 mi^1");

    /*struct measurement m3 = {3, "kg", 1};
    struct measurement m4 = {4, "lb", 1};
    add_mult_print_free(m3, m4, add_measurements(m3, m4),
                        "ERROR - units must match");*/
}


/* scale_print_free: print/free for scale_measurement/convert_units */
void scale_conv_print_free(struct measurement m, struct measurement res,
                           char* expect) {
    printf("m: ");
    print_measurement(m);
    printf("expect: %s\n", expect);
    printf("result: ");
    print_measurement(res);
    printf("\n");
    free(res.units);
}


/* evidence_scale_measurement: test scale_measurement */
void evidence_scale_measurement() {
    printf("*** testing scale_measurement\n");

    struct measurement m1 = {1, "mi", 1};
    scale_conv_print_free(m1, scale_measurement(m1, 2.5), "2.5 mi^1");

    struct measurement m2 = {0.5, "m", 2};
    scale_conv_print_free(m2, scale_measurement(m2, 0), "0 cm^2");
}


/* evidence_multiply_measurements: test multiply_measurements */
void evidence_multiply_measurements() {
    printf("*** testing multiply_measurements\n");

    struct measurement m1 = {2, "mi", 1};
    struct measurement m2 = {3.5, "mi", 2};
    add_mult_print_free(m1, m2, multiply_measurements(m1, m2), "7 mi^3");

    /*struct measurement m3 = {3, "kg", 1};
    struct measurement m4 = {4, "lb", 1};
    add_mult_print_free(m3, m4, multiply_measurements(m3, m4),
                        "ERROR - units must match");*/
}


/* tos_print_free: print/free for measurement_tos */
void tos_print_free(struct measurement m, char* res, char* expect) {
    printf("m: ");
    print_measurement(m);
    printf("expect: %s\n", expect);
    printf("result: %s\n", res);
    printf("\n");
    free(res);
}


/* evidence_measurement_tos: test measurement_tos */
void evidence_measurement_tos() {
    printf("*** testing measurement_tos\n");

    struct measurement m1 = {3.5, "mi", 2};
    tos_print_free(m1, measurement_tos(m1), "3.5 mi^2");

    struct measurement m2 = {0, "cm", 3};
    tos_print_free(m2, measurement_tos(m2), "0 cm^3");

}


/* evidence_convert_units: test convert_units */
void evidence_convert_units() {
    printf("*** testing convert_units\n");

    unsigned int n_conversions = 1;
    struct conversion* conversions = (struct conversion*)malloc(n_conversions *
                                     sizeof(struct conversion));
    conversions[0].from = "in";
    conversions[0].to = "cm";
    conversions[0].mult_by = 2.54;

    conversions[1].from = "gal";
    conversions[1].to = "L";
    conversions[1].mult_by = 3.78541;

    struct measurement m1 = {2, "in", 1};
    scale_conv_print_free(m1,
                          convert_units(conversions, n_conversions, m1, "cm"),
                          "5.08 cm^1");

    struct measurement m2 = {2, "in", 2};
    scale_conv_print_free(m2,
                          convert_units(conversions, n_conversions, m2, "cm"),
                          "12.9032 cm^2");

    struct measurement m3 = {3, "cm", 2};
    scale_conv_print_free(m3,
                          convert_units(conversions, n_conversions, m3, "in"),
                          "0.465001 in^2");

    /*struct measurement m4 = {4, "lb", 1};
    scale_conv_print_free(m4,
                          convert_units(conversions, n_conversions, m4, "kg"),
                          "ERROR - conversion not found");*/

    free(conversions);
}


/* main: run the evidence functions above */
int main(int argc, char *argv[]) {
    evidence_flip_case();
    evidence_matches();
    evidence_concat_strings();
    evidence_add_measurements();
    evidence_scale_measurement();
    evidence_multiply_measurements();
    evidence_measurement_tos();
    evidence_convert_units();
    return 0;
}