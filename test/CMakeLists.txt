set(BINARY ${CMAKE_PROJECT_NAME}_tst)

set(TEST_SOURCES    main.cpp 
                    Gates_tst.cpp 
                    MemoryBit_tst.cpp
                    MemoryByte_tst.cpp 
                    Bit_tst.cpp
                    Byte_tst.cpp
                    ByteEnabler_tst.cpp
                    Register_tst.cpp
                    Decoder_tst.cpp)

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gmock)