# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = app
TARGET = ourtrackserv
DESTDIR = ../BUILD/other/Debug
QT += core sql network
CONFIG += debug console

win32 {
    DEFINES += QT_DLL QT_NETWORK_LIB QT_SQL_LIB
}

INCLUDEPATH += . \
    ./GeneratedFiles/Debug
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/debug
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(ourtrackserv.pri)
