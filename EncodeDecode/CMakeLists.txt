add_library(EncodeDecode
	Encoder.c
	Decoder.c
	RequestResponse.h
	)
#add_executable(Encoder Encoder.c)
#add_executable(Decoder Decoder.c)
option (PACKAGE_TESTS "Build the tests" OFF)
if(PACKAGE_TESTS)
	enable_testing()
	add_subdirectory(unit_test)
endif()
