QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testsomething.cpp

INCLUDEPATH += E:\WORKSPACES\Qt\untitled01

HEADERS += \
    Calculator.h \
    Calculator2.h


