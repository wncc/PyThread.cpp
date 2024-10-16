# Parallel_Programming
Parallel programming is often used interchangeably with parallel processing or in connection with parallel computing, which refers to systems that enhance the efficiency of parallel execution. In parallel programming, tasks are divided and executed simultaneously across multiple computers or multiple CPU cores. This approach is essential for large-scale projects where speed and precision are crucial. Although complex, parallel programming enables developers, researchers, and users to perform research and analysis much faster than programs limited to processing tasks sequentially

## Project Description
This project demonstrates the use of parallel programming techniques in C++ with OpenMP to efficiently execute computations across multiple threads. It includes examples of parallel loops, task scheduling, and thread synchronization. The goal is to showcase performance improvements in computational tasks using OpenMP directives.

## **1. OpenMP** <a id="openmp"></a>

`OpenMP` is a multi-platform programming interface that enables multiprocessing programming. `OpenMP` can be used in C++, C and Fortran languages, including different architectures like Windows and Unix. It consists of compilator directives that have an impact on code execution.

The `OpenMP` interface is a component of the GNU Compiler Collection (`GCC`), a set of open-source compilers developed by the GNU Project. `GCC` compiler is therefore highly recommended for use with `OpenMP`, although it is not required (there is an Intel compiler that also support `OpenMP`).

**INSTALLATION AND CONFIGURATION ON LINUX SYSTEMS:**

Start the terminal and update the repository:

```bash
>>> sudo apt-get update
```

Then install the `build-essential` package, including `gcc`, `g++` and `make`:

```bash
>>> sudo apt-get install build-essential
```

We can also install the manual pages on using GNU/Linux for programming, but it is not necessary:

```bash
>>> sudo apt-get install manpages-dev
```

To check `GCC` version, type:

```bash
>>> gcc --version
```

**INSTALLATION AND CONFIGURATION ON WINDOWS 10:**

On Windows, we need `MinGW`, a port of `GCC` providing a free, open environment
and tools that allow us to compile native executables for the Windows platform.
To do this, we go to: [https://sourceforge.net/projects/mingw/](https://sourceforge.net/projects/mingw/) and download `MinGW` - Minimalist GNU for Windows. Once installed, we check the compiler in the command line:

```bash
>>> gcc -v
```

Make sure that you've installed the `GCC` with the Posix thread model. If you get a message that the command is not recognised, add the appropriate environment variable to your system - "`../MinGW/bin`".

The use of `OpenMP` requires including a following library in the C/C++ code:

```c++
#include <omp.h>
```

It is also required to specify the appropriate flag during compilation:

```bash
>>> gcc -fopenmp -pedantic -pipe -O3 -march=native main.cpp -o main
```

The above flags mean:

- `-fopenmp` enables the execution of `OpenMP` directives,
- `-pedantic` is a standard error warning flag,
- `-pipe` causes that temporary files will be avoided, which speeds up build,
- `-O3` imposes a high degree of optimisation (be careful with this),
- `-march=native` generates code dedicated to the system on which it is compiled.

Only the `-fopenmp` flag is required for `OpenMP` to work. The others are optional flags which are worth using to optimise the code. We can read more about `GNU GCC` here: [https://gcc.gnu.org/](https://gcc.gnu.org/).

---
