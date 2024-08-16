//#include"Headers/Clients.h"
//#include "Headers/sqlite3.h"
//#include <iostream>
//#include "Headers/sqlite3.h"
//#include <QDebug>


//Clients::Clients(int id,QString imie,QString nazwisko,QString adres,int telefon,QString email,int numerkarty){

//    ClientID = id;
//    Imie = imie;
//    Nazwisko = nazwisko;
//    Adres = adres;
//    NumerTelefonu = telefon;
//    Email = email;
//    NumerKarty = numerkarty;
//}

//void Clients::setDataList(database *Db){

//    const char* sql = "SELECT * FROM Klienci;";
//    sqlite3_stmt* stmt;
//    int rc = sqlite3_prepare_v2(Db->Db,sql,-1,&stmt,NULL);
//    if (rc != SQLITE_OK) {
//        qDebug()<< sqlite3_errmsg(Db->Db);
//    }
//    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW){
//        Clients tmp;
//        QString str[3];
//        str[0].setNum(sqlite3_column_int(stmt,0));
//        str[1].setNum(sqlite3_column_int(stmt,4));
//        str[2].setNum(sqlite3_column_int(stmt,6));
//        tmp.append(str[0]);
//        tmp.append((char*)sqlite3_column_text(stmt,1));
//        tmp.append((char*)sqlite3_column_text(stmt,2));
//        tmp.append((char*)sqlite3_column_text(stmt,3));
//        tmp.append(str[1]);
//        tmp.append((char*)sqlite3_column_text(stmt,5));
//        tmp.append(str[2]);


//        datalist.append(tmp);
//    }
//    qDebug()<<".count():"<<datalist.count();

//}





//}
