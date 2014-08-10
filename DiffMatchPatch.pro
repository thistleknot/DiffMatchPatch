#-------------------------------------------------
#
# Project created by QtCreator 2014-08-10T07:23:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DiffMatchPatch
TEMPLATE = app


SOURCES += main.cpp\
        diffmatchpatch.cpp \
    diff_match_patch.cpp \
    diff_match_patch_test.cpp

HEADERS  += diffmatchpatch.h \
    diff_match_patch.h \
    diff_match_patch_test.h

FORMS    += diffmatchpatch.ui
