#include "Client.h"

#include <filesystem>
#include <iostream>

#include "Logger.h"
#include "StringSplitter.h"
#include "MakeDirectoryCommand.h"
#include "InfoCommand.h"
#include "DeleteCommand.h"
#include "RenameCommand.h"
#include "DirectoryListingCommand.h"

const std::string Client::BASE_DIRECTORY = {std::filesystem::current_path().generic_string().append("/dropbox/")};

Client::Client(const std::string& hostname, const std::string& port)
    : HOSTNAME{hostname},
      PORT{port},
      expect_response_{true},
      multiple_responses_incoming_{false}
{
    connect();
}

void Client::connect()
{
    server_ = std::make_unique<asio::ip::tcp::iostream>(HOSTNAME, PORT);
    if (!*server_) throw std::runtime_error("could not connect to server");
}

void Client::run()
{
    bool keepRunning{true};
    while (keepRunning && *server_) {
        // Response
        if (expect_response_) {
            std::string resp;

            // default amount of responses on input = 1
            int responses = 1;

            // if multiple responses are expected, update the responses amount
            if (multiple_responses_incoming_) {
                getline(*server_, resp);
                resp.erase(resp.end() - 1); // remove '\r'
                responses = std::stoi(resp);
                multiple_responses_incoming_ = false;
            }

            // handle all responses
            for (int i=0; i<responses; i++) {
                getline(*server_, resp);
                resp.erase(resp.end() - 1); // remove '\r'
                handleResponse(resp);
            }

            keepRunning = handleRequest();
        } else {
            keepRunning = handleRequest();
        }
    }
}

void Client::handleResponse(const std::string& response)
{
    // if the response is an error (following the protocol), have the ability to print it different
    if (response.rfind("Error: ", 0) == 0) {
        Utils::Logger::error(response);
    } else {
        Utils::Logger::inform(response);
    }
}

bool Client::handleRequest()
{
    std::cout << Utils::Logger::PREFIX << std::flush;
    std::string req;

    // get user input
    getline(std::cin, req);

    // notify server that you are gonna disconnect and stop running
    if (req == "quit") {
        *server_ << req << Utils::Logger::CRLF;
        return false;
    }

    // if you aren't gonna disconnect, execute the command specified
    std::unique_ptr<std::vector<std::string>> args = std::move(Utils::StringSplitter::Split(req, ' '));
    handleCommand(req, *args);
    return true;
}

void Client::handleCommand(const std::string &request, const std::vector<std::string> &args)
{
    // handle no arguments provided
    if (args.empty()) {
        Utils::Logger::inform("Please specify a valid command.");
        expect_response_ = false;
        return;
    }

    // execute specified command
    if (args[0] == "mkdir") {
        expect_response_ = Commands::MakeDirectoryCommand{*server_, request, args}.Execute();
    }
    else if (args[0] == "info") {
        expect_response_ = Commands::InfoCommand{*server_, request, args}.Execute();
    }
    else if (args[0] == "del") {
        expect_response_ = Commands::DeleteCommand{*server_, request, args}.Execute();
    }
    else if (args[0] == "ren") {
        expect_response_ = Commands::RenameCommand{*server_, request, args}.Execute();
    }
    else if (args[0] == "dir") {
        expect_response_ = Commands::DirectoryListingCommand{*server_, request, args}.Execute();
        multiple_responses_incoming_ = true;
    }

    // handle specified command isn't defined
    else {
        Utils::Logger::inform("The command you entered does not exist.");
        expect_response_ = false;
    }
}