TEMPLATE = app
CONFIG += qt warn_on
TARGET = Register
DESTDIR = bin
MOC_DIR = tmp
OBJECTS_DIR = obj
RES_DIR = resource
DEPENDPATH += . include src
INCLUDEPATH += . include
QMAKE_CXXFLAGS_WARN_ON += -Wno-reorder
QMAKE_CXXFLAGS_WARN_ON += -Wno-parentheses
QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter

# Input
HEADERS += include/attribute.h \
           include/database.h \
           include/doublylinkedlist.h \
           include/hashtable.h \
           include/manager.h \
           include/menu.h \
           include/readwrite.h \
           include/record.h
SOURCES += src/attribute.cpp \
           src/database.cpp \
           src/manager.cpp \
           src/menu.cpp \
           src/readwrite.cpp \
           src/record.cpp \
           src/register.cpp
