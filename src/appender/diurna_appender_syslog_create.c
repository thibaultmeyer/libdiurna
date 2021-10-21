#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include "diurna_internal.h"

struct s_diurna_appender *diurna_appender_syslog_create(void) {
    struct s_diurna_appender *appender = malloc(sizeof(struct s_diurna_appender) + 1);

    if (appender != NULL) {
        memset(appender, 0, sizeof(struct s_diurna_appender) + 1);

        appender->f_write = &diurna_appender_syslog_write;
    }

    return (appender);
}
