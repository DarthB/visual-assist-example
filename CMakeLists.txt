# Setup cmake project, policies and minimum version.
cmake_policy(SET CMP0048 NEW)
project(example_va VERSION 0.1.0 
	DESCRIPTION "An example project to show capabilities of visual assist."
	HOMEPAGE_URL "https://github.com/DarthB/example_va"
)
cmake_minimum_required(VERSION 3.20)

# We will use C++17 Standard in this example project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# We use gsl to be explicit about ownership
include(FetchContent)
FetchContent_Declare(GSL
    GIT_REPOSITORY "https://github.com/microsoft/GSL"
    GIT_TAG "v3.1.0"
)
FetchContent_MakeAvailable(GSL)


# Option to turn on/off unit testing
option(DO_TESTS "Perform Testiing with gooogle test framework" ON)

#add_definitions(-DRESULT_NAMESPACE vae)

# The library project
add_library(example_va_lib
	"src/def/Problem.cpp"
	"src/def/Variable.cpp"
	"src/om/OptimizationMethodFactory.cpp"
	"src/om/OptimizationMethodBase.cpp"
	"src/om/OptimizationMethodDFORandomSearch.cpp")
target_link_libraries(example_va_lib PRIVATE Microsoft.GSL::GSL)
target_include_directories(example_va_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc")

# The executable of the program
add_executable(example_va_bin 
	"src/main_example_va.cpp"
)
target_include_directories(example_va_bin PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc")
target_link_libraries(example_va_bin PRIVATE example_va_lib)

# 
if (DO_TESTS)
	find_package(GTest)

	# The test code project for the library
	if (GTEST_FOUND)
		enable_testing()
		message(STATUS "Setup test project")
		add_executable(example_va_tests  "tests/Problem.cpp")
		target_include_directories(example_va_tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/inc")
		target_link_libraries(example_va_tests PRIVATE GTest::gtest_main example_va_lib)

		include(GoogleTest)
		gtest_discover_tests(example_va_tests)
	else()
		message(WARNING "The google test library has not been found, neglecting tests.")
	endif()
endif()