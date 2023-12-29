#include "calculations.h"
#include "callfuncs.h"
#include <stdio.h>
#include <argp.h>

const char* argp_program_version = "calc 1.5.2";
static char doc[] = "Your program description.";
static char args_doc[] = "program-doc";
const char* argp_program_bug_address = "(please don't)";


static struct argp_option options[] = {
        { "pq", 'p', "p,q", 0,                  "Calculates PQ-Formula of given numbers"},
        { "fac", 'f', "n", 0,                   "Calculates faculty of given number n"},
        { "ncr", 'n', "n,k", 0,                 "Calculates n over k for given numbers n, k"},
        { "pdf", 129, "n,p,k", 0,               "calculates the binomial-pdf"},
        { "cdf", 130, "n,p,k", 0,               "calculates the binomial-cdf"},
        {"bisection", 'b',  "function", 0,      "bisection to determine Zero of a function"},
        {"param a", 'x',  "left limit", 0,               "left limit for bisection/gauss"},
        {"param b", 'y',  "right limit", 0,               "right limit for bisection/gauss"},


        {"base", 'B',  "BASE", 0,               "base of the output (default: 10)"},
        {"precision", 'P',  "PRECISION", 0,     "precision of the output (default: 10)"},
        { 0 }
};

struct arguments {
    int base;
    int precision;
    char* value;
    double limit1;
    double limit2;
    enum { HELP, PQ, FACULTY, NCR, BIN_PDF, BIN_CDF, BISECTION } action;
};

static error_t
parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;
    switch (key) {
        case 'p': arguments->action = PQ; arguments->value = arg; break;
        case 'f': arguments->action = FACULTY; arguments->value = arg; break;
        case 129: arguments->action = BIN_PDF; arguments->value = arg; break;
        case 130: arguments->action = BIN_CDF; arguments->value = arg; break;
        case 'n': arguments->action = NCR; arguments->value = arg; break;
        case 'b': arguments->action = BISECTION; arguments->value = arg; break;
        case 'x': arguments->action = BISECTION; arguments->limit1 = strtod(arg, NULL); break;
        case 'y': arguments->action = BISECTION; arguments->limit2 = strtod(arg, NULL); break;

        case 'B': arguments->base = (int) strtol(arg, NULL, 10); break;
        case 'P': arguments->precision = (int) strtol(arg, NULL, 10); break;

        case ARGP_KEY_ARG: return 0;
        default: return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc, 0, 0, 0 };

int
main(int argc, char* argv[]) {
    struct arguments arguments;

    arguments.action = HELP;
    arguments.base = 10;
    arguments.precision = 10;

    argp_parse(&argp, argc, argv, 0, 0, &arguments);
    init(10, 10);
    switch (arguments.action) {
        case HELP:
            break;
        case PQ:
            out_pq(arguments.value);
            break;
        case FACULTY:
            out_fac(arguments.value);
            break;
        case NCR:
            out_ncr(arguments.value);
            break;
        case BIN_PDF:
            out_bin_pdf(arguments.value);
            break;
        case BIN_CDF:
            out_bin_cdf(arguments.value);
            break;
        case BISECTION:
            out_bisection(arguments.value, arguments.limit1, arguments.limit2);
            break;
    }
    return 0;
}