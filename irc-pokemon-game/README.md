# IRC Pokémon Game

## Overview
The IRC Pokémon Game is an interactive game that allows players to engage in Pokémon battles and adventures through an IRC (Internet Relay Chat) interface. Players can join channels, interact with each other, and command their Pokémon in battles.

## See the Bot in Action!
Want to see a real bot running?  
Join us at the IRC server:  
```
/server irc.skychatz.org 7000
```
and connect to the channel:  
```
/join #Pokemon
```

## Setup Instructions
1. **Clone the Repository**
   ```bash
   git clone <repository-url>
   cd irc-pokemon-game
   ```

2. **Install Dependencies**
   Ensure you have CMake and a C++ compiler installed on your system.

3. **Build the Project**
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

4. **Configuration**
   Edit the `bot.conf` file to set your IRC server details, port, nickname, and channel.

## Gameplay
- Players can join the game by connecting to the specified IRC channel.
- Use commands like `!help` to see available commands.
- Players can battle Pokémon, level them up, and interact with other players.

## Contribution Guidelines
Contributions are welcome! Please fork the repository and submit a pull request with your changes. Ensure that your code adheres to the project's coding standards and includes appropriate tests.

## License
This project is licensed under the MIT License. See the LICENSE file for more details.