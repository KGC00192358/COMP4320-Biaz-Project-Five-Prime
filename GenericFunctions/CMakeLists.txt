add_library(GenericFunctions
	Generic_Functions.c
	Generic_Functions.h
	)
#add_executable(Encoder Encoder.c)
#add_executable(Decoder Decoder.c)
option (PACKAGE_TESTS "Build the tests" OFF)
if(PACKAGE_TESTS)
	enable_testing()
	add_subdirectory(unit_test)
endif()
