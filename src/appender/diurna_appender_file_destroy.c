#include <stdio.h>

void diurna_appender_file_destroy(void *appender_ctx) {
    if (appender_ctx != NULL) {
        FILE *file_description = appender_ctx;

        fflush(file_description);
        fclose(file_description);
    }
}
