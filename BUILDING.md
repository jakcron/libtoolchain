# Building
## Linux (incl. Windows Subsystem for Linux) & MacOS - Makefile
### Requirements
* `make`
* `doxygen`
* `graphvis`
* Terminal access
* Typical GNU compatible development tools (e.g. `clang`, `g++`, `c++`, `ar` etc) with __C++11__ support

### Using Makefile
* `make` (default) - Compile library & self-test program & generate documentation
* `make lib` - Compile library
* `make selftest` - Compile self-test program
* `make docs` - Generate documentation
* `make clean` - Remove all object files, compiled programs and documentation

## Native Win32 - Visual Studio
### Requirements
* [Visual Studio Community](https://visualstudio.microsoft.com/vs/community/) 2015 or 2017
* [Doxygen](http://www.doxygen.nl/download.html#srcbin)
* [Graphvis](https://graphviz.gitlab.io/_pages/Download/Download_windows.html) (make sure to download the GUI)
	* Add the location of the Graphvis `bin` directory to `$(PATH)` or create a separate enviroment variable `$(DOT_PATH)` for it.

### Compiling Library & Self-Test Program
* Open `build/visualstudio/libtoolchain.sln` in Visual Studio
* Select Target (e.g `Debug`|`Release` & `x86`|`x64`)
* Navigate to `Build`->`Build Solution`

### Including libtoolchain in another VS Solution for static linking
* Clone `libtoolchain` as a submodule into your project
* Navigate to the `Solution Explorer` window
* Right-click on the Solution Item and select `Add`->`Existing Project...`
* In the filesystem popup window open `<libtoolchain location>/build/visualstudio/libtoolchain/libtoolchain.vcxproj`
* Update each dependant project's `References` to include libtoolchain
* Update each dependant project's `Property Pages` so that for `All Configurations` and `All Platforms` the `Addition Include Directories` has the relative path to `<libtoolchain location>/include`
* Update the `Project Build Order` so libtoolchain is built before any of its dependants
* Update the `Project Dependencies` so that each dependant has the box checked for libtoolchain

### Generating Doxygen Documentation
* Open `Doxywizard`
* Under `Step 1` specify the directory of libtoolchain as the working directory
* This should open the Doxyfile and pre-fill all the configuration
* Under `Step 2` navigate to `Run` and press `Run doxygen`
