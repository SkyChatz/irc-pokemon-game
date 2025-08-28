#include "game_logic.h"
#include "pokemon.h"
#include <iostream>
#include <map>
#include <string>
#include <sstream> // Include sstream for istringstream

GameLogic::GameLogic(IRCClient *irc_client, const std::string &channel)
    : irc_client_(irc_client), channel_(channel) {}

void GameLogic::startGame()
{
    std::cout << "Welcome to the IRC Pok�mon Game!" << std::endl;
}

void GameLogic::handle_command(const std::string &command)
{
    // Example: "!catch Pikachu Electric"
    if (command.rfind("!catch ", 0) == 0)
    {
        std::istringstream iss(command.substr(7));
        std::string name, type;
        iss >> name >> type;
        if (name.empty() || type.empty())
        {
            irc_client_->sendCommand("PRIVMSG " + channel_ + " :Usage: !catch <name> <type>");
            return;
        }
        std::string playerNick = "Player";
        playerPokemons[playerNick] = Pokemon(name, type);
        irc_client_->sendCommand("PRIVMSG " + channel_ + " :" + playerNick + " caught a " + name + " (" + type + ")!");
    }
    else if (command == "!help")
    {
        std::string helpMsg = "Available commands: !help, !catch, !battle, !quit, etc.";
        irc_client_->sendCommand("PRIVMSG " + channel_ + " :" + helpMsg);
    }
    else if (command.rfind("!battle ", 0) == 0)
    {
        std::string opponentNick = command.substr(8);
        std::string playerNick = "Player";
        if (playerPokemons.find(playerNick) == playerPokemons.end())
        {
            irc_client_->sendCommand("PRIVMSG " + channel_ + " :You need to catch a Pok�mon first!");
            return;
        }
        if (playerPokemons.find(opponentNick) == playerPokemons.end())
        {
            irc_client_->sendCommand("PRIVMSG " + channel_ + " :" + opponentNick + " has no Pok�mon!");
            return;
        }
        battle(playerPokemons[playerNick], playerPokemons[opponentNick]);
    }
    else if (command == "!quit")
    {
        irc_client_->sendCommand("PRIVMSG " + channel_ + " :Use !quit in your client to leave the channel.");
    }
    else
    {
        irc_client_->sendCommand("PRIVMSG " + channel_ + " :Unknown command. Type !help for a list of commands.");
    }
}

void GameLogic::handlePlayerAction(const std::string &action)
{
    if (action == "attack")
    {
        irc_client_->sendCommand("PRIVMSG " + channel_ + " :You attacked! (Feature coming soon)");
    }
    else if (action == "catch")
    {
        irc_client_->sendCommand("PRIVMSG " + channel_ + " :You tried to catch a Pok�mon! (Feature coming soon)");
    }
    else if (action == "run")
    {
        irc_client_->sendCommand("PRIVMSG " + channel_ + " :You ran away! (Feature coming soon)");
    }
    else
    {
        irc_client_->sendCommand("PRIVMSG " + channel_ + " :Unknown action. Try 'attack', 'catch', or 'run'.");
    }
}

void GameLogic::battle(Pokemon &playerPokemon, Pokemon &opponentPokemon)
{
    // battle
    irc_client_->sendCommand("PRIVMSG " + channel_ + " :Battle started between " +
                             playerPokemon.getName() + " and " + opponentPokemon.getName() + "!");

    // attacks first
    int playerAttack = 10;
    opponentPokemon.takeDamage(playerAttack);
    irc_client_->sendCommand("PRIVMSG " + channel_ + " :" +
                             playerPokemon.getName() + " attacks " + opponentPokemon.getName() +
                             " for " + std::to_string(playerAttack) + " damage!");

    if (opponentPokemon.isFainted())
    {
        irc_client_->sendCommand("PRIVMSG " + channel_ + " :" +
                                 opponentPokemon.getName() + " fainted! " + playerPokemon.getName() + " wins!");
        return;
    }

    // Opponent attacks back
    int opponentAttack = 8;
    playerPokemon.takeDamage(opponentAttack);
    irc_client_->sendCommand("PRIVMSG " + channel_ + " :" +
                             opponentPokemon.getName() + " attacks " + playerPokemon.getName() +
                             " for " + std::to_string(opponentAttack) + " damage!");

    if (playerPokemon.isFainted())
    {
        irc_client_->sendCommand("PRIVMSG " + channel_ + " :" +
                                 playerPokemon.getName() + " fainted! " + opponentPokemon.getName() + " wins!");
        return;
    }
}

void GameLogic::levelUp(Pokemon &pokemon)
{
    pokemon.levelUp();
    irc_client_->sendCommand("PRIVMSG " + channel_ + " :" +
                             pokemon.getName() + " leveled up to level " + std::to_string(pokemon.getLevel()) + "!");
}

void GameLogic::displayStatus(const Pokemon &pokemon)
{
    std::string status = pokemon.getName() + " | Type: " + pokemon.getType() +
                         " | Level: " + std::to_string(pokemon.getLevel());
    irc_client_->sendCommand("PRIVMSG " + channel_ + " :" + status);
}

void GameLogic::update()
{
}