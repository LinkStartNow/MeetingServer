HEADERS += \
                $$PWD/Mysock.h \
                $$PWD/Tcpsock.h \
                $$PWD/cjson.h

SOURCES += \
                $$PWD/Mysock.cpp \
                $$PWD/Tcpsock.cpp

LIBS += -L/usr/local/lib/  -ljson

INCLUDEPATH += /usr/local/include/json \
                mynet
