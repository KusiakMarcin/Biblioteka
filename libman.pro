QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Source/Books.cpp \
    Source/BooksTableModel.cpp \
    Source/ClientTableModel.cpp \
    Source/Clients.cpp \
    Source/Rentals.cpp \
    Source/database.cpp \
    Source/sqlite3.c \
    addclientelement.cpp \
    main.cpp \
    mainwindow.cpp



HEADERS += \
    Headers/Books.h \
    Headers/BooksTableModel.h \
    Headers/ClientTableModel.h \
    Headers/Clients.h \
    Headers/Rentals.h \
    Headers/database.h \
    Headers/sqlite3.h \
    addclientelement.h \
    mainwindow.h

FORMS += \
    addclientelement.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    DATA.qrc

DISTFILES += \
    databases/data.db \
    databases/data.db-journal


