cmake_minimum_required(VERSION 3.16)
project(budget_limited_reads LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

add_library(mirror_engine STATIC
  src/engine/fake_backend.cpp
  src/mirror/mirror_reader.cpp
  src/mirror/verify.cpp
  src/policy/selector.cpp
  src/policy/hedge_fixed.cpp
  src/policy/hedge_budget.cpp
  src/accounting/counters.cpp
  src/accounting/logger.cpp
  src/workload/trace.cpp
)
target_include_directories(mirror_engine PUBLIC src)
target_compile_options(mirror_engine PRIVATE -Wall -Wextra -Wpedantic)

# io_uring backend is Linux-only; macOS builds use the fake backend.
if(UNIX AND NOT APPLE)
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(URING REQUIRED liburing)
  target_sources(mirror_engine PRIVATE src/engine/uring_backend.cpp)
  target_compile_definitions(mirror_engine PUBLIC BLR_HAVE_URING=1)
  target_include_directories(mirror_engine PUBLIC ${URING_INCLUDE_DIRS})
  target_link_libraries(mirror_engine PUBLIC ${URING_LIBRARIES})
endif()

add_executable(blr src/main.cpp)
target_link_libraries(blr PRIVATE mirror_engine)

add_executable(gen_trace src/workload/gen_trace.cpp)
target_link_libraries(gen_trace PRIVATE mirror_engine)

enable_testing()
add_executable(blr_tests tests/test_main.cpp)
target_link_libraries(blr_tests PRIVATE mirror_engine)
add_test(NAME blr_tests COMMAND blr_tests)
