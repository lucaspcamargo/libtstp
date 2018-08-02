cmake_minimum_required(VERSION 3.0)

project(libtstp)
set (CMAKE_CXX_STANDARD 11)


# LIBRARY DEF
add_library(libtstp STATIC 
    src/libtstp.cpp 
    src/tstpcrypto.cpp
    src/tstpengine.cpp
    src/tstpgeom.cpp
    src/tstpstructs.cpp )
target_include_directories( libtstp PRIVATE include/ thirdparty/ )

## INSTALLATION
install(TARGETS libtstp ARCHIVE DESTINATION lib)
