cmake_minimum_required(VERSION 3.28)

project(lab1 VERSION 1.0.0 LANGUAGES C)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SOURCES
    src/list/initList.c
    src/list/addNode.c
    src/list/deleteHead.c
    src/list/deleteTail.c 
    src/list/clearList.c
    src/list/printList.c
    src/list/serializeList.c
    src/list/deserializeList.c
    src/list/searchByFirstname.c
    src/list/searchByLastname.c
    src/list/searchByGrade.c
    src/grade-convert/gradeToString.c
    src/grade-convert/stringToGrade.c
    src/keyreader/getch.c
    src/utils/instruction.c
    src/utils/clickEsc.c
    src/list/deleteById.c
    
    src/main.c
)

add_executable(${PROJECT_NAME} ${SOURCES})