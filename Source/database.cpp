#include "Headers/database.h"
#include "Headers/sqlite3.h"
#include <stdio.h>
#include <QDebug>

database::database() {

}

database::~database() {
    if(Db){
        sqlite3_close(Db);
    }
}

bool database::initDatabase(){


    sqlite3 *Db;
    const char *filename = "data.db";
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(filename, &Db);
    if(rc){
        fprintf(stderr, "Can't open database:  %s\n", sqlite3_errmsg(Db));
        return false;
        }
    else{
        fprintf(stderr, "Opened database succesfully\n");
    }

        const char *sqlCreateTables =
            "CREATE TABLE IF NOT EXISTS \"Klienci\" ("
            "\"id\" integer primary key NOT NULL UNIQUE,"
            "\"imie\" VARCHAR(50) NOT NULL,"
            "\"nazwisko\" VARCHAR(50) NOT NULL,"
            "\"adres\" VARCHAR(100) NOT NULL,"
            "\"nr_telefonu\" VARCHAR(9) NOT NULL UNIQUE,"
            "\"email\" TEXT UNIQUE,"
            "\"nr_karty\" INTEGER(6) UNIQUE,"
            "CHECK ("
            "email LIKE '%_@_%._%' AND "
            "LENGTH(email) - LENGTH(REPLACE(email, '@', '')) = 1 AND "
            "SUBSTR(LOWER(email), 1, INSTR(email, '.') - 1) NOT GLOB '*[^@0-9a-z]*' AND "
            "SUBSTR(LOWER(email), INSTR(email, '.') + 1) NOT GLOB '*[^a-z]*'"
            "),"
            "CHECK ("
            "LENGTH (nr_telefonu) = 9"
            "),"
            "CHECK ("
            "LENGTH (nr_karty) = 6"
            "));"

            "CREATE TABLE IF NOT EXISTS \"Wypożyczenia\" ("
            "\"id\" INTEGER NOT NULL,"
            "\"klienci_id\" INTEGER NOT NULL,"
            "\"ksiazki_id\" INTEGER NOT NULL,"
            "\"data_wydania\" DATETIME NOT NULL,"
            "\"data_zwrotu\" DATETIME NOT NULL,"
            "\"termin_oddania\" DATETIME NOT NULL,"
            "FOREIGN KEY(\"klienci_id\") REFERENCES \"Klienci\"(\"id\"),"
            "FOREIGN KEY(\"ksiazki_id\") REFERENCES \"Ksiazki\"(\"id\"));"

            "CREATE TABLE IF NOT EXISTS \"Gatunki\" ("
            "\"id\" integer NOT NULL,"
            "\"gatunek\" TEXT NOT NULL UNIQUE,"
            "PRIMARY KEY(\"id\"));"

            "CREATE TABLE IF NOT EXISTS \"Autorzy\" ("
            "\"id\" integer NOT NULL,"
            "\"name\" TEXT NOT NULL UNIQUE,"
            "PRIMARY KEY(\"id\"));"

            "CREATE TABLE IF NOT EXISTS \"nr_karty_losowy\" ("
            "\"Field1\" INTEGER,"
            "\"value\" INTEGER NOT NULL,"
            "PRIMARY KEY(\"Field1\" AUTOINCREMENT));"

            "CREATE TABLE IF NOT EXISTS \"Ksiazki\" ("
            "\"opis\" TEXT,"
            "\"id\" INTEGER,"
            "\"tytul\" TEXT NOT NULL,"
            "\"autorzy_id\" INTEGER NOT NULL,"
            "\"czy_wypozyczone\" INTEGER NOT NULL,"
            "\"rok_wydania\" INTEGER NOT NULL,"
            "\"gatunek_id\" INTEGER NOT NULL,"
            "\"liczba_wypozyczen\" INTEGER,"
            "FOREIGN KEY(\"autorzy_id\") REFERENCES \"Autorzy\"(\"id\"),"
            "FOREIGN KEY(\"gatunek_id\") REFERENCES \"Gatunki\"(\"id\"),"
            "PRIMARY KEY(\"id\" AUTOINCREMENT));"

            "CREATE VIEW IF NOT EXISTS W_Ksiazki AS "
            "SELECT Ksiazki.id AS id,"
            "Ksiazki.tytul AS tytul,"
            "Autorzy.name AS Autor,"
            "Ksiazki.rok_wydania AS rok_wydania,"
            "Gatunki.gatunek AS gatunek,"
            "Ksiazki.czy_wypozyczone AS czy_wypozyczone,"
            "count(Ksiazki.tytul) AS ilosc_egzemplarzy "
            "FROM Ksiazki "
            "JOIN Autorzy ON Ksiazki.autorzy_id = Autorzy.id "
            "JOIN Gatunki ON Ksiazki.gatunek_id = Gatunki.id "
            "GROUP BY Ksiazki.tytul;";

     rc = sqlite3_exec(Db, sqlCreateTables, 0, 0, &zErrMsg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            return false;
        } else {
            fprintf(stdout, "Tables created successfully\n");
            return true;
        }
}

bool database::addNewClient(const QString& imie, const QString& nazwisko, const QString& adres, int nrtel, const QString& email) {
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO Klienci (id, imie, nazwisko, adres, nr_telefonu, email) VALUES (NULL, ?, ?, ?, ?, ?);";

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



