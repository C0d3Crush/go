#include "File_manager.h"

#include <iostream>

File_manager::File_manager(const std::string& value)
{
    file_path = value;
}

File_manager::~File_manager()
{
}

std::vector<std::pair<int, int>> File_manager::parseSGF()
{
    std::vector<std::pair<int, int>> moves;

    std::ifstream file(file_path);
    if (!file) {
        std::cerr << "Failed to open SGF file: " << file_path << std::endl;
        return moves;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.find("SZ[") != std::string::npos) {
            int startPos = line.find("SZ[") + 3;
            int endPos = line.find("]", startPos);
            int boardSize = std::stoi(line.substr(startPos, endPos - startPos));
            std::cout << "Board Size: " << boardSize << std::endl;
        } else if (line.find("KM[") != std::string::npos) {
            int startPos = line.find("KM[") + 3;
            int endPos = line.find("]", startPos);
            float komi = std::stof(line.substr(startPos, endPos - startPos));
            std::cout << "Komi: " << komi << std::endl;
        } else if (line.find("RU[") != std::string::npos) {
            int startPos = line.find("RU[") + 3;
            int endPos = line.find("]", startPos);
            std::string ruleset = line.substr(startPos, endPos - startPos);
            std::cout << "Ruleset: " << ruleset << std::endl;
        } else if (line.find("RE[") != std::string::npos) {
            int startPos = line.find("RE[") + 3;
            int endPos = line.find("]", startPos);
            std::string result = line.substr(startPos, endPos - startPos);
            std::cout << "Result: " << result << std::endl;
        } else if (line.find("PB[") != std::string::npos) {
            int startPos = line.find("PB[") + 3;
            int endPos = line.find("]", startPos);
            std::string blackPlayer = line.substr(startPos, endPos - startPos);
            std::cout << "Black Player: " << blackPlayer << std::endl;
        } else if (line.find("PW[") != std::string::npos) {
            int startPos = line.find("PW[") + 3;
            int endPos = line.find("]", startPos);
            std::string whitePlayer = line.substr(startPos, endPos - startPos);
            std::cout << "White Player: " << whitePlayer << std::endl;
        } else if (line.find(";B[") != std::string::npos || line.find(";W[") != std::string::npos) {
            size_t pos = 0;
            while ((pos = line.find(";")) != std::string::npos) {
                std::string move = line.substr(pos + 1, 5); // Expecting format like "B[ab]"
                line.erase(0, pos + 6); // Erase up to the next move

                if (move.size() >= 4 && (move[0] == 'B' || move[0] == 'W')) {
                    char player = move[0];
                    char x = move[2];
                    char y = move[3];
                    if (x == ']' || y == ']') {
                        // Pass move
                        moves.push_back({-1, -1});
                    } else {
                        moves.push_back({x - 'a', y - 'a'});
                    }
                }
            }
        }
    }
    return moves;
}