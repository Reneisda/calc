#include "calculations.h"
#include "callfuncs.h"
#include <stdio.h>
#include <argp.h>

const char*argp_program_version = "calc 1.3";
static char doc[] = "Your program description.";
static char args_doc[] = "program-doc";
const char* argp_program_bug_address = "(please don't)";
static int pre_out, base;



static struct argp_option options[] = {
        { "pq", 128, "NUMBER 1", 0,          "Calculates PQ-Formula of given numbers p, q        [-p {p},{q}]"},
        { "fac", 'f', "NUMBER", 0,         "Calculates faculty of given number n               [-f {n}]"},
        { "ncr", 'n', 0, 0,         "Calculates n over k for given numbers n, k         [-n {n},{k} ]"},
        { "pdf", 129, 0, 0,  "Compare case insensitive instead of case sensitive."},
        { "cdf", 130, 0, 0,  "Compare case insensitive instead of case sensitive."},
        {"base", 'b',  "BASE", 0,      "base of the output (default: 10"},
        {"precision", 'p',  "PRECISION", 0,      "base of the output (default: 10"},
        { 0 }
};

struct arguments {
    int base;
    int precision;
    char* value;
    enum { HELP, PQ, FACULTY, NCR, BIN_PDF, BIN_CDF } action;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    uint8_t action_set = 0;
    struct arguments *arguments = state->input;
    switch (key) {
        case 'l': base = 10; break;
        case 128: arguments->action = PQ; arguments->value = arg; break;
        case 'f': arguments->action = FACULTY; arguments->value = arg; break;
        case 129: arguments->action = BIN_PDF; arguments->value = arg; break;
        case 130: arguments->action = BIN_CDF; arguments->value = arg; break;
        case 'n': arguments->action = NCR; arguments->value = arg; break;

        case 'b': arguments->base = (int) strtol(arg, NULL, 10); break;
        case 'p': arguments->precision = (int) strtol(arg, NULL, 10); break;

        case ARGP_KEY_ARG: return 0;
        default: return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc, 0, 0, 0 };

int
main(int argc, char* argv[]) {
    pre_out = 10;
    base = 10;
    struct arguments arguments;

    arguments.action = HELP;
    arguments.base = 10;
    arguments.precision = 10;

    argp_parse(&argp, argc, argv, 0, 0, &arguments);
    printf("Action: %s\n", arguments.action == PQ ? "PQ" : arguments.action == FACULTY ? "Fac": "HELP");
    printf("Base: %d\n", arguments.base);
    printf("Precision: %d\n", arguments.precision);

    init(10, 10);
    out_pq("5,4");
    return 0;
}