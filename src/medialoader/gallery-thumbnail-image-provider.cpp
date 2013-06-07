/*
 * Copyright (C) 2012 Canonical Ltd
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
 * Guenter Schwann <guenter.schwann@canonical.com>
*/

#include "gallery-thumbnail-image-provider.h"

// media
#include "preview-manager.h"

#include <QDebug>
#include <QElapsedTimer>

const char* GalleryThumbnailImageProvider::PROVIDER_ID = "gallery-thumbnail";
const char* GalleryThumbnailImageProvider::PROVIDER_ID_SCHEME = "image://gallery-thumbnail/";
const char* GalleryThumbnailImageProvider::REVISION_PARAM_NAME = "edit";

/*!
 * @brief GalleryThumbnailImageProvider::GalleryThumbnailImageProvider
 */
GalleryThumbnailImageProvider::GalleryThumbnailImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Image),
      m_previewManager(0),
      m_logImageLoading(false)
{
}

/*!
 * \brief GalleryThumbnailImageProvider::ToURL return the URL to this image provider for a local file
 * \param file is the file that you want the url for
 * \return URL to be used to load a local image usign this image provider
 */
QUrl GalleryThumbnailImageProvider::ToURL(const QFileInfo &file)
{
    return QUrl::fromUserInput(PROVIDER_ID_SCHEME + file.absoluteFilePath());
}

/*!
 * @brief GalleryThumbnailImageProvider::requestImage @reimp of QQuickImageProvider::requestImage
 * @param id is the requested image source
 * @param size must be set to the original size of the image
 * @param requestedSize is not used here, as thumbnails have a fixed size
 * @return the image with id
 */
QImage GalleryThumbnailImageProvider::requestImage(const QString &id, QSize *size,
                                                   const QSize &requestedSize)
{
    Q_UNUSED(requestedSize);

    if (!m_previewManager) {
        qWarning() << Q_FUNC_INFO << "no PreviewManager set";
        return QImage();
    }

    QElapsedTimer timer;
    timer.start();

    QUrl url(id);
    QFileInfo photoFile(url.path());
    m_previewManager->ensurePreview(photoFile);

    QString fileName = m_previewManager->thumbnailFileName(photoFile);

    QImage thumbnail;
    thumbnail.load(fileName);
    if (thumbnail.isNull()) {
        qWarning() << "Could not load thumbnail:" << id;
    }

    if (size != NULL)
        *size = thumbnail.size();

    if (m_logImageLoading) {
        qDebug() << id << thumbnail.size() << "time:" << timer.elapsed() << "ms";
    }

    return thumbnail;
}

void GalleryThumbnailImageProvider::setPreviewManager(PreviewManager *previewManager)
{
    m_previewManager = previewManager;
}

void GalleryThumbnailImageProvider::setLogging(bool enableLogging)
{
    m_logImageLoading = enableLogging;
}