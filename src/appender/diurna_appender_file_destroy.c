#include "diurna_internal.h"
#include <stdlib.h>

void diurna_appender_file_destroy(void *appender_ctx) {
    if (appender_ctx != NULL) {
        struct s_diurna_appender_file_ctx *ctx = appender_ctx;

        if (ctx->output_filename != NULL) {
            free(ctx->output_filename);
        }
        if (ctx->current_filename != NULL) {
            free(ctx->current_filename);
        }
        if (ctx->current_date != NULL) {
            free(ctx->current_date);
        }
        free(ctx);
    }
}
