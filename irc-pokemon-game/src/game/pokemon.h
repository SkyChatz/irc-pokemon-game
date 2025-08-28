#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <vector>
#include <map>

class Pokemon {
public:
    Pokemon();
    Pokemon(const std::string& name, const std::string& type);
    void levelUp();
    void takeDamage(int damage);
    bool isFainted() const;
    std::string getName() const;
    std::string getType() const;
    int getLevel() const;
    
private:
    std::string name;
    std::string type;
    int level;
    int health;
};

class Trainer {
public:
    Trainer(const std::string& name);
    
    void addPokemon(const Pokemon& pokemon);
    void removePokemon(const std::string& name);
    void showPokemons() const;
    
private:
    std::string name;
    std::map<std::string, Pokemon> pokemons;
};

#endif // POKEMON_H