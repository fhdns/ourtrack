# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = lib
TARGET = fervorUpdater
DESTDIR = ../Win32/Debug
QT += core network
CONFIG += staticlib
DEFINES += WIN64 QT_DLL QT_NETWORK_LIB FERVORUPDATER_LIB
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/Debug
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/debug
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(fervorUpdater.pri)