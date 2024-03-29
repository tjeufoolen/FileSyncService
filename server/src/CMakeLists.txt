target_sources(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/Server.h"
    "${CMAKE_CURRENT_LIST_DIR}/utils/StringSplitter.h"
    "${CMAKE_CURRENT_LIST_DIR}/utils/Logger.h"
    "${CMAKE_CURRENT_LIST_DIR}/utils/TimestampConverter.h"
    "${CMAKE_CURRENT_LIST_DIR}/commands/ICommand.h"
    "${CMAKE_CURRENT_LIST_DIR}/commands/Command.h"
    "${CMAKE_CURRENT_LIST_DIR}/commands/InfoCommand.h"
    "${CMAKE_CURRENT_LIST_DIR}/commands/MakeDirectoryCommand.h"
    "${CMAKE_CURRENT_LIST_DIR}/commands/DeleteCommand.h"
    "${CMAKE_CURRENT_LIST_DIR}/commands/RenameCommand.h"
    "${CMAKE_CURRENT_LIST_DIR}/commands/DirectoryListingCommand.h"
    "${CMAKE_CURRENT_LIST_DIR}/commands/DownloadFileCommand.h"
    "${CMAKE_CURRENT_LIST_DIR}/commands/UploadFileCommand.h"
)

target_sources(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/Server.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/utils/StringSplitter.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/utils/Logger.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/commands/Command.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/commands/InfoCommand.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/commands/MakeDirectoryCommand.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/commands/DeleteCommand.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/commands/RenameCommand.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/commands/DirectoryListingCommand.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/commands/DownloadFileCommand.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/commands/UploadFileCommand.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}"
    "${CMAKE_CURRENT_LIST_DIR}/utils"
    "${CMAKE_CURRENT_LIST_DIR}/exceptions"
    "${CMAKE_CURRENT_LIST_DIR}/commands"
)
