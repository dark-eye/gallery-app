/*
 * Copyright (C) 2011 Canonical Ltd
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
 *
 * Authors:
 * Jim Nelson <jim@yorba.org>
 * Lucas Beeler <lucas@yorba.org>
 */

#include "qml-media-model.h"

#include <QHash>
#include <QtDeclarative>

#include "media-source.h"

QmlMediaModel::QmlMediaModel(QObject* parent = NULL)
  : QmlViewCollectionModel(parent) {
}

void QmlMediaModel::RegisterType() {
  qmlRegisterType<QmlMediaModel>("org.yorba.qt.qmlmediamodel", 1, 0,
    "QmlMediaModel");
}

void QmlMediaModel::Init(SelectableViewCollection* view) {
  QHash<int, QByteArray> roles;
  roles[ObjectNumberRole] = "object_number";
  roles[PreviewPathRole] = "preview_path";
  roles[PathRole] = "path";
  roles[SelectionRole] = "is_selected";
  
  QmlViewCollectionModel::Init(view, roles);
}

QVariant QmlMediaModel::DataForRole(DataObject *object, int role) const {
  MediaSource* media_source = qobject_cast<MediaSource*>(object);
  if (media_source == NULL)
    return QVariant();
  
  switch (role) {
    case PreviewPathRole:
      return QVariant("file:" + media_source->preview_file().absoluteFilePath());
    
    case PathRole:
      return QVariant("file:" + media_source->file().absoluteFilePath());
    
    default:
      return QVariant();
  }
}
