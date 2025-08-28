#include <iostream>
#include <map>
#include <string>
#include "irc/irc_client.h"
#include "game/game_logic.h"
#include "utils/config.h"

#define IRC_POKEMON_GAME_VERSION "1.0.0-PIBOT"

int main()
{
    std::cout << "IRC Pokémon Game Version: " << IRC_POKEMON_GAME_VERSION << std::endl;

    // Load configuration
    auto config = load_config("bot.conf");
    std::string server = config["server"];
    int port = std::stoi(config["port"]);
    std::string nick = config["nick"];
    std::string user = config["user"];
    std::string channel = config["channel"];

    // Initialize IRC client
    IRCClient irc_client(server, port, nick, user, channel);
    if (!irc_client.connectToServer())
    { // Use correct function name
        std::cerr << "Failed to connect to IRC server." << std::endl;
        return 1;
    }

    GameLogic game_logic(&irc_client, channel);

    game_logic.startGame();
    irc_client.sendCommand("PRIVMSG " + channel + " :Welcome to the IRC Pok�mon Game!");

    // Start game loop
    while (true)
    {
        irc_client.receiveMessages([&](const std::string &command)
                                   { game_logic.handle_command(command); });

        game_logic.update();

        std::string command;
        std::getline(std::cin, command);
        if (command == "!quit")
        {
            irc_client.sendCommand("QUIT :Goodbye.");
            break;
        }
        else
        {
            game_logic.handle_command(command);
        }
    }

    return 0;
}