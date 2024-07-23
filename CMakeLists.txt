cmake_minimum_required(VERSION 3.5)
project (hello_headers)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    intelhex_diag/intelhex_diag.cpp
    intelhex_class/intelhexclass.cpp
)
# file(GLOB SOURCES "src/*.cpp")
# aux_source_directory(src SOURCES)

# Add an executable with the above sources
add_executable(hello_headers ${SOURCES})

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(hello_headers
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/intelhex_class
)
