#pragma once
#include <functional>

class IRCClient
{
public:
    IRCClient(const std::string &server, int port, const std::string &nick, const std::string &user, const std::string &channel);

    void disconnect();

    bool connectToServer();
    void sendCommand(const std::string &command);
    void receiveMessages(std::function<void(const std::string &)> onCommand);
    void handleMessage(const std::string &message);

private:
    std::string server;
    int port;
    std::string nick;
    std::string user;
    std::string channel;
    int sock;
};