cmake_minimum_required(VERSION 3.0.0)
project(pwmfanctrl VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()
set(CMAKE_CXX_STANDARD 20)
add_executable(pwmfanctrl main.cpp src/pwm.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
