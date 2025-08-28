// filepath: /irc-pokemon-game/irc-pokemon-game/src/game/pokemon.cpp
#include "pokemon.h"
#include <iostream>
#include <string>
#include <map>

Pokemon::Pokemon(const std::string &name, const std::string &type)
    : name(name), type(type), level(1), health(100) {}

Pokemon::Pokemon()
    : name(""), type(""), level(1), health(100) {}

void Pokemon::levelUp()
{
    level++;
    health += 10;
    std::cout << name << " leveled up to level " << level << "!\n";
}

void Pokemon::takeDamage(int damage)
{
    health -= damage;
    if (health < 0)
        health = 0;
    std::cout << name << " took " << damage << " damage! Health is now " << health << ".\n";
}

bool Pokemon::isFainted() const
{
    return health <= 0;
}

std::string Pokemon::getName() const
{
    return name;
}

std::string Pokemon::getType() const
{
    return type;
}

int Pokemon::getLevel() const
{
    return level;
}

// Trainer implementations
void Trainer::addPokemon(const Pokemon &pokemon)
{
    pokemons[pokemon.getName()] = pokemon;
}

void Trainer::showPokemons() const
{
    for (const auto &pair : pokemons)
    {
        std::cout << "Pokemon: " << pair.second.getName()
                  << ", Type: " << pair.second.getType()
                  << ", Level: " << pair.second.getLevel() << "\n";
    }
}
