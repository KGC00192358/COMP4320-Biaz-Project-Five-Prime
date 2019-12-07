cmake_minimum_required (VERSION 2.8 FATAL_ERROR)
project("Fortner Womack Conyers Project Fourc")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /WX /EHsc")
endif()

if (NOT CONFIGURED_ONCE)
    set(CMAKE_CXX_FLAGS "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
    set(CMAKE_C_FLAGS   "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()


set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${warnings}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(EncodeDecode)
add_subdirectory(GenericFunctions)

if(CSERVERBUILD)
	add_executable(ServerTCP ServerTCP.c)
	target_link_libraries(ServerTCP EncodeDecode)
	target_link_libraries(ServerTCP GenericFunctions)
endif()
add_executable(ClientTCP ClientTCP.c)
target_link_libraries(ClientTCP EncodeDecode)
target_link_libraries(ClientTCP GenericFunctions)
