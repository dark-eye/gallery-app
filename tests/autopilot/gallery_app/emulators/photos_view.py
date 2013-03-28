# -*- Mode: Python; coding: utf-8; indent-tabs-mode: nil; tab-width: 4 -*-
# Copyright 2012 Canonical
#
# This program is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License version 3, as published
# by the Free Software Foundation.

from gallery_utils import GalleryUtils

class PhotosView(GalleryUtils):

    def __init__(self, app):
        self.app = app

    def get_tabs_bar(self):
        """Returns the top tabs bar."""
        return self.app.select_single("NewTabBar")

    def get_events_tab(self):
        """Returns the events tab."""
        return self.app.select_single("AbstractButton", buttonIndex=4)

    def get_photos_tab(self):
        """Returns the photos tab."""
        return self.app.select_single("AbstractButton", buttonIndex=5)

    def get_photos_view(self):
        """Returns the photos view."""
        return self.app.select_single("Tab", objectName="photosView")

    def get_first_photo_in_photos_view(self):
        """Returns the very first photo in the photos view."""
        return self.app.select_many("QQuickItem", objectName="allPotosGridPhoto")[0]

    def number_of_photos_in_photos_view(self):
        """Returns the number of events"""
        photo_delegates = self.app.select_many("QQuickItem", objectName="allPotosGridPhoto")
        return len(photo_delegates)