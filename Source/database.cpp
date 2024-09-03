#include "Headers/database.h"
#include "Headers/sqlite3.h"
#include <stdio.h>
#include <QDebug>
#include <stdlib.h>

QVector<QString> tables = {"Klienci", "Ksiazki","Wypozyczenia"};
QVector<QString> clients={"id","imie","nazwisko","adres","nr_telefonu","email","nr_karty"};
QVector<QString> books = {"id","tytul","autorzy_id","liczba_egzemplarzy","rok_wydania","gatunek_id","liczba_wypozyczen"};
QVector<QString> rentals= {"id","klienci_id","ksiazki_id","data_zwrotu","data_wydania"};


database::database() {

    initDatabase();
}

database::~database() {
    if(Db){
        sqlite3_close(Db);
    }
}

bool database::initDatabase(){          //incjalizuje połączenie z bazą danych, jeśli baza nie istnieje tworzy nowa baze (patrz sqlCreateTables)



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

            "CREATE TABLE IF NOT EXISTS \"Wypozyczenia\" ("
            "\"id\" INTEGER NOT NULL,"
            "\"klienci_id\" INTEGER NOT NULL,"
            "\"ksiazki_id\" INTEGER NOT NULL,"
            "\"data_wydania\" DATETIME NOT NULL,"
            "\"data_zwrotu\" DATETIME NOT NULL,"
            "FOREIGN KEY(\"klienci_id\") REFERENCES \"Klienci\"(\"id\"),"
            "FOREIGN KEY(\"ksiazki_id\") REFERENCES \"Ksiazki\"(\"id\"));"
            "PRIMARY KEY(\"id\" AUTOINCREMENT));"

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
            "PRIMARY KEY(\"id\" AUTOINCREMENT));"
            "CREATE TRIGGER \"increment_rented\""
            "AFTER INSERT ON Wypozyczenia"
            "FOR EACH ROW"
            "BEGIN"
            "IF (SELECT COUNT(*) FROM Wypozyczenia WHERE klienci_id = NEW.klienci_id) = 1 THEN"
            "UPDATE users"
            "SET reference_count = reference_count + 1"
            "WHERE user_id = NEW.user_id;"
            "END IF;"
            "END;"
            "CREATE TRIGGER decrement_liczba_wypozyczen"
            "AFTER DELETE ON Wypozyczenia"
            "FOR EACH ROW"
            "BEGIN"
            "UPDATE Ksiazki"
            "SET liczba_wypozyczen = liczba_wypozyczen - 1"
            "WHERE id = OLD.ksiazka_id;"
            "END;";

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
    qDebug() <<rc;
    if (rc != SQLITE_DONE) {
        qDebug() << "Failed to execute statement: %s\n" <<sqlite3_errmsg(this->Db);
        sqlite3_finalize(stmt);
        return false;
    }
    qDebug() <<"Record inserted successfully\n";

    sqlite3_finalize(stmt);
    return true;
}

bool database::addNewBook(const QString& tytul, int rokWydania , int liczbaEgzemplarzy, const QString& autor, const QString& gatunek) {
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
    sqlite3_bind_text(stmt, 2, autor.toUtf8().constData(), tytul.length(), SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, liczbaEgzemplarzy);
    sqlite3_bind_int(stmt, 4, rokWydania);
    sqlite3_bind_text(stmt, 5, gatunek.toUtf8().constData(), tytul.length(), SQLITE_TRANSIENT);




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

bool database::addRental(int clientID,int bookID,QDate borrowDate, QDate returnDate){
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO Wypozyczenia (id,klienci_id,ksiazki_id,data_zwrotu,data_wydania) VALUES (NULL,?,?,?,?)";

    int rc = sqlite3_prepare_v2(Db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(Db));
        return false;
    }
    else{
        fprintf(stdout,"statement prepared");

    }
    sqlite3_bind_int(stmt, 1, clientID);
    sqlite3_bind_int(stmt,2,bookID);
    sqlite3_bind_text(stmt,3,returnDate.toString("yyyy-MM-dd").toUtf8().constData(),10,SQLITE_TRANSIENT);
    qDebug()<<"return"<<returnDate.toString("yyyy-MM-dd").toUtf8().constData();
    sqlite3_bind_text(stmt,4,borrowDate.toString("yyyy-MM-dd").toUtf8().constData(),10,SQLITE_TRANSIENT);
    qDebug()<<"borrow"<<borrowDate.toString("yyyy-MM-dd").toUtf8().constData();
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        qDebug() << "Failed to execute statement: %s\n" <<sqlite3_errmsg(Db);
        sqlite3_finalize(stmt);
        return false;
    }
    qDebug() <<"Record inserted successfully\n";

    sqlite3_finalize(stmt);
    return true;
}

bool database::editElement(int id,const int table, const int column,const QString value){
    sqlite3_stmt* stmt;
    qDebug()<<id<<table<<column<<value;
    QString sql = "UPDATE  SET  = ? WHERE id =?;";
    switch(table){
        case 0: sql.insert(12,clients[column]);
        break;
        case 1: sql.insert(12,books[column]);
        break;
        case 2: sql.insert(12,rentals[column]);
        break;
    }


    sql.insert(7,tables[table]);
    const char* querry = sql.toUtf8();
    qDebug()<< querry;
    int rc = sqlite3_prepare_v2(Db,querry,-1,&stmt,NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(Db));
        qDebug()<<sqlite3_errmsg(Db);
        return false;
    }
    else{
        fprintf(stdout,"statement prepared");
        qDebug()<<"ok";

    }
    sqlite3_bind_text(stmt,1,value.toUtf8().constData(),value.length(),SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt,2,id);


    rc = sqlite3_step(stmt);
    qDebug()<<sqlite3_errmsg(Db)<<rc;
    if (rc != SQLITE_DONE) {
        qDebug() << "Failed to execute statement: %s\n" <<sqlite3_errmsg(this->Db);
        sqlite3_finalize(stmt);
        return false;
    }
    return true;
}

bool database::editElement(int id,const int table, const int column,int value){
    sqlite3_stmt* stmt;
    QString sql = "UPDATE  SET  = ? WHERE id =?;";
    switch(table){
    case 0: sql.insert(12,clients[column]);
        break;
    case 1: sql.insert(12,books[column]);
        break;
    case 2: sql.insert(12,rentals[column]);
        break;
    }

    sql.insert(7,tables[table]);
    const char* querry = sql.toUtf8();
    qDebug()<<querry;
    int rc = sqlite3_prepare_v2(Db,querry,-1,&stmt,NULL);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(Db));
        qDebug()<<sqlite3_errmsg(Db);
        return false;
    }
    else{
        fprintf(stdout,"statement prepared");

    }

    sqlite3_bind_int(stmt,1,value);
    sqlite3_bind_int(stmt,2,id);



    rc = sqlite3_step(stmt);
    qDebug()<<sqlite3_errmsg(Db)<<rc;
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
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(Db,sql,-1,&stmt,NULL);

    if (rc != SQLITE_OK) {
        qDebug()<< sqlite3_errmsg(Db);
    }
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW){
        Books tmp;
        tmp.BookID = sqlite3_column_int(stmt,0);
        tmp.Title = (char*)sqlite3_column_text(stmt,1);
        tmp.Author = (char*)sqlite3_column_text(stmt,2);
        tmp.Stock = sqlite3_column_int(stmt,3);
        tmp.RokWydania = sqlite3_column_int(stmt,4);
        tmp.Genre = (char*)sqlite3_column_text(stmt,5);
        tmp.NumberRented = sqlite3_column_int(stmt,6);




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
    qDebug()<<sqlite3_errmsg(Db);
    if (sqlite3_step(stmtRemoveClient) != SQLITE_DONE) {
        qDebug() << "Failed to execute delete statement:" << sqlite3_errmsg(Db);
        sqlite3_finalize(stmtRemoveClient);
        return false;
    }

    sqlite3_finalize(stmtRemoveClient);
    return true;
}

bool database::removeRental(int rentalID){
    const char* deleteQuery = "DELETE FROM Wypozyczenia WHERE id = ?;";
    sqlite3_stmt* stmtRemoveClient;
    if (sqlite3_prepare_v2(Db, deleteQuery, -1, &stmtRemoveClient, nullptr) != SQLITE_OK) {
        qDebug() << "Failed to prepare delete statement:" << sqlite3_errmsg(Db);
        return false;
    }

    sqlite3_bind_int(stmtRemoveClient, 1, rentalID);

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

QVector<Rentals> database::setRentalList(){
    QVector<Rentals> datalist;
    const char* querry ="select * from Wypozyczenia";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(Db,querry,-1,&stmt,NULL);
    if (rc != SQLITE_OK) {
        qDebug()<< sqlite3_errmsg(Db);
    }
    while(sqlite3_step(stmt)==SQLITE_ROW){
        Rentals tmp;
        tmp.ID = sqlite3_column_int(stmt,0);
        tmp.clientID = sqlite3_column_int(stmt,1);
        tmp.bookID = sqlite3_column_int(stmt,2);
        tmp.returnDay = QDate::fromString(QString((char*)sqlite3_column_text(stmt,3)),"yyyy-MM-dd");
        tmp.borrowedDay = QDate::fromString(QString((char*)sqlite3_column_text(stmt,4)),"yyyy-MM-dd");
        datalist.append(tmp);
    }
    //QDebug()<<
    return datalist;
}
