#ifndef WORKSCHEDULER_CONNECTIONPROVIDER_H
#define WORKSCHEDULER_CONNECTIONPROVIDER_H

#include <cppconn/driver.h>
#include <string>

class ConnectionProvider {
private:
    sql::Driver* driver;
    sql::Connection* con;

public:
    ConnectionProvider(const ConnectionProvider&) = delete;
    ConnectionProvider& operator=(const ConnectionProvider&) = delete;
    ConnectionProvider(const std::string& hostName,
        const std::string& userName,
        const std::string& password,
        const std::string& dbName) noexcept(false);
    ~ConnectionProvider();
    sql::Connection* getConnection() const;
};

#endif // WORKSCHEDULER_CONNECTIONPROVIDER_H
