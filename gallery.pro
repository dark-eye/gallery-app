######################################################################
# Automatically generated by qmake (2.01a) Mon Oct 24 15:04:00 2011
######################################################################

isEmpty(PREFIX) {
	PREFIX = /usr/local
}

TEMPLATE = app
TARGET = gallery
DEPENDPATH += . src
INCLUDEPATH += src
CONFIG += qt debug link_pkgconfig
QMAKE_CXXFLAGS += -Werror -Wno-unused-parameter
QT += gui declarative opengl
MOC_DIR = build
OBJECTS_DIR = build
RESOURCES = rc/gallery.qrc
RCC_DIR = build
QMAKE_RESOURCE_FLAGS += -root /rc
PKGCONFIG += exiv2

install.path = $$PREFIX/bin/
install.files = gallery
INSTALLS = install

# Input

SOURCES += \
	src/main.cpp \
	src/album/album.cpp \
	src/album/album-default-template.cpp \
	src/album/album-collection.cpp \
	src/album/album-page.cpp \
	src/album/album-template.cpp \
	src/album/album-template-page.cpp \
	src/core/container-source.cpp \
	src/core/container-source-collection.cpp \
	src/core/data-collection.cpp \
	src/core/data-object.cpp \
	src/core/data-source.cpp \
	src/core/selectable-view-collection.cpp \
	src/core/source-collection.cpp \
	src/core/view-collection.cpp \
	src/media/media-collection.cpp \
	src/media/media-source.cpp \
	src/photo/photo.cpp \
	src/photo/photo-metadata.cpp \
	src/qml/qml-album-collection-model.cpp \
	src/qml/qml-media-collection-model.cpp \
	src/qml/qml-stack.cpp \
	src/qml/qml-view-collection-model.cpp

HEADERS += \
	src/album/album.h \
	src/album/album-collection.h \
	src/album/album-default-template.h \
	src/album/album-page.h \
	src/album/album-template.h \
	src/album/album-template-page.h \
	src/core/container-source.h \
	src/core/container-source-collection.h \
	src/core/data-collection.h \
	src/core/data-object.h \
	src/core/data-source.h \
	src/core/selectable-view-collection.h \
	src/core/source-collection.h \
	src/core/utils.h \
	src/core/view-collection.h \
	src/media/media-collection.h \
	src/media/media-source.h \
	src/photo/photo.h \
	src/photo/photo-metadata.h \
	src/qml/qml-album-collection-model.h \
	src/qml/qml-media-collection-model.h \
	src/qml/qml-stack.h \
	src/qml/qml-view-collection-model.h

OTHER_FILES += \
	rc/gallery.qrc \
	rc/qml/AddToAlbumButton.qml \
	rc/qml/AlbumPickerPopup.qml \
	rc/qml/AlbumPreviewA.qml \
	rc/qml/AlbumPreviewB.qml \
	rc/qml/AlbumPreviewComponent.qml \
	rc/qml/AlbumViewer.qml \
	rc/qml/AlbumViewMasthead.qml \
	rc/qml/BinaryTabGroup.qml \
	rc/qml/Checkerboard.qml \
	rc/qml/FramePortrait.qml \
	rc/qml/MediaSelector.qml \
	rc/qml/NavButton.qml \
	rc/qml/NavStack.qml \
	rc/qml/NavToolbar.qml \
	rc/qml/Overview.qml \
	rc/qml/PhotoComponent.qml \
	rc/qml/PhotoViewer.qml \
	rc/qml/ReturnButton.qml \
	rc/qml/SquareButton.qml \
	rc/qml/Tab.qml \
	rc/qml/TabletSurface.qml \
	rc/qml/ViewerNavigationButton.qml
