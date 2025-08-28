#ifndef INDEX_H
#define INDEX_H

enum class PokemonType {
    FIRE,
    WATER,
    GRASS,
    ELECTRIC,
    GROUND,
    FLYING,
    PSYCHIC,
    ICE,
    ROCK,
    BUG,
    GHOST,
    NORMAL,
    FIGHTING,
    FAIRY,
    DARK,
    STEEL,
    POISON
};

enum class GameState {
    LOBBY,
    IN_GAME,
    GAME_OVER
};

struct Pokemon {
    std::string name;
    PokemonType type;
    int level;
    int health;
    int attack;
    int defense;
};

#endif // INDEX_H