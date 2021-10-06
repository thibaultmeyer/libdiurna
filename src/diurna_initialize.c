#include <stdlib.h>
#include <string.h>
#include "diurna.h"

s_diurna_context *gl_diurna_ctx_handle = NULL;

int diurna_initialize(const char* app_name) {
    if (gl_diurna_ctx_handle != NULL) {
        gl_diurna_ctx_handle = malloc(sizeof(struct s_diurna_context));
        gl_diurna_ctx_handle->app_name = strdup(app_name);
    }

    return (0);
}
