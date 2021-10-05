#include <stdlib.h>
#include "diurna.h"

s_diurna_context *gl_diurna_ctx_handle = NULL;

int diurna_initialize(void) {
    gl_diurna_ctx_handle = malloc(sizeof(struct s_diurna_context));

    return (0);
}
