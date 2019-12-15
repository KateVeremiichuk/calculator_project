set(CALC_PARSER parser)

add_library(${CALC_PARSER}
    src/Parser.cpp
    )

target_include_directories(${CALC_PARSER}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

target_link_libraries(${CALC_PARSER}
    PUBLIC lexer
    PUBLIC ast
    )

if(CALC_BUILD_TESTS)
    add_subdirectory(test)
endif()
