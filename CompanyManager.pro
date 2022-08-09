QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    editcompanywindow.cpp \
    main.cpp \
    mainwindow.cpp \
    setupcompanywindow.cpp \
    src/company.cpp \
    src/employee.cpp \
    src/treeNode.cpp

HEADERS += \
    editcompanywindow.h \
    mainwindow.h \
    setupcompanywindow.h \
    src/company.h \
    src/employee.h \
    src/treeNode.h

FORMS += \
    editcompanywindow.ui \
    mainwindow.ui \
    setupcompanywindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resource.qrc
