#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <map>
#include <string>
#include <vector>
#include "pokemon.h"
#include "../irc/irc_client.h"

class GameLogic
{
public:
    GameLogic(IRCClient *irc_client, const std::string &channel);
    void startGame();
    void handlePlayerAction(const std::string &action);
    void battle(Pokemon &playerPokemon, Pokemon &opponentPokemon);
    void levelUp(Pokemon &pokemon);
    void displayStatus(const Pokemon &pokemon);
    void displayGameState() const;
    void update();
    void handle_command(const std::string &command);

private:
    IRCClient *irc_client_;
    std::string channel_;
    std::map<std::string, Pokemon> playerPokemons; // key: player nick, value: their Pokemon
};

#endif