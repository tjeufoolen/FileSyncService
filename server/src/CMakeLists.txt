target_sources(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/Server.h"
    "${CMAKE_CURRENT_LIST_DIR}/utils/StringSplitter.h"
    "${CMAKE_CURRENT_LIST_DIR}/utils/Logger.h"
    "${CMAKE_CURRENT_LIST_DIR}/exceptions/ClientDisconnectException.h"
    "${CMAKE_CURRENT_LIST_DIR}/commands/ICommand.h"
    "${CMAKE_CURRENT_LIST_DIR}/commands/Command.h"
    "${CMAKE_CURRENT_LIST_DIR}/commands/InfoCommand.h"
    "${CMAKE_CURRENT_LIST_DIR}/commands/QuitCommand.h"
    "${CMAKE_CURRENT_LIST_DIR}/commands/MakeDirectoryCommand.h"
)

target_sources(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/Server.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/utils/StringSplitter.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/utils/Logger.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/commands/Command.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/commands/InfoCommand.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/commands/QuitCommand.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/commands/MakeDirectoryCommand.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}"
    "${CMAKE_CURRENT_LIST_DIR}/utils"
    "${CMAKE_CURRENT_LIST_DIR}/exceptions"
    "${CMAKE_CURRENT_LIST_DIR}/commands"
)
