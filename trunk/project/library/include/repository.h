#ifndef repositoryClass
#define repositoryClass

#include <memory>
#include <string>
#include <vector>

template<class T,typename Id>
class Repository{
public:
    virtual void add(const std::shared_ptr<T>&)= 0;
    virtual void remove(const Id&)=0;
    virtual const std::vector<std::shared_ptr<T>>& getAll() const= 0;
    virtual const std::shared_ptr<T>& get(const Id&) const= 0;
    virtual std::string info() const= 0;
    virtual ~Repository()= default;
};


#endif
