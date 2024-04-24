QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/command.cpp \
    src/test.cpp \
    qt/src/main.cpp \
    qt/src/mainwindow.cpp

HEADERS += \
    headers/command.hpp \
    headers/model_interface.hpp \
    headers/test.hpp \
    headers/view_interface.hpp \
    qt/headers/mainwindow.h

FORMS += \
    qt/ui/mainwindow.ui

TRANSLATIONS += \
    qt/translations/cw-vesupplier_ru_RU.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
