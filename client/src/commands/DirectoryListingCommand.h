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
            std::string Name;
            long long ModifiedAt;
            long long Size;

            Item(const ItemType& type, const std::string& name, long long modified_at, long long size)
                :  Type{type}, Name{name}, ModifiedAt{modified_at}, Size{size}  {}
        };
    private:
        std::vector<Item> items_;
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
