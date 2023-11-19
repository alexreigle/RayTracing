# CMakeList.txt : CMake project for OneWeekend, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("OneWeekend")

# Add source to this project's executable.
add_executable (OneWeekend "OneWeekend.cpp" "OneWeekend.h" "color.h" "vec3.h" "ray.h" "hittable.h" "sphere.h" "hittable_list.h" "constants.h" "interval.h")

# TODO: Add tests and install targets if needed.
