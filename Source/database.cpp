#include "Headers/database.h"
#include "Headers/sqlite3.h"
#include <stdio.h>

database::database() {}

database::~database() {
    if(Db){
        sqlite3_close(Db);
    }
}

bool database::initDatabase(){

    sqlite3 *Db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("C:\\Users\\adria\\Desktop\\Biblioteka-ui_databasebranch\\databases\\data.db", &Db);
    if(rc){
        fprintf(stderr, "Can't open database:  %s\n", sqlite3_errmsg(Db));
        return false;
        }
    else{
        fprintf(stderr, "Opened database succesfully\n");
        return true;
    }
}

bool database::addNewClient(const QString& imie, const QString& nazwisko, const QString& adres, int nrtel, const QString& email) {
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO Klienci (id, imie, nazwisko, adres, nr_telefonu, email) VALUES (NULL, '?', '?', '?', ?, '?');";

    int rc = sqlite3_prepare_v2(Db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(Db));
        return false;
    }
    else{
        fprintf(stdout,"statement prepared");

    }
    sqlite3_bind_text(stmt, 1, imie.toUtf8().constData(), imie.length(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, nazwisko.toUtf8().constData(), nazwisko.length(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, adres.toUtf8().constData(),adres.length(), SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, nrtel);
    sqlite3_bind_text(stmt, 5, email.toUtf8().constData(), email.length(), SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(Db));
        sqlite3_finalize(stmt);
        return false;
    }
    fprintf(stdout, "Record inserted successfully\n");

    sqlite3_finalize(stmt);
    return true;
}
