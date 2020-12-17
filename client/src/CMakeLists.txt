target_sources(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/client.h"
        )

target_sources(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/client.cpp"
        )

#target_include_directories(${PROJECT_NAME} PRIVATE
#        "${CMAKE_CURRENT_LIST_DIR}/models"
#        "${CMAKE_CURRENT_LIST_DIR}/utils"
#        )