# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(libcurves-demoTests LANGUAGES CXX)

# ---- Dependencies ----

find_package(Catch2 REQUIRED)
include(Catch)

# ---- Tests ----

add_executable(libcurves-demo_test source/libcurves-demo_test.cpp)
target_link_libraries(
    libcurves-demo_test PRIVATE
    libcurves-demo_lib
    Catch2::Catch2WithMain
)
target_compile_features(libcurves-demo_test PRIVATE cxx_std_20)

catch_discover_tests(libcurves-demo_test)

# ---- End-of-file commands ----

add_folders(Test)
