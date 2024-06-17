#ifndef DATABASE_H
#define DATABASE_H
#include "sqlite3.h"
#include <QString>

//bool initDatabase(sqlite3 *Db);
//int callback(void* data, int argc, char** argv, char** azColName);
class database{
    //static int callback(void* data, int argc, char** argv, char** azColName);
public:
    database();
    bool initDatabase();
};

//const char *databaseMain = "databases/data.db";
//sqlite3 *Db;

#endif // DATABASE_H
