#ifndef CPPLS2_CLIENT_DIRECTORYLISTINGCOMMAND_H
#define CPPLS2_CLIENT_DIRECTORYLISTINGCOMMAND_H

#include "Command.h"

namespace Commands {
    class DirectoryListingCommand : public Command
    {
    public:
        enum class ItemType {
            DIRECTORY,
            FILE,
            OTHER
        };
        struct Item {
            ItemType Type;
            std::string Path;
            std::string Name;
            std::string ModifiedAt;
            std::string Size;

            Item(const ItemType& type, const std::string& name, const std::string& path, const std::string& modified_at, const std::string& size)
                :  Type{type}, Name{name}, Path{path}, ModifiedAt{modified_at}, Size{size}  {}
        };
    private:
        std::vector<Item> items_;
        std::string path_;
    public:
        DirectoryListingCommand(asio::ip::tcp::iostream& server, const std::string& request, const std::vector<std::string>& args, bool log = true);

        bool Execute() override;
        void HandleResponse() override;

        std::vector<Item> GetItems() const;
    private:
        void SaveItemOutputHistory(const std::string& output);
    };
}

#endif //CPPLS2_CLIENT_DIRECTORYLISTINGCOMMAND_H
