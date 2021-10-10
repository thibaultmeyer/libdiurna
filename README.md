# libdiurna

[![Latest release](https://img.shields.io/badge/latest_release-1.0.0-orange.svg)](https://github.com/thibaultmeyer/libdiurna/releases)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/thibaultmeyer/libdiurna/blob/master/LICENSE)
[![CodeFactor](https://www.codefactor.io/repository/github/thibaultmeyer/libdiurna/badge)](https://www.codefactor.io/repository/github/thibaultmeyer/libdiurna)

A simple, fast, and portable logging library.
*****

## Build & install from sources
To compile and install this project, you must ensure that make, cmake, gcc or
clang or MSVC are being correctly installed.

```shell
#> mkdir cmake-build-release
#> cd cmake-build-release
#> cmake -DCMAKE_BUILD_TYPE=Release ..
#> make
#> make install
```

## Usage
```c
#include <diurna.h>

int main(const int argc, const char *const *argv) {
    // Initialize Diurna with min log level "INFO" and default appender
    diurna_initialize("my_application", DIURNA_LOGLEVEL_INFO, NULL);

    // Add a new message with level "INFORMATION"
    diurna_info("libdiurna version %s (%d)", diurna_get_version_as_str(), diurna_get_version_as_int());

    // Flush latest log message and destroy Diurna context
    diurna_destroy();
    
    return (0);
}
```

```shell
#> cc example.cc -ldiurna
```

```
2021-10-07 21:46:25.458 [INFO] libdiurna version 1.0.0 (10000)
```


## License
This project is released under terms of the [MIT license](https://github.com/thibaultmeyer/libdiurna/blob/master/LICENSE).