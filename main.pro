TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ckernel.cpp \
        main.cpp

DISTFILES += \
                myepoll.pri \
                mynet.pri \
                mynet.pri

include(mynet/mynet.pri)
include(myepoll/myepoll.pri)
include(mysql/mysql.pri)

LIBS += -pthread

HEADERS += \
                Protocol.h \
                ckernel.h \
                mymap.h
