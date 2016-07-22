#-------------------------------------------------
#
# Project created by QtCreator 2015-06-25T10:32:47
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       += opengl
CONFIG   += C++14
CONFIG   += console
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
VERSION = 1.0.2.7
TARGET = EXOSTAR
TEMPLATE = app
RC_ICONS =logo.ico
SOURCES += \
    main.cpp \
    SpaceEngine/Objects/EButton.cpp \
    SpaceEngine/Objects/ECamera.cpp \
    SpaceEngine/Objects/EEffect.cpp \
    SpaceEngine/Objects/EFon.cpp \
    SpaceEngine/Objects/EGameObject.cpp \
    SpaceEngine/Objects/EImage.cpp \
    SpaceEngine/Objects/EMinimap.cpp \
    SpaceEngine/Objects/EModuleObject.cpp \
    SpaceEngine/Objects/EObject.cpp \
    SpaceEngine/System/EAi.cpp \
    SpaceEngine/System/EAiControle.cpp \
    SpaceEngine/System/EConfig.cpp \
    SpaceEngine/System/EError.cpp \
    SpaceEngine/System/eevents.cpp \
    SpaceEngine/System/EInterface.cpp \
    SpaceEngine/System/EKord.cpp \
    SpaceEngine/System/EMaps.cpp \
    SpaceEngine/System/EMusic.cpp \
    SpaceEngine/System/ESprite.cpp \
    SpaceEngine/System/EThread.cpp \
    SpaceEngine/SpaceEngine.cpp \
    SpaceEngine/Objects/QButton.cpp \
    SpaceEngine/System/ESoundsCenter.cpp \
    SpaceEngine/Objects/EDialog.cpp \
    SpaceEngine/System/ELanguage.cpp \
    SpaceEngine/Objects/ECheckBox.cpp \
    SpaceEngine/Objects/EParticles.cpp \
    SpaceEngine/System/EGraphicsConfig.cpp \
    SpaceEngine/System/EContur.cpp \
    SpaceEngine/Objects/EParalax.cpp \
    SpaceEngine/System/EPool.cpp

HEADERS += \
    SpaceEngine/Objects/EButton.h \
    SpaceEngine/Objects/ECamera.h \
    SpaceEngine/Objects/EEffect.h \
    SpaceEngine/Objects/EFon.h \
    SpaceEngine/Objects/EGameObject.h \
    SpaceEngine/Objects/EImage.h \
    SpaceEngine/Objects/EMinimap.h \
    SpaceEngine/Objects/EModuleObject.h \
    SpaceEngine/Objects/EObject.h \
    SpaceEngine/System/EAi.h \
    SpaceEngine/System/EAiControle.h \
    SpaceEngine/System/EConfig.h \
    SpaceEngine/System/EDefkey.h \
    SpaceEngine/System/EError.h \
    SpaceEngine/System/eevents.h \
    SpaceEngine/System/EInterface.h \
    SpaceEngine/System/EKord.h \
    SpaceEngine/System/EList.h \
    SpaceEngine/System/EMaps.h \
    SpaceEngine/System/EMusic.h \
    SpaceEngine/System/EPair.h \
    SpaceEngine/System/ESoundsCenter.h \
    SpaceEngine/System/ESprite.h \
    SpaceEngine/System/EThread.h \
    SpaceEngine/SpaceEngine.h \
    SpaceEngine/Objects/QButton.h \
    SpaceEngine/Objects/EDialog.h \
    SpaceEngine/System/ELanguage.h \
    SpaceEngine/Objects/ECheckBox.h \
    SpaceEngine/Objects/EParticles.h \
    SpaceEngine/System/EGraphicsConfig.h \
    SpaceEngine/System/EContur.h \
    SpaceEngine/Objects/EParalax.h \
    SpaceEngine/System/EPool.h

RESOURCES +=
#LIBS += -lopengl32
INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

DISTFILES +=

