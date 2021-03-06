A benchmark for c/c++ standard library.

[![Build
Status](https://travis-ci.org/hiraditya/std-benchmark.svg?branch=master)](https://travis-ci.org/hiraditya/std-benchmark)

**DEPENDENCIES**
- CMake 2.8 or higher
- Since this is a standard library benchmark, you need a compiler toolchain to benchmark.
- A C++ compiler with C++11 support
- google-benchmark (added as a submodule)
        To download the google-benchmark submodule run the following command in the project root.
        `git submodule update --recursive --remote`

**BUILDING ON LINUX, MAC**
```sh
mkdir $SRC/build
cd $SRC/build
cmake ..
cmake --build .
cmake --buid . --config Release
```

When you are compiling with clang compiler along with libcxx enabled (-DBENCHMARK_USE_LIBCXX=ON),
you might get cmake error like this:
```sh
   CMake Error at benchmark/CMakeLists.txt:171 (message):
   Failed to determine the source files for the regular expression backend
  -- Configuring incomplete, errors occurred!
```

In that case,
```sh
export LD_LIBRARY_PATH=path-to-clang-install/lib
```

**BUILDING WITH VISUAL STUDIO**
```sh
mkdir $SRC/build
cd $SRC/build
C:\Program Files (x86)\Microsoft Visual Studio <Version>\VC\vcvarsall.bat amd64
cmake -G"Visual Studio 15 2017 Win64" ..
cmake --build . --config release
```

Remember to use a generator for Win64 otherwise 32-bit binaries will be built.
For more help see config.bat in the top level directory. It has some useful tricks
which allows you to use git-bash for building and running the tests.

If there are errors then build the project by opening the visual studio IDE (devenv)
and then try to build one component at a time.

**TESTING**

To test the project run ctest. Running ctest will run the google-benchmark harness tests
as well, so if you are only interested in runningthe `c` and `cxx` std-benchmark tests use:
```sh
ctest -L c --verbose
ctest -L cxx --verbose
ctest -C Release -L c.vs.cxx --verbose
```

NB: On windows the tests might not run because ctest adds each test under specific
configurations. So you have to pass the appropriate configuration using the `-C <config>` e.g.,
```sh
ctest -C Release -L c --verbose
ctest -C Release -L cxx --verbose
ctest -C Release -L c.vs.cxx --verbose
```

