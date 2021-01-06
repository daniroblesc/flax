set(BINARY ${CMAKE_PROJECT_NAME}_tst)

set(TEST_SOURCES main.cpp Gates_tst.cpp MemoryBit_tst.cpp)

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest gmock)