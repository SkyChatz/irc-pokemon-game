#include <iostream>
#include <string>
#include <cstring>
#include <netdb.h>
#include <unistd.h>
#include "irc_client.h"
#include "game/game_logic.h"

IRCClient::IRCClient(const std::string &server, int port, const std::string &nick, const std::string &user, const std::string &channel)
    : server(server), port(port), nick(nick), user(user), channel(channel), sock(-1) {}

bool IRCClient::connectToServer()
{
    struct hostent *host = gethostbyname(server.c_str());
    if (!host)
    {
        std::cerr << "Failed to resolve server address.\n";
        return false;
    }

    struct sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);
    memset(&(server_addr.sin_zero), 0, 8);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        std::cerr << "Failed to create socket.\n";
        return false;
    }

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        std::cerr << "Connection failed!\n";
        close(sock);
        return false;
    }

    sendCommand("NICK " + nick);
    sendCommand("USER " + user + " 0 * :" + user);
    sendCommand("JOIN " + channel); // channel "#pokemon"
    return true;
}

void IRCClient::sendCommand(const std::string &command)
{
    std::string msg = command + "\r\n";
    send(sock, msg.c_str(), msg.length(), 0);
}

void IRCClient::receiveMessages(std::function<void(const std::string &)> onCommand)
{
    char buffer[512];
    while (true)
    {
        int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (bytes <= 0)
            break;

        buffer[bytes] = '\0';
        std::string line(buffer);
        size_t pos = 0;
        while ((pos = line.find("\r\n")) != std::string::npos)
        {
            std::string singleLine = line.substr(0, pos);
            if (singleLine.substr(0, 6) == "PING :")
            {
                sendCommand("PONG :" + singleLine.substr(6));
            }
            else if (singleLine.find("PRIVMSG") != std::string::npos)
            {
                size_t msgStart = singleLine.find(":", 1);
                if (msgStart != std::string::npos)
                {
                    std::string command = singleLine.substr(msgStart + 1);
                    onCommand(command);
                }
            }
            line.erase(0, pos + 2);
        }
    }
}

void IRCClient::disconnect()
{
    if (sock != -1)
    {
        close(sock);
        sock = -1;
    }
}