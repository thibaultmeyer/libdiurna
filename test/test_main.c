#include <stdio.h>
#include "../src/diurna.h"

int main(const int argc, const char *const *argv) {
    printf("libdiurna version %s (%d)\n", diurna_get_version_as_str(), diurna_get_version_as_int());

    diurna_initialize();

    diurna_info("libdiurna version %s (%d)", diurna_get_version_as_str(), diurna_get_version_as_int());
    diurna_warn("Oooops");

    diurna_destroy();

    return (0);
}
