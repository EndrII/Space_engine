#-------------------------------------------------
#
# Project created by QtCreator 2016-07-14T10:33:12
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       += opengl
CONFIG   += C++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
VERSION = 0.1.2.0
TARGET = EXOSTAR_Editor
TEMPLATE = app
RC_ICONS =logo.ico

HEADERS += \
    SpaceEngine/Objects/EButton.h \
    SpaceEngine/Objects/ECamera.h \
    SpaceEngine/Objects/ECheckBox.h \
    SpaceEngine/Objects/EDialog.h \
    SpaceEngine/Objects/EEffect.h \
    SpaceEngine/Objects/EFon.h \
    SpaceEngine/Objects/EGameObject.h \
    SpaceEngine/Objects/EImage.h \
    SpaceEngine/Objects/EMinimap.h \
    SpaceEngine/Objects/EModuleObject.h \
    SpaceEngine/Objects/EObject.h \
    SpaceEngine/Objects/EParalax.h \
    SpaceEngine/Objects/EParticles.h \
    SpaceEngine/Objects/EShell.h \
    SpaceEngine/Objects/QButton.h \
    SpaceEngine/System/EAi.h \
    SpaceEngine/System/EAiControle.h \
    SpaceEngine/System/EConfig.h \
    SpaceEngine/System/EContur.h \
    SpaceEngine/System/EDefkey.h \
    SpaceEngine/System/EError.h \
    SpaceEngine/System/eevents.h \
    SpaceEngine/System/EGraphicsConfig.h \
    SpaceEngine/System/EMapCore.h \
    SpaceEngine/System/EKord.h \
    SpaceEngine/System/ELanguage.h \
    SpaceEngine/System/EList.h \
    SpaceEngine/System/EMaps.h \
    SpaceEngine/System/EMusic.h \
    SpaceEngine/System/EPair.h \
    SpaceEngine/System/EPool.h \
    SpaceEngine/System/ERandom.h \
    SpaceEngine/System/ESound.h \
    SpaceEngine/System/ESoundsCenter.h \
    SpaceEngine/System/ESprite.h \
    SpaceEngine/System/EThread.h \
    SpaceEngine/SpaceEngine.h \
    widget.h \
    SpriteEditor.h \
    projectdir.h \
    Buttons.h \
    SpaceEngine/Objects/ELoadScreen.h \
    CompressMenu.h \
    SpaceEngine/System/EMouseEvent.h \
    ObjectEditor.h \
    ModuleInformation.h \
    Modules/Module.h \
    Modules/ModuleParalax.h \
    Modules/Modules.h \
    SpaceEngine/GameObjects/EGameResurs.h \
    SpaceEngine/GameObjects/EResurse.h \
    SpaceEngine/System/css.h \
    SpaceEngine/NetworkObjects/ELocalServers.h \
    SpaceEngine/NetworkObjects/EServer.h \
    SpaceEngine/NetworkObjects/ETcpSocket.h \
    SpaceEngine/GameObjects/EResursePack.h \
    Modules/ModuleResursObject.h \
    SpaceEngine/GameObjects/EResObjectView.h \
    Modules/AddResurse.h \
    LanguageEditor.h \
    SpaceEngine/System/EThreadObject.h \
    SpaceEngine/System/ECore.h \
    SpaceEngine/GameObjects/EItem.h \
    Modules/ResObjectsView.h \
    SpaceEngine/System/EBase.h

SOURCES += \
    SpaceEngine/Objects/EButton.cpp \
    SpaceEngine/Objects/ECamera.cpp \
    SpaceEngine/Objects/ECheckBox.cpp \
    SpaceEngine/Objects/EDialog.cpp \
    SpaceEngine/Objects/EEffect.cpp \
    SpaceEngine/Objects/EFon.cpp \
    SpaceEngine/Objects/EGameObject.cpp \
    SpaceEngine/Objects/EImage.cpp \
    SpaceEngine/Objects/EMinimap.cpp \
    SpaceEngine/Objects/EModuleObject.cpp \
    SpaceEngine/Objects/EObject.cpp \
    SpaceEngine/Objects/EParalax.cpp \
    SpaceEngine/Objects/EParticles.cpp \
    SpaceEngine/Objects/EShell.cpp \
    SpaceEngine/Objects/QButton.cpp \
    SpaceEngine/System/EAi.cpp \
    SpaceEngine/System/EAiControle.cpp \
    SpaceEngine/System/EConfig.cpp \
    SpaceEngine/System/EContur.cpp \
    SpaceEngine/System/EError.cpp \
    SpaceEngine/System/eevents.cpp \
    SpaceEngine/System/EGraphicsConfig.cpp \
    SpaceEngine/System/EMapCore.cpp \
    SpaceEngine/System/EKord.cpp \
    SpaceEngine/System/ELanguage.cpp \
    SpaceEngine/System/EMaps.cpp \
    SpaceEngine/System/EMusic.cpp \
    SpaceEngine/System/EPool.cpp \
    SpaceEngine/System/ERandom.cpp \
    SpaceEngine/System/ESound.cpp \
    SpaceEngine/System/ESoundsCenter.cpp \
    SpaceEngine/System/ESprite.cpp \
    SpaceEngine/System/EThread.cpp \
    SpaceEngine/SpaceEngine.cpp \
    main.cpp \
    widget.cpp \
    SpriteEditor.cpp \
    Buttons.cpp \
    SpaceEngine/Objects/ELoadScreen.cpp \
    CompressMenu.cpp \
    SpaceEngine/System/EMouseEvent.cpp \
    ObjectEditor.cpp \
    ModuleInformation.cpp \
    Modules/Module.cpp \
    Modules/ModuleParalax.cpp \
    SpaceEngine/GameObjects/EGameResurs.cpp \
    SpaceEngine/GameObjects/EResurse.cpp \
    SpaceEngine/System/css.cpp \
    SpaceEngine/NetworkObjects/ELocalServers.cpp \
    SpaceEngine/NetworkObjects/EServer.cpp \
    SpaceEngine/NetworkObjects/ETcpSocket.cpp \
    SpaceEngine/GameObjects/EResursePack.cpp \
    Modules/ModuleResursObject.cpp \
    SpaceEngine/GameObjects/EResObjectView.cpp \
    Modules/AddResurse.cpp \
    LanguageEditor.cpp \
    SpaceEngine/System/EThreadObject.cpp \
    SpaceEngine/System/ECore.cpp \
    SpaceEngine/GameObjects/EItem.cpp \
    Modules/ResObjectsView.cpp \
    SpaceEngine/System/EBase.cpp

#LIBS += -lopengl32

RESOURCES += \
    ress.qrc

DISTFILES += \
    logo.png \
    logo.ico \
    Resurses/StyleProgramm.css

FORMS += \
    dialog.ui
