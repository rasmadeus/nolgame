QT += core gui widgets

TARGET = nolgame
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += precompile_header c++14
PRECOMPILED_HEADER = pch.h

RESOURCES += \
    res.qrc

SOURCES += \
    main.cpp \
    cell.cpp \
    main_view.cpp \
    game.cpp \
    champions.cpp \
    settings.cpp \
    settings_spinbox.cpp \
    about.cpp \
    lock.cpp \
    safe.cpp \
    keylock.cpp \
    pawl.cpp \
    history.cpp

HEADERS += \
    pch.h \
    cell.h \
    main_view.h \
    game.h \
    champions.h \
    settings.h \
    settings_spinbox.h \
    about.h \
    lock.h \
    safe.h \
    keylock.h \
    pawl.h \
    history.h
