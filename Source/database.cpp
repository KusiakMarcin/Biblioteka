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


    //sqlite3 *Db; to jest zadeklarowane w database.h, w ten sposob przeciazasz(chyba) i korzystasz ze strumienia w funkcji a ten zadeklarowany w obiekcie zostaje
    //              niezainicjalizowany i nie da sie z niego korzystac
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
            "\"imie\" TEXT NOT NULL,"
            "\"nazwisko\" TEXT NOT NULL,"
            "\"adres\" VARCHAR(100) NOT NULL,"
            "\"nr_telefonu\" (9) NOT NULL UNIQUE,"
            "\"email\" TEXT UNIQUE,"
            "\"nr_karty\" INTEGER(6) NOT NULL UNIQUE,"
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
            "LENGTH(nr_karty) = 6"
            "));"

            "CREATE TABLE IF NOT EXISTS \"Wypożyczenia\" ("
            "\"id\" INTEGER NOT NULL,"
            "\"klienci_id\" INTEGER NOT NULL,"
            "\"ksiazki_id\" INTEGER NOT NULL,"
            "\"data_wydania\" DATETIME NOT NULL,"
            "\"data_zwrotu\" DATETIME NOT NULL,"
            "FOREIGN KEY(\"klienci_id\") REFERENCES \"Klienci\"(\"id\"),"
            "FOREIGN KEY(\"ksiazki_id\") REFERENCES \"Ksiazki\"(\"id\"));"

            "CREATE TABLE IF NOT EXISTS \"nr_karty_losowy\" ("
            "\"Field1\" INTEGER,"
            "\"value\" INTEGER NOT NULL,"
            "PRIMARY KEY(\"Field1\" AUTOINCREMENT));"

            "CREATE TABLE IF NOT EXISTS \"Ksiazki\" ("
            "\"id\" INTEGER,"
            "\"tytul\" TEXT NOT NULL,"
            "\"autorzy\" INT NOT NULL,"
            "\"liczba_egzemplarzy\" INTEGER NOT NULL,"
            "\"rok_wydania\" INTEGER NOT NULL,"
            "\"gatunek\" INT NOT NULL,"
            "\"liczba_wypozyczen\" INTEGER,"
            "FOREIGN KEY(\"autorzy\") REFERENCES \"Autorzy\"(\"id\"),"
            "FOREIGN KEY(\"gatunek\") REFERENCES \"Gatunki\"(\"id\"),"
            "PRIMARY KEY(\"id\" AUTOINCREMENT));";

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

bool database::addNewBook(const QString& tytul, int rokWydania , int liczbaEgzemplarzy, int autor, int gatunek) {
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO Ksiazki (id, tytul, autorzy_id, liczba_egzemplarzy, rok_wydania, gatunek_id, liczba_wypozyczen) VALUES (NULL, ?, ?, ?, ?, ?,0);";

    int rc = sqlite3_prepare_v2(Db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(Db));
        return false;
    }
    else{
        fprintf(stdout,"statement prepared");

    }
    sqlite3_bind_text(stmt, 1, tytul.toUtf8().constData(), tytul.length(), SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, autor);
    sqlite3_bind_int(stmt, 3, liczbaEgzemplarzy);
    sqlite3_bind_int(stmt, 4, rokWydania);
    sqlite3_bind_int(stmt, 5, gatunek);




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

bool database::editClient(const int id,const QString& imie, const QString& nazwisko, const QString& adres, int nrtel, const QString& email){
    sqlite3_stmt* stmt;
    const char* sql = "UPDATE klienci SET imie=\"?\", nazwisko=\"?\", adres=\"?\", nr_telefonu=\"?\", email=\"?\" WHERE id =?";
    int rc = sqlite3_prepare_v2(Db,sql,-1,&stmt,NULL);
    qDebug()<<rc;
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
    sqlite3_bind_int(stmt,6,id);


    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        qDebug() << "Failed to execute statement: %s\n" <<sqlite3_errmsg(this->Db);
        sqlite3_finalize(stmt);
        return false;
    }
    return true;
}

QVector<Clients> database::setDataClient(){
    QVector<Clients> datalist;
    const char* sql = "SELECT * FROM Klienci;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(Db,sql,-1,&stmt,NULL);
    if (rc != SQLITE_OK) {
        qDebug()<< sqlite3_errmsg(Db);
    }
    while ((sqlite3_step(stmt)) == SQLITE_ROW){
        Clients tmp;

        tmp.ClientID = sqlite3_column_int(stmt,0);
        tmp.Imie =(char*)sqlite3_column_text(stmt,1);
        tmp.Nazwisko =(char*)sqlite3_column_text(stmt,2);
        //qDebug()<<(char*)sqlite3_column_text(stmt,2);
        tmp.Adres =(char*)sqlite3_column_text(stmt,3);
        tmp.NumerTelefonu = sqlite3_column_int(stmt,4);
        tmp.Email=(char*)sqlite3_column_text(stmt,5);
        tmp.NumerKarty =sqlite3_column_int(stmt,6);
        datalist.append(tmp);
    }
    qDebug()<<"Clients List count"<<datalist.count();
    return datalist;
}
QVector<Books> database::setDataBook(){
    QVector<Books> datalist;
    const char* sql = "SELECT * FROM Ksiazki;";
    const char* sqlAuthor = "SELECT * FROM Autorzy WHERE id=?";
    const char* sqlGenre = "SELECT * FROM Gatunki WHERE id=?";
    sqlite3_stmt* stmt;
    sqlite3_stmt* getAuthor;
    sqlite3_stmt* getGenre;
    int rc = sqlite3_prepare_v2(Db,sql,-1,&stmt,NULL);

    if (rc != SQLITE_OK) {
        qDebug()<< sqlite3_errmsg(Db);
    }
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW){
        Books tmp;
        sqlite3_prepare_v2(Db,sqlAuthor,-1,&getAuthor,NULL);
        sqlite3_prepare_v2(Db,sqlGenre,-1,&getGenre,NULL);
        tmp.BookID = sqlite3_column_int(stmt,0);
        tmp.Title = (char*)sqlite3_column_text(stmt,1);
        sqlite3_bind_int(getAuthor,1,sqlite3_column_int(stmt,2));
        sqlite3_step(getAuthor);
        tmp.Author = (char*)sqlite3_column_text(getAuthor,1);

        tmp.Stock = sqlite3_column_int(stmt,3);
        tmp.RokWydania = sqlite3_column_int(stmt,4);
        sqlite3_bind_int(getGenre,1,sqlite3_column_int(stmt,5));
        sqlite3_step(getGenre);
        tmp.Genre = (char*)sqlite3_column_text(getGenre,1);

        tmp.NumberRented = sqlite3_column_int(getGenre,6);




        datalist.append(tmp);
    }
    qDebug()<<"Book list count"<<datalist.count();
    return datalist;
}
bool database::removeClient(int ClientID){
    const char* deleteQuery = "DELETE FROM KLienci WHERE id = ?;";
    sqlite3_stmt* stmtRemoveClient;
    if (sqlite3_prepare_v2(Db, deleteQuery, -1, &stmtRemoveClient, nullptr) != SQLITE_OK) {
        qDebug() << "Failed to prepare delete statement:" << sqlite3_errmsg(Db);
        return false;
    }

    sqlite3_bind_int(stmtRemoveClient, 1, ClientID);

    if (sqlite3_step(stmtRemoveClient) != SQLITE_DONE) {
        qDebug() << "Failed to execute delete statement:" << sqlite3_errmsg(Db);
        sqlite3_finalize(stmtRemoveClient);
        return false;
    }

    sqlite3_finalize(stmtRemoveClient);
    return true;
}

bool database::removeBook(int BookID){
    const char* deleteQuery = "DELETE FROM Ksiazki WHERE id = ?;";
    sqlite3_stmt* stmtRemoveClient;
    if (sqlite3_prepare_v2(Db, deleteQuery, -1, &stmtRemoveClient, nullptr) != SQLITE_OK) {
        qDebug() << "Failed to prepare delete statement:" << sqlite3_errmsg(Db);
        return false;
    }

    sqlite3_bind_int(stmtRemoveClient, 1, BookID);

    if (sqlite3_step(stmtRemoveClient) != SQLITE_DONE) {
        qDebug() << "Failed to execute delete statement:" << sqlite3_errmsg(Db);
        sqlite3_finalize(stmtRemoveClient);
        return false;
    }

    sqlite3_finalize(stmtRemoveClient);
    return true;
}

QVector<QString> database::setDataAuthor(){
    QVector<QString> datalist;
    const char* querry = "Select * from Autorzy";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(Db,querry,-1,&stmt,NULL);
    if(rc != SQLITE_OK){
        qDebug()<<sqlite3_errmsg(Db);

    }
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW){
        datalist.append((char*)sqlite3_column_text(stmt,1));
    }
    return datalist;
}

QVector<QString> database::setDataGenre(){
    QVector<QString> datalist;
    const char* querry = "Select * from Gatunki";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(Db,querry,-1,&stmt,NULL);
    if(rc != SQLITE_OK){
        qDebug()<<sqlite3_errmsg(Db);

    }
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW){
        datalist.append((char*)sqlite3_column_text(stmt,1));
    }
    return datalist;
}

