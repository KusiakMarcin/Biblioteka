#include "Headers/database.h"
#include "Headers/sqlite3.h"
#include <stdio.h>

/*

int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

*/
database::database() {}

bool database::initDatabase(){
    sqlite3 *Db;
    char buffer[PATH_MAX];
    getcwd(buffer, sizeof(buffer));
    qDebug()<<buffer;
    int rc;
    /*std::ifstream ifile(".\\databases\\data.db");
    if (!ifile) {
        fprintf(stderr, "Can't find the database file: ./databases/data.db\n");
        return false;
    }*/
    rc = sqlite3_open("data.db", &Db);
    if(rc){
        qDebug() << "Can't open database"<<sqlite3_errmsg(Db);
        //fprintf(stderr, "Can't open database:  %s\n", sqlite3_errmsg(Db));
        return false;
        }
    else{
        qDebug() <<"Opened database succesfully\n";
        return true;
    }
}
