#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "diurna_internal.h"

static inline const char *retrieve_filename(struct s_diurna_appender_file_ctx *const ctx,
                                            const char *appname,
                                            const char *date) {
    // If filename is already generated for current date, use it
    if (ctx->current_filename != NULL && strncmp(ctx->current_date, date, 10) == 0) {
        return (ctx->current_filename);
    }

    // Generate filename
    size_t idx_variable;
    size_t idx_str_parsed = 0;
    size_t idx_str        = 0;
    size_t allocated      = strlen(ctx->output_filename);
    char   *str_parsed    = malloc(sizeof(char) * allocated);
    char   variable[12]   = {0};

    memset(str_parsed, 0, sizeof(char) * allocated);

    while (ctx->output_filename[idx_str] != '\0') {
        if (ctx->output_filename[idx_str] == '{') {
            memset(variable, 0, sizeof(char) * 12);
            idx_variable = 0;

            while (ctx->output_filename[++idx_str] != '}' && idx_variable < 12) {
                variable[idx_variable] = ctx->output_filename[idx_str];
                idx_variable += 1;
            }

            if (strncmp(variable, "appname", 7) == 0) {
                size_t appname_len = strlen(appname);
                str_parsed = realloc(str_parsed, sizeof(char) * (allocated + appname_len) + 1);

                memcpy(str_parsed + idx_str_parsed, appname, appname_len);
                idx_str_parsed += appname_len;
                allocated += appname_len;
            } else if (strncmp(variable, "date", 4) == 0) {
                str_parsed = realloc(str_parsed, sizeof(char) * allocated + 11);

                memcpy(str_parsed + idx_str_parsed, date, 10);
                idx_str_parsed += 10;
                allocated += 10;
            }
        } else {
            str_parsed[idx_str_parsed++] = ctx->output_filename[idx_str];
        }

        str_parsed[idx_str_parsed] = '\0';
        idx_str += 1;
    }

    // Clean existing values
    if (ctx->current_filename != NULL) {
        free(ctx->output_filename);
    }
    if (ctx->current_date != NULL) {
        free(ctx->current_date);
    }

    // Set new filename to use and date
    ctx->current_filename = str_parsed;
    ctx->current_date     = strdup(date);

    return (str_parsed);
}

void diurna_appender_file_write(void *const appender_ctx,
                                const char *const app_name,
                                const enum e_diurna_log_level level,
                                const struct timeval *const tv,
                                const char *const log_msg) {
    // Convert timeval to human reading time
    char      date_stamp[24] = {0};
    struct tm *tm_stamp      = gmtime(&tv->tv_sec);
    strftime(date_stamp, sizeof(date_stamp), "%Y-%m-%d %H:%M:%S", tm_stamp);

    // Level
    char *level_as_str;
    switch (level) {
        case DIURNA_LOGLEVEL_DEBUG:
            level_as_str = "DEBUG";
            break;
        case DIURNA_LOGLEVEL_INFO:
            level_as_str = "INFO";
            break;
        case DIURNA_LOGLEVEL_WARN:
            level_as_str = "WARN";
            break;
        case DIURNA_LOGLEVEL_ERROR:
            level_as_str = "ERROR";
            break;
        default:
            level_as_str = "NONE";
    }

    // Write message to log file
    struct s_diurna_appender_file_ctx *ctx      = appender_ctx;
    const char                        *filename = retrieve_filename(ctx, app_name, date_stamp);
    FILE                              *file     = fopen(filename, "a+");

    if (file != NULL) {
        fprintf(file, "%s.%.03d [%s] %s\n", date_stamp, (int) (tv->tv_usec / 1000), level_as_str, log_msg);
        fclose(file);
    } else {
        perror(filename);
    }
}
