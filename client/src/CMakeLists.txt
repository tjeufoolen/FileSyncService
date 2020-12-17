target_sources(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/Client.h"
        "${CMAKE_CURRENT_LIST_DIR}/exceptions/EndSessionException.h"
        "${CMAKE_CURRENT_LIST_DIR}/utils/StringSplitter.h"
        "${CMAKE_CURRENT_LIST_DIR}/utils/Logger.h"
        )

target_sources(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/Client.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/utils/StringSplitter.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/utils/Logger.cpp"
        )

target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/exceptions"
        "${CMAKE_CURRENT_LIST_DIR}/utils"
        )