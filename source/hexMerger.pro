QT += core widgets gui xml

APPLICATION_NAME = HEX-Merger
APPLICATION_DESCRIPTION = HEX-file post-processor
APPLICATION_COPYRIGHT = Christian Marty

VERSION_MAJOR = 0
VERSION_MINOR = 1
VERSION_PATCH = 0
VERSION_BUILD = 0

CONFIG += c++22
TEMPLATE = app

VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}.$${VERSION_BUILD}
DEFINES += APPLICATION_VERSION=\\\"$${VERSION}\\\"

TARGET = $${APPLICATION_NAME}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060800    # disables all the APIs deprecated before Qt 6.8.0

SOURCES += \
    QuCLib/source/hexFileParser.cpp \
    logic/fileItem.cpp \
    logic/fileMerger.cpp \
    logic/settings.cpp \
    logic/transformItem.cpp \
    logic/xmlReader.cpp \
    ui/fileItemWidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    QuCLib/source/hexFileParser.h \
    colourPalette.h \
    logic/fileItem.h \
    logic/fileMerger.h \
    logic/settings.h \
    logic/transformItem.h \
    logic/xmlReader.h \
    main.h \
    ui/fileItemWidget.h \
    mainwindow.h

FORMS += \
    ui/fileItemWidget.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32:CONFIG(release, debug|release){

    # add executable meta data
    QMAKE_TARGET_COMPANY = $$COMPANY_NAME
    QMAKE_TARGET_PRODUCT = $$APPLICATION_NAME
    QMAKE_TARGET_DESCRIPTION = $$APPLICATION_DESCRIPTION
    QMAKE_TARGET_COPYRIGHT = $$APPLICATION_COPYRIGHT


    RELEASE_FOLDER = $$PWD/../build/Desktop_Qt_6_7_0_MinGW_64_bit-Release/release
    DISTRIBUTION_FOLDER = $$PWD/../build/distribution

    RELEASE_FILES = \
            $${RELEASE_FOLDER}/$${APPLICATION_NAME}.exe


    distribution.files = $${RELEASE_FILES}
    distribution.path = $${DISTRIBUTION_FOLDER}

    COPIES += distribution

    TOOLCHAIN =  $$[QT_INSTALL_PREFIX]/bin/
    DEPLOY_MAIN = $${TOOLCHAIN}windeployqt6.exe $${DISTRIBUTION_FOLDER}/$${APPLICATION_NAME}.exe

    system($$DEPLOY_MAIN)
}
