/*
 * Copyright (C) 2012 Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "sharefile.h"

#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QtQuick/QtQuick>
#include <QDebug>

/*!
 * \brief ShareFile::ShareFile
 * \param parent
 */
ShareFile::ShareFile(QObject *parent) :
    QObject(parent)
{
}

/*!
 * \brief ShareFile::writeShareFile
 * \param id
 * \param path
 */
void ShareFile::writeShareFile(const QString &id, const QString &path)
{
    QFileInfo imageFilePath(QDir::tempPath() + QDir::separator() + "sharelocation");
    QFile imageFile(imageFilePath.absoluteFilePath());
    if (imageFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream stream(&imageFile);
        stream << id;
        stream << "\n";
        stream << path;
        imageFile.close();
    } else {
        qWarning() << "Failed to open share file for writing";
    }
}
