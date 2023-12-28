#include <stdlib.h>

#define func struct function_f

struct function_f {
    size_t size;
    double* coefficient;
    double* exp;
};

void    func_print(func* f);
void    func_print_raw(func* f);
func    func_get(char* str);
double  get_y(func* f, double x);
void    func_free(func* f);
