#ifndef fileStreamHeader
#define fileStreamHeader

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <memory>
#include <stdexcept>

class FileException : public std::logic_error
{
private:
    std::string path;
public:
    explicit FileException(const std::string &message, std::string path);
    virtual std::string message() const;
};

class PathException : public FileException
{
public:
    explicit PathException(const std::string &message, const std::string &path);
};

class DataException : public FileException
{
public:
    explicit DataException(const std::string &message, const std::string &path);
    std::string message() const override;
};

class Position;
typedef std::shared_ptr<Position> positionPtr;

namespace input
{
    std::vector<positionPtr> loadPositions();
    void employeeRepository(const std::string&) noexcept(false);
    void desiredSchedule(const std::string&) noexcept(false);
    void teamRepository(const std::string&) noexcept(false);
    void teamSchedule(const std::string&) noexcept(false);
}

namespace output
{
    void employeeRepository(const std::string&) noexcept(false);
    void desiredSchedule(const std::string&) noexcept(false);
    void schedule(const std::string&) noexcept(false);
    void teamRepository(const std::string&) noexcept(false);
    void teamSchedule(const std::string&) noexcept(false);
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
