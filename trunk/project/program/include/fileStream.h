#ifndef fileStreamHeader
#define fileStreamHeader

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <memory>

class Position;
typedef std::shared_ptr<Position> positionPtr;

namespace input
{
    std::vector<positionPtr> loadPositions();
    void employeeRepository(const std::string&);
    void desiredSchedule(const std::string&);
    void schedule(const std::string&);
    void teamRepository(const std::string&);
    void teamSchedule(const std::string&);
}

namespace output
{
    void employeeRepository(const std::string&);
    void desiredSchedule(const std::string&);
    void schedule(const std::string&);
    void teamRepository(const std::string&);
    void teamSchedule(const std::string&);
}

template<typename T>
std::vector<T> cellToRawValues(std::string &chain, char separator)
{
    std::vector<T> output;
    std::replace(chain.begin(), chain.end(), separator, ' ');
    std::stringstream stream(chain);
    T temp;
    while (stream >> temp)
        output.push_back(temp);
    return output;
}

#endif
