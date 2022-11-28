#include <cstdlib>
#include <iostream>
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

int DataBaseConn(string command){
    cout << endl;
    cout << "Running 'SELECT 'Hello World!' » AS _message'..." << endl;

    try {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;

        sql::ConnectOptionsMap connection_properties;
        connection_properties["hostName"] = "tcp://127.0.0.1:3306";
        connection_properties["userName"] = "root";
        connection_properties["password"] = "proyecto3";
        connection_properties["OPT_LOCAL_INFILE"] = 1;

        /* Create a connection */
        driver = get_driver_instance();
        con = driver->connect(connection_properties);
        /* Connect to the MySQL "prueba" database */
        con->setSchema("prueba");

        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT 'Hello World!' AS _message");
        while (res->next()) {
            cout << "\t... MySQL replies: ";
            /* Access column data by alias or column name */
            cout << res->getString("_message") << endl;
            cout << "\t... MySQL says it again: ";
            /* Access column data by numeric offset, 1 is the first column */
            cout << res->getString(1) << endl;
        }

        stmt->execute(command);

        delete res;
        delete stmt;
        delete con;
        return 0;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        return -1;
    }
}