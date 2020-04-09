# libtoolchain - Toolchain Development Library
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](./LICENSE)
![Language](https://img.shields.io/badge/langauge-c++11-blue.svg)
![Platform](https://img.shields.io/badge/platform-linux--64%20%7C%20linux--32%20%7C%20win--64%20%7C%20win--32%20%7C%20macos--64-lightgrey.svg)

![Version](https://img.shields.io/badge/version-0.3.0%20%7C%20prerelease-green.svg)

Library to ease the development of toolchain applications.

This library aims to help with the busy work that is common to many toolchain development projects including:
* Cross platform FileSystem IO with large file support for both 32bit & 64bit targets and unicode path support
* String transcoding (UTF-8/UTF-16/UTF-32)
* Usable abstractions/interfaces for generating and processing files and binary data.

Planned features:
* CLI argv processing
* Serialisation of human readable formats (XML, JSON, YAML, INI, CSV, etc)
* Properly integrated wrappers for Compression Algorithms (LZ4, etc)
* Properly integrated wrappers for Cryptographic Algorithms (AES, RSA, Eliptic Curve, SHA, etc)

# File tree
* `bin/` - Compiled binaries
* `build/visualstudio/` - Visual Studio Project files
* `docs/` - Doxygen Generated API Documentation
* `include/` - Public headers
* `src/` - Library source code & private headers
* `test/` - Test program source code
* `Makefile` - Root makefile (GNU/Unix build system file)
* `LICENCE` - Distribution License 
* `Doxyfile`  -  Doxygen config

# Building
For GNU/unix systems `make` can be used. For native Windows, Visual Studio project files are provided.

See more [here](./BUILDING.md).

# Documentation
The documentation is available at docs/index.html. Or alternatively at https://jakcron.github.io/libtoolchain.

# License 
This source code is made available under the [MIT license](./LICENSE).
