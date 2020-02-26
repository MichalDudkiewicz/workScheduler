#include "database/connectionProvider.h"
#include <cppconn/exception.h>

ConnectionProvider::ConnectionProvider(const std::string& hostName,
                                       const std::string& userName,
                                       const std::string& password,
                                       const std::string& dbName) try
  : driver(get_driver_instance())
  , con(driver->connect(hostName, userName, password)) {
  /* Connect to the MySQL database */
  con->setSchema(dbName);
} catch (sql::SQLException& e) {
  std::cout << "# ERR: SQLException in " << __FILE__;
  std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
  std::cout << "# ERR: " << e.what();
  std::cout << " (MySQL error code: " << e.getErrorCode();
  std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
}

ConnectionProvider::~ConnectionProvider()
{
  delete con;
}

sql::Connection*
ConnectionProvider::getConnection() const
{
  return con;
}
