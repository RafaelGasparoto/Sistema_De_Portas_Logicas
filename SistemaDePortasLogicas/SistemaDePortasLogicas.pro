TEMPLATE = app
TARGET = Trabalho
QT = core gui widgets
QT += core gui
QT += qml xml

SOURCES += \
    and.cpp \
    falso.cpp \
    janelaprincipal.cpp \
    led.cpp \
    main.cpp \
    not.cpp \
    or.cpp \
    porta.cpp \
    verdade.cpp

HEADERS += \
    and.h \
    falso.h \
    janelaprincipal.h \
    led.h \
    not.h \
    or.h \
    porta.h \
    verdade.h

DISTFILES += \
    imagens/AND.png \
    imagens/NOT.png \
    imagens/OR.png \
    imagens/falso.png \
    imagens/led.png \
    imagens/verdade.png

RESOURCES += \
    images.qrc


