QT += quick

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
QML_IMPORT_PATH += /opt/Qt5.8.0/5.8/gcc_64/qml/QtGraphicalEffects
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib64 -laws-cpp-sdk-core -laws-cpp-sdk-s3 -laws-cpp-sdk-sns -laws-cpp-sdk-lambda -laws-cpp-sdk-dynamodb

SOURCES += \
        classmoor.cpp \
        classmoorapplication.cpp \
        dynamoclient.cpp \
        lambdaclient.cpp \
        main.cpp \
        setup.cpp \
        snsclient.cpp

RESOURCES += qml.qrc
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =/opt/Qt5.14.2/gcc_64/qml/QtGraphicalEffects/

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/local/lib64/release/ -laws-cpp-sdk-core
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/local/lib64/debug/ -laws-cpp-sdk-core
#else:unix: LIBS += -L$$PWD/../../../usr/local/lib64/ -laws-cpp-sdk-core

#INCLUDEPATH += $$PWD/../../../usr/local/include/aws
#DEPENDPATH += $$PWD/../../../usr/local/include/aws

HEADERS += \
    classmoor.h \
    classmoorapplication.h \
    dynamoclient.h \
    lambdaclient.h \
    setup.h \
    snsclient.h
