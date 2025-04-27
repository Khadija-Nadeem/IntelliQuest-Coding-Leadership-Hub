#include "databasemanager.h"

// Initialize the static db object
QSqlDatabase DatabaseManager::db;

// Constructor
DatabaseManager::DatabaseManager() {}

// Destructor: Close the database connection if open
DatabaseManager::~DatabaseManager() {
    if (db.isOpen()) {
        db.close();
        qDebug() << "Database connection closed.";
    }
}

// Connect to the database
bool DatabaseManager::connectToDatabase() {
    // Create a database connection
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("intelliquest_coding_eleadership_hub");
    db.setUserName("root");
    db.setPassword("programmer._.2004");

    // Open the connection
    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError().text();
        return false;
    } else {
        qDebug() << "Database connection successful!";
        return true;
    }
}
