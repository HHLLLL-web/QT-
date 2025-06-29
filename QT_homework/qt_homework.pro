QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Cloth.cpp \
    changeuserinfo.cpp \
    closet.cpp \
    history.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    newclothes.cpp \
    newclothespic.cpp \
    newclothestype.cpp \
    recommend.cpp \
    recommend_algorithm.cpp \
    showhistory.cpp \
    showrecommend.cpp \
    signup.cpp

HEADERS += \
    Cloth.h \
    DataBase.h \
    changeuserinfo.h \
    closet.h \
    history.h \
    login.h \
    mainwindow.h \
    newclothes.h \
    newclothespic.h \
    newclothestype.h \
    recommend.h \
    recommend_algorithm.h \
    showhistory.h \
    showrecommend.h \
    signup.h

FORMS += \
    changeuserinfo.ui \
    closet.ui \
    history.ui \
    login.ui \
    mainwindow.ui \
    newclothes.ui \
    newclothespic.ui \
    newclothestype.ui \
    recommend.ui \
    showhistory.ui \
    showrecommend.ui \
    signup.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES +=
