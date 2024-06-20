#include <vector>   
#include <sstream>
#include <fstream>

class File_manager
{
private:
    std::string file_path;
public:
    File_manager(const std::string& file_path);
    ~File_manager();

    std::vector<std::pair<int, int>> parseSGF();

};