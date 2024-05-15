QT       += core gui sql testlib widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    qt/src/connectdialog.cpp \
    main.cpp \
    qt/src/mainwindow.cpp \
    core/src/postgre_model.cpp

HEADERS += \
    qt/headers/mainwindow.h \
    core/headers/postgre_model.hpp \
    qt/headers/connectdialog.h

FORMS += \
    qt/ui/connectdialog.ui \
    qt/ui/mainwindow.ui

TRANSLATIONS += \
    qt/translations/cw-vesupplier_ru_RU.ts \
    qt/translations/cw-vesupplier_en_US.ts \
    qt/translations/cw-vesupplier_zh_CN.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
