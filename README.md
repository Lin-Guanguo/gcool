# GCool - cool language implement by LGG

## feature

* Using llvm toolchain
* Generate llvm IR
* Part of the runtime library is written in C, other write in gcool.
* Use Fat Pointer
* Special optimization for primitive types(Int, Float, Bool, Std, NullType), they will not use heap memory(place data directly in object pointer).

## todo

* user define operator.
* garbage collection

## build

dependencies: llvm-13, google-test, Ninja, c++20

```bash
mkdir build
cd build
cmake .. -G Ninja
```

set CMakeCache.txt GTEST_DIR

```bash
ninja
```
