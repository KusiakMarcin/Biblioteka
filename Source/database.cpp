#include "Headers/database.h"
#include "Headers/sqlite3.h"
#include <stdio.h>
#include <QDebug>

database::database() {
    initDatabase();
}

database::~database() {
    if(Db){
        sqlite3_close(Db);
    }
}

bool database::initDatabase(){

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
        "CREATE TABLE IF NOT EXISTS \"Gatunki\" ("
        "   \"id\" INTEGER NOT NULL,"
        "   \"gatunek\" TEXT NOT NULL UNIQUE,"
        "   PRIMARY KEY(\"id\")"
        ");"
        "CREATE TABLE IF NOT EXISTS \"Autorzy\" ("
        "   \"id\" INTEGER NOT NULL,"
        "   \"name\" TEXT NOT NULL UNIQUE,"
        "   PRIMARY KEY(\"id\")"
        ");"
        "CREATE TABLE IF NOT EXISTS \"nr_karty_losowy\" ("
        "   \"Field1\" INTEGER,"
        "   \"value\" INTEGER NOT NULL,"
        "   PRIMARY KEY(\"Field1\" AUTOINCREMENT)"
        ");"
        "CREATE TABLE IF NOT EXISTS \"Wypożyczenia\" ("
        "   \"id\" INTEGER NOT NULL,"
        "   \"klienci_id\" INTEGER NOT NULL,"
        "   \"ksiazki_id\" INTEGER NOT NULL,"
        "   \"data_wydania\" DATETIME NOT NULL,"
        "   \"data_zwrotu\" DATETIME,"
        "   \"termin_oddania\" DATETIME NOT NULL,"
        "   FOREIGN KEY(\"klienci_id\") REFERENCES \"Klienci\"(\"id\"),"
        "   FOREIGN KEY(\"ksiazki_id\") REFERENCES \"Ksiazki\"(\"id\"),"
        "   PRIMARY KEY(\"id\")"
        ");"
        "CREATE TABLE IF NOT EXISTS \"Kwota_oplaty\" ("
        "   \"oplata_dzienna\" REAL"
        ");"
        "CREATE TABLE IF NOT EXISTS \"Naliczone_oplaty\" ("
        "   \"id\" INTEGER,"
        "   \"wypozyczenia_id\" INTEGER,"
        "   \"dni_po_terminie\" INTEGER,"
        "   \"oplata\" REAL,"
        "   \"czy_oplacone\" INTEGER DEFAULT 0,"
        "   PRIMARY KEY(\"id\" AUTOINCREMENT)"
        ");"
        "CREATE TABLE IF NOT EXISTS \"Ksiazki\" ("
        "   \"opis\" TEXT,"
        "   \"id\" INTEGER,"
        "   \"tytul\" TEXT NOT NULL,"
        "   \"autorzy_id\" INTEGER NOT NULL,"
        "   \"czy_wypozyczone\" NUMERIC NOT NULL,"
        "   \"rok_wydania\" INTEGER NOT NULL,"
        "   \"gatunek_id\" INTEGER NOT NULL,"
        "   \"liczba_wypozyczen\" INTEGER,"
        "   FOREIGN KEY(\"gatunek_id\") REFERENCES \"Gatunki\"(\"id\"),"
        "   FOREIGN KEY(\"autorzy_id\") REFERENCES \"Autorzy\"(\"id\"),"
        "   PRIMARY KEY(\"id\" AUTOINCREMENT)"
        ");"
        "CREATE VIEW IF NOT EXISTS W_Ksiazki AS "
        "SELECT Ksiazki.id AS id, "
        "   Ksiazki.tytul AS tytul, "
        "   Autorzy.name AS Autor, "
        "   Ksiazki.rok_wydania AS rok_wydania, "
        "   Gatunki.gatunek AS gatunek, "
        "   Ksiazki.czy_wypozyczone AS czy_wypozyczone, "
        "   count(Ksiazki.tytul) AS ilosc_egzemplarzy "
        "FROM Ksiazki "
        "JOIN Autorzy ON Ksiazki.autorzy_id = Autorzy.id "
        "JOIN Gatunki ON Ksiazki.gatunek_id = Gatunki.id "
        "GROUP BY Ksiazki.tytul;"
        "CREATE VIEW IF NOT EXISTS W_opoznienia AS "
        "SELECT "
        "   Wypożyczenia.id AS wypozyczenia_id, "
        "   Wypożyczenia.klienci_id as klienci_id, "
        "   Klienci.imie as imie_klienta, "
        "   Klienci.nazwisko as nazwisko_klienta, "
        "   Wypożyczenia.ksiazki_id AS ksiazki_id, "
        "   CAST(julianday('now') - julianday(Wypożyczenia.termin_oddania) AS INTEGER) as dni_po_terminie, "
        "   round((julianday('now') - julianday(Wypożyczenia.termin_oddania)) * 0.10, 2) as oplata "
        "FROM Wypożyczenia "
        "JOIN Klienci ON Wypożyczenia.klienci_id = Klienci.id "
        "WHERE Wypożyczenia.data_zwrotu IS NULL "
        "AND julianday('now') > julianday(Wypożyczenia.termin_oddania);"
        "CREATE VIEW IF NOT EXISTS W_nieoplacone as "
        "SELECT Naliczone_oplaty.id as id, "
        "   Wypożyczenia.id as wypozyczenia_id, "
        "   Klienci.id as klienci_id, "
        "   Klienci.imie as imie_klienta, "
        "   Klienci.nazwisko as nazwisko_klienta, "
        "   Naliczone_oplaty.oplata as oplata "
        "FROM Naliczone_oplaty "
        "JOIN Wypożyczenia ON Naliczone_oplaty.wypozyczenia_id = Wypożyczenia.id "
        "JOIN Klienci ON Wypożyczenia.klienci_id = Klienci.id "
        "WHERE Naliczone_oplaty.czy_oplacone == 0;";

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
        qDebug() << "Failed to execute statement: %s\n" <<sqlite3_errmsg(this->Db);
        sqlite3_finalize(stmt);
        return false;
    }
    qDebug() <<"Record inserted successfully\n";

    sqlite3_finalize(stmt);
    return true;
}



