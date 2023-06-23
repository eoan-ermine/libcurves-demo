cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    libcurves-demo
    VERSION 0.1.0
    HOMEPAGE_URL "https://github.com/eoan-ermine/libcurves-demo"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare executable ----

add_executable(libcurves-demo_exe source/main.cpp)
add_executable(libcurves-demo::exe ALIAS libcurves-demo_exe)

set_property(TARGET libcurves-demo_exe PROPERTY OUTPUT_NAME libcurves-demo)

target_compile_features(libcurves-demo_exe PRIVATE cxx_std_20)

find_package(libcurves REQUIRED)
target_link_libraries(libcurves-demo_exe INTERFACE libcurves::libcurves)

find_package(OpenMP REQUIRED)
target_link_libraries(libcurves-demo_exe PUBLIC OpenMP::OpenMP_CXX)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT libcurves-demo_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of libcurves-demo"
  )
endif()

include(cmake/dev-mode.cmake)
