#-------------------------------------------------
#
# Project created by QtCreator 2015-06-29T17:31:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FlowSoploCulc
TEMPLATE = app

CONFIG -= debug
CONFIG += release

INCLUDEPATH += src
INCLUDEPATH += ../mnasoft_lib \
               ../mnasoft_lib/ns_MNAS_CodePage \
               ../mnasoft_lib/ns_MNAS_Error \
               ../mnasoft_lib/ns_MNAS_ValDimension \
               ../mnasoft_lib/ns_MNAS_Gases \
               ../mnasoft_lib/ns_MNAS_HalfDiv \
               ../mnasoft_lib/ns_MNAS_Matrix \
               ../mnasoft_lib/ns_MNAS_MendeleevTbl

INCLUDEPATH += ../EnterBoxPlugin \
               ../EnterBoxPlugin\src


HEADERS  += src/Flow.h
SOURCES += src/Flow.cpp src/main.cpp

unix:LIBS  += -L. -L/usr/local/lib -lmnas
win32:LIBS += E:/home/namatv/usr/bin/mnas.dll E:/PRG/Qt/5.4/mingw491_32/plugins/designer/mnasoft_eb.dll

#$$[QT_INSTALL_PLUGINS]/designer/mnasoft_eb.dll

FORMS    += src/Flow.ui

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32 {
    target.path = e:/home/namatv/usr/bin
    INSTALLS += target
}
