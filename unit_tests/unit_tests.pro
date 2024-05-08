QT += testlib sql
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_unittest.cpp ../core/src/postgre_model.cpp
