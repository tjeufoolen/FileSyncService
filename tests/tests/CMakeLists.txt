target_sources(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/Tests.h"
    "${CMAKE_CURRENT_LIST_DIR}/Test.h"
    "${CMAKE_CURRENT_LIST_DIR}/InfoCommandTest.h"
    "${CMAKE_CURRENT_LIST_DIR}/DirCommandTest.h"
    "${CMAKE_CURRENT_LIST_DIR}/GetCommandTest.h"
    "${CMAKE_CURRENT_LIST_DIR}/PutCommandTest.h"
)

target_sources(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/Test.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/InfoCommandTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/DirCommandTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/GetCommandTest.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/PutCommandTest.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/tests"
)