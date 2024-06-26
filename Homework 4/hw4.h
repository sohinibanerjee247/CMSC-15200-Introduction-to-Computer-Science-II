/* struct measurement: holds value, units, and exponent */
struct measurement {
    double value;
    char* units;
    unsigned int exponent;
};


/* struct conversion: holds from/to units and factor */
struct conversion {
    char *from, *to;
    double mult_by;
};


/* flip_case: returns string with capitalization of each letter flipped */
char* flip_case(char* s);


/* matches: returns pattern matches in larger string */
char** matches(char* s, char* pat, unsigned int* nmatches);


/* concat_strings: merges strings together with specified delimeter */
char* concat_strings(char** strings, unsigned int num_strings, char delim);


/* add_measurement: adds measurements and returns new measurement */
struct measurement add_measurements(struct measurement m1,
                                    struct measurement m2);


/* scale_measurement: scales a measurement and returns new measurement */
struct measurement scale_measurement(struct measurement m, double lambda);


/* multiply_measurements: multiplies measurements and returns new measurement */
struct measurement multiply_measurements(struct measurement m1,
        struct measurement m2);


/* measurement_tos: returns measurement in specified string format */
char* measurement_tos(struct measurement m);


/* convert_units: converts measurement and returns new measurement */
struct measurement convert_units(struct conversion* conversions,
                                 unsigned int n_conversions,
                                 struct measurement m,
                                 char* to);