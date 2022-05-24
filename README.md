# libdiurna

[![Latest release](https://img.shields.io/badge/latest_release-1.0.0-orange.svg)](https://github.com/thibaultmeyer/libdiurna/releases)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/thibaultmeyer/libdiurna/blob/master/LICENSE)
[![CodeFactor](https://www.codefactor.io/repository/github/thibaultmeyer/libdiurna/badge)](https://www.codefactor.io/repository/github/thibaultmeyer/libdiurna)
[![Repository size](https://img.shields.io/github/repo-size/thibaultmeyer/libdiurna.svg?logo=git)](https://github.com/thibaultmeyer/libdiurna)

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

#### Appender "Console" (Default)
```c
#include <stdlib.h>
#include <diurna.h>

int main(void) {
    // Initialize Diurna with min log level "DEBUG" and default appender
    int ret = diurna_initialize("test_diurna", DIURNA_LOGLEVEL_DEBUG);
    if (ret != DIURNA_SUCCESS) {
        return (EXIT_FAILURE);
    }

    // Add a new message with level "INFORMATION"
    diurna_info("libdiurna version %s (%d)", diurna_version_as_str(), diurna_version_as_int());

    // Flush latest log message and destroy Diurna context
    diurna_destroy();
    
    return (EXIT_SUCCESS);
}
```

#### Appender "File"
```c
#include <stdlib.h>
#include <diurna.h>

int main(void) {
    // Initialize Diurna with min log level "INFO" and "File" appender
    struct s_diurna_appender *appender_file = diurna_appender_file_create("/tmp/test.log");
    int ret = diurna_initialize_ex("test_diurna", DIURNA_LOGLEVEL_INFO, appender_file);
    if (ret != DIURNA_SUCCESS) {
        return (EXIT_FAILURE);
    }

    // Add a new message with level "INFORMATION"
    diurna_info("libdiurna version %s (%d)", diurna_version_as_str(), diurna_version_as_int());

    // Flush latest log messages and destroy Diurna context
    diurna_destroy();
    
    return (EXIT_SUCCESS);
}
```

#### Multiple appender
```c
#include <stdlib.h>
#include <diurna.h>

int main(void) {
    // Initialize Diurna with min log level "DEBUG" and default appender
    int ret = diurna_initialize("test_diurna", DIURNA_LOGLEVEL_DEBUG);
    if (ret != DIURNA_SUCCESS) {
        return (EXIT_FAILURE);
    }
    
    // Register "FILE" appender
    struct s_diurna_appender *appender_file = diurna_appender_file_create("/tmp/test.log");
    ret = diurna_cfg_appender_register(appender_file);
    if (ret != DIURNA_SUCCESS) {
        diurna_error("Can't register 'FILE' appender");
    }

    // Add a new message with level "INFORMATION"
    diurna_info("libdiurna version %s (%d)", diurna_version_as_str(), diurna_version_as_int());

    // Flush latest log message and destroy Diurna context
    diurna_destroy();
    
    return (EXIT_SUCCESS);
}
```

#### Run example

```shell
#> cc example.cc -ldiurna
```

```
2021-10-07 21:46:25.458 [INFO] libdiurna version 1.0.0 (10000)
```


## Built-in appender

| APPENDER | USAGE | INFORMATION |
|----------|-------|-------------|
| Console  | diurna_appender_console_create(void) ||
| File     | diurna_appender_file_create(const char* filename) | The filename can contains following variables: `{appname}` and `{date}`|
| Syslog   | diurna_appender_syslog_create(void) ||


## Create your own appender

Creating a new appender is very simple, you need to initialize an instance of
`struct s_diurna_appender` in which you have defined, at least, the function
`f_appender_write`.

Feel free to consult the source code of the built-in appender on `./src/appender/`.


## License
This project is released under terms of the [MIT license](https://github.com/thibaultmeyer/libdiurna/blob/master/LICENSE).
