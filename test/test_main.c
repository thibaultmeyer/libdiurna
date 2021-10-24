#include <stdlib.h>
#include "diurna.h"

int main(const int argc, const char *const *argv) {
    (void) argc; // Unused parameter
    (void) argv; // Unused parameter

    int ret = diurna_initialize("test_diurna", DIURNA_LOGLEVEL_DEBUG);
    if (ret != DIURNA_SUCCESS) {
        return (EXIT_FAILURE);
    }

    // Register "FILE" appender
    struct s_diurna_appender *appender_file = diurna_appender_file_create("/tmp/{appname}_{date}.log");
    ret = diurna_cfg_appender_register(appender_file);
    if (ret != DIURNA_SUCCESS) {
        diurna_error("Can't register 'FILE' appender");
    }

    diurna_info("libdiurna version %s (%d)", diurna_version_as_str(), diurna_version_as_int());
    diurna_debug("Aliquam sed mi risus");
    diurna_warn("Lorem ipsum dolor sit amet, consectetur adipiscing elit");
    diurna_error("Duis quis pretium leo, id fermentum justo");

    diurna_destroy();

    return (EXIT_SUCCESS);
}
