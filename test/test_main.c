#include "../src/diurna.h"

int main(const int argc, const char *const *argv) {
    diurna_initialize("test");

    diurna_info("libdiurna version %s (%d)", diurna_get_version_as_str(), diurna_get_version_as_int());
    diurna_debug("Aliquam sed mi risus");
    diurna_warn("Lorem ipsum dolor sit amet, consectetur adipiscing elit");
    diurna_error("Duis quis pretium leo, id fermentum justo");

    diurna_destroy();

    return (0);
}
