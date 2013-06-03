/*
 * Copyright (C) 2013 Canonical, Ltd.
 *
 * Authors:
 *  Nicolas d'Offay <nicolas.doffay@canonical.com>
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
 *
 */

#include "gallery-manager.h"
#include "album/album-collection.h"
#include "album/album-default-template.h"
#include "core/command-line-parser.h"
#include "database/database.h"
#include "event/event-collection.h"
#include "media/media-collection.h"
#include "media/preview-manager.h"
#include "qml/gallery-standard-image-provider.h"
#include "qml/gallery-thumbnail-image-provider.h"
#include "util/resource.h"

GalleryManager* GalleryManager::gallery_mgr_ = NULL;

/*!
 * \brief GalleryManager::instance
 * \param application_path_dir the directory of where the executable is
 * \param pictures_dir the directory of the images
 * \param view the view is used to determine the max texture size
 * \param log_image_loading if true, the image loadings times are printed to stdout
 * \return
 */
GalleryManager* GalleryManager::instance(const QDir &pictures_dir,
                                         QQuickView *view, const bool log_image_loading)
{
    if (!gallery_mgr_)
        gallery_mgr_ = new GalleryManager(pictures_dir, view, log_image_loading);

    return gallery_mgr_;
}

GalleryManager::GalleryManager(const QDir& pictures_dir,
                               QQuickView *view, const bool log_image_loading)
    : collections_initialised(false),
      resource_(new Resource(pictures_dir.path(), view)),
      gallery_standard_image_provider_(new GalleryStandardImageProvider(log_image_loading)),
      gallery_thumbnail_image_provider_(new GalleryThumbnailImageProvider(log_image_loading)),
      database_(NULL),
      default_template_(NULL),
      media_collection_(NULL),
      album_collection_(NULL),
      event_collection_(NULL),
      preview_manager_(NULL)
{
    const int maxTextureSize = resource_->maxTextureSize();
    gallery_standard_image_provider_->setMaxLoadResolution(maxTextureSize);
}

void GalleryManager::post_init()
{
    if (!collections_initialised)
    {
        qDebug() << "Opening" << resource_->picturesDirectory() << "...";

        Exiv2::LogMsg::setLevel(Exiv2::LogMsg::mute);

        database_ = new Database(resource_->databaseDirectory(),
                                 resource_->get_rc_url("sql").path());
        database_->get_media_table()->verify_files();
        default_template_ = new AlbumDefaultTemplate();
        QDir mediaDir(resource_->picturesDirectory());
        media_collection_ = new MediaCollection(mediaDir);
        album_collection_ = new AlbumCollection();
        event_collection_ = new EventCollection();
        preview_manager_ = new PreviewManager();

        collections_initialised = true;

        qDebug() << "Opened" << resource_->picturesDirectory();
    }
}

GalleryManager::~GalleryManager()
{
    delete resource_;
    resource_ = NULL;

    delete gallery_standard_image_provider_;
    gallery_standard_image_provider_ = NULL;

    delete gallery_thumbnail_image_provider_;
    gallery_thumbnail_image_provider_ = NULL;

    delete database_;
    database_ = NULL;

    delete default_template_;
    default_template_ = NULL;

    delete media_collection_;
    media_collection_ = NULL;

    delete album_collection_;
    album_collection_ = NULL;

    delete event_collection_;
    event_collection_ = NULL;

    delete preview_manager_;
    preview_manager_ = NULL;
}
