#include <vector>   
#include <sstream>
#include <fstream>

class File_manager
{
private:
    /* data */
public:
    File_manager(/* args */);
    ~File_manager();

    std::vector<std::pair<int, int>> parseSGF(const std::string& filePath);

};