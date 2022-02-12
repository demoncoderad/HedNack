cmake_minimum_required(VERSION 3.21)
project(HedNack)

set(CMAKE_CXX_STANDARD 17)

set (Res_source "${CMAKE_SOURCE_DIR}/Res")
set (Res_destination "${CMAKE_CURRENT_BINARY_DIR}/Res")

add_executable(HedNack HedNack/Source/main.cpp HedNack/Include/RunCode.h HedNack/Include/Token.h HedNack/Source/Token.cpp HedNack/Source/RunCode.cpp HedNack/Source/Scanner.cpp HedNack/Include/Scanner.h HedNack/Include/Error.h HedNack/Source/Error.cpp HedNack/Source/Parser.cpp HedNack/Include/Parser.h HedNack/Source/Expressions/Expression.cpp HedNack/Include/Expressions/Expression.h HedNack/Include/Expressions/ExpressionVisitorPrint.h HedNack/Source/Expressions/ExpressionVisitorPrint.cpp)
target_include_directories(HedNack PUBLIC "HedNack/Include")

add_executable(HedNack_PrintTest HedNack/Source/Expressions/ExpressionVisitorPrint.cpp HedNack/Include/Expressions/ExpressionVisitorPrint.h HedNack/Include/Token.h HedNack/Source/Token.cpp HedNack/Source/Expressions/Expression.cpp HedNack/Include/Expressions/Expression.h)
target_include_directories(HedNack_PrintTest PUBLIC "HedNack/Include")

add_custom_command(
        TARGET HedNack POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink ${Res_source} ${Res_destination}
        DEPENDS ${Res_destination}
        COMMENT "symbolic link resources folder from ${Res_source} => ${Res_destination}"
)
