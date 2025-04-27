#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql/QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

class DatabaseManager
{
public:
    DatabaseManager();  // Constructor
    ~DatabaseManager(); // Destructor

    // Connect to the database
    bool connectToDatabase();

    // Check available database drivers (if needed)
    void checkDrivers();

    // Static method to get the database instance
    static QSqlDatabase getDatabase() {
        return db;  // Return the static db object
    }

private:
    static QSqlDatabase db; // Declare db as static so it can be accessed statically
};

#endif // DATABASEMANAGER_H

