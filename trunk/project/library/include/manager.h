#ifndef managerInterface
#define managerInterface

#include <memory>
#include <vector>
#include <string>

template <class T, typename id>
class Manager
{
public:
    virtual void remove(const id&)=0;
    virtual const std::shared_ptr<T>& get(const id&) const=0;
    virtual std::string info() const=0;
    virtual std::vector<std::shared_ptr<T>> getAll() const=0;
    virtual ~Manager() = default;
};

#endif
