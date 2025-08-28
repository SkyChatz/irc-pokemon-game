#include <iostream>
#include <fstream>
#include <string>
#include <map>

std::map<std::string, std::string> load_config(const std::string& filename) {
    std::ifstream file(filename);
    std::map<std::string, std::string> config;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        size_t eq = line.find('=');
        if (eq != std::string::npos) {
            config[line.substr(0, eq)] = line.substr(eq + 1);
        }
    }
    return config;
}