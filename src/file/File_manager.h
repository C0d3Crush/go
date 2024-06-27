#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

class File_manager
{
private:
    std::string file_path;
public:
    File_manager();
    ~File_manager();

    std::vector<std::pair<int, int>> parseSGF(const std::string& file_path);
    void saveSGF(const std::string& file_path, int board_size, float komi, const std::string& ruleset,
                 const std::string& result, const std::string& black_player, const std::string& white_player,
                 const std::vector<std::pair<int, int>>& moves);
};

#endif // FILE_MANAGER_H
