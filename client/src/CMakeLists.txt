target_sources(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/Client.h"
        "${CMAKE_CURRENT_LIST_DIR}/utils/StringSplitter.h"
        "${CMAKE_CURRENT_LIST_DIR}/utils/Logger.h"
        "${CMAKE_CURRENT_LIST_DIR}/commands/ICommand.h"
        "${CMAKE_CURRENT_LIST_DIR}/commands/Command.h"
        "${CMAKE_CURRENT_LIST_DIR}/commands/MakeDirectoryCommand.h"
        "${CMAKE_CURRENT_LIST_DIR}/commands/InfoCommand.h"
        "${CMAKE_CURRENT_LIST_DIR}/commands/DeleteCommand.h"
        "${CMAKE_CURRENT_LIST_DIR}/commands/RenameCommand.h"
        "${CMAKE_CURRENT_LIST_DIR}/commands/DirectoryListingCommand.h"
        )

target_sources(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/Client.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/utils/StringSplitter.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/utils/Logger.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/commands/Command.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/commands/MakeDirectoryCommand.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/commands/InfoCommand.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/commands/DeleteCommand.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/commands/RenameCommand.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/commands/DirectoryListingCommand.cpp"
        )

target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}"
        "${CMAKE_CURRENT_LIST_DIR}/exceptions"
        "${CMAKE_CURRENT_LIST_DIR}/commands"
        "${CMAKE_CURRENT_LIST_DIR}/utils"
        )