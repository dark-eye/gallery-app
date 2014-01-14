# -*- Mode: Python; coding: utf-8; indent-tabs-mode: nil; tab-width: 4 -*-
# Copyright 2012 Canonical
#
# This program is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License version 3, as published
# by the Free Software Foundation.


"""Tests the Photos view of the gallery app."""

from __future__ import absolute_import

from testtools.matchers import Equals, Is
from autopilot.matchers import Eventually

from gallery_app.tests import GalleryTestCase
from gallery_app.emulators.photos_view import PhotosView

from os.path import exists
import unittest

class TestPhotosView(GalleryTestCase):

    @property
    def photos_view(self):
        return PhotosView(self.app)

    def setUp(self):
        self.ARGS = []
        super(TestPhotosView, self).setUp()
        self.switch_to_photos_tab()

    def switch_to_photos_tab(self):
        self.main_view.switch_to_tab("photosTab")
        self.ensure_tabs_dont_move()

    def click_first_photo(self):
        photo = self.photos_view.get_first_photo_in_photos_view()
        self.click_item(photo)

    def test_open_photo(self):
        self.main_view.close_toolbar()
        self.click_first_photo()
        photo_viewer = self.photos_view.get_main_photo_viewer()
        self.assertThat(photo_viewer.visible, Eventually(Equals(True)))

    def test_select_button_cancel(self):
        """Clicking the cancel button after clicking the select button must
        hide the toolbar automatically."""
        photos_overview = self.app.select_single("PhotosOverview")
        self.assertFalse(photos_overview.inSelectionMode)

        self.main_view.open_toolbar().click_button("selectButton")
        self.assertTrue(photos_overview.inSelectionMode)

        self.main_view.open_toolbar().click_custom_button("cancelButton")

        toolbar = self.main_view.get_toolbar()
        self.assertThat(toolbar.opened, Eventually(Equals(False)))
        self.assertFalse(photos_overview.inSelectionMode)

        first_photo = self.photos_view.get_first_photo_in_photos_view()
        self.tap_item(first_photo)
        self.assertTrue(photos_overview.inSelectionMode)

    def test_delete_photo_dialog_appears(self):
        """Selecting a photo must make the delete button clickable."""
        number_of_photos = self.photos_view.number_of_photos()
        self.main_view.open_toolbar().click_button("selectButton")
        self.click_first_photo()
        self.main_view.open_toolbar().click_button("deleteButton")

        self.assertThat(self.gallery_utils.delete_dialog_shown,
                        Eventually(Is(True)))

        cancel_item = self.photos_view.get_delete_dialog_cancel_button()
        self.click_item(cancel_item)
        self.assertThat(self.gallery_utils.delete_dialog_shown,
                        Eventually(Is(False)))

    def test_delete_a_photo(self):
        """Must be able to select a photo and use the dialog to delete it."""
        number_of_photos = self.photos_view.number_of_photos()
        self.main_view.open_toolbar().click_button("selectButton")
        self.click_first_photo()
        self.main_view.open_toolbar().click_button("deleteButton")

        self.assertThat(self.gallery_utils.delete_dialog_shown,
                        Eventually(Is(True)))

        self.main_view.open_toolbar().click_button("deleteButton")

        delete_item = self.photos_view.get_delete_dialog_delete_button()
        self.click_item(delete_item)
        self.assertThat(
            self.gallery_utils.delete_dialog_shown,
            Eventually(Is(False))
        )

        self.assertThat(lambda: self.photos_view.number_of_photos(),
                        Eventually(Equals(number_of_photos - 1)))

    @unittest.skip("Temporarily disable as it fails in some cases, supposedly due to problems with the infrastructure")
    def test_save_state(self):
        self.switch_to_photos_tab()

        tabs = self.main_view.select_single("Tabs")
        tab = tabs.get_current_tab()
        self.assertThat(tab.objectName, Equals("photosTab"))
        index = tab.index

        self.ensure_app_has_quit()
        self.start_app()

        tabs = self.main_view.select_single("Tabs")
        tab = tabs.get_current_tab()
        self.assertThat(tabs.selectedTabIndex, Eventually(Equals(index)))
        self.assertThat(tab.objectName, Equals("photosTab"))
