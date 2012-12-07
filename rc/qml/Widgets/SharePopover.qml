/*
 * Copyright (C) 2011-2012 Canonical Ltd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 2.0
import Ubuntu.Components.Popups 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem

Popover {
    id: sharePopover
    Column {
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }
        ListItem.Header { text: "Dummy share menu" }
        ListItem.Subtitled {
            text: "Facebook"
            subText: "calumpringle"
            onClicked: hide()
        }
        ListItem.Subtitled {
            text: "Twitter"
            subText: "@ckpringle"
            onClicked: hide()
        }
        ListItem.Subtitled {
            text: "Ubuntu One"
            subText: "ckpringle"
            onClicked: hide()
        }
        ListItem.Subtitled {
            text: "Gmail"
            subText: "calumpringle@gmail.com"
            onClicked: hide()
        }
        ListItem.Subtitled {
            text: "Pinterest"
            subText: "ckpringle@yahoo.co.uk"
            onClicked: hide()
        }
    }
}
