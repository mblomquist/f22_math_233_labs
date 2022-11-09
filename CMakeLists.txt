cmake_minimum_required(VERSION 3.22)
project(f22_math_233_labs)

set(CMAKE_CXX_STANDARD 14)

add_executable(f22_math_233_labs
        mains/main_lab06.cpp
        lib/Grid2d.cpp
        lib/Grid2d.h
        lib/FullMatrix.cpp
        lib/FullMatrix.h
        lib/math_tools.cpp
        lib/math_tools.h
        lib/SL_method.cpp
        lib/SL_method.h
        lib/Matrix.cpp
        lib/Matrix.h
        lib/FVsolver.cpp
        lib/FVsolver.h
        lib/cf2.cpp
        lib/cf2.h
        lib/Solvers.cpp
        lib/Solvers.h)
