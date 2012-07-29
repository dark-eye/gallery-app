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
 * Charles Lindsay <chaz@yorba.org>
 */

#ifndef GALLERY_PHOTO_CACHES_H_
#define GALLERY_PHOTO_CACHES_H_

#include <QString>
#include <QFileInfo>
#include <QFile>

// An abstraction around the various files we keep in addition to the photo
// file itself: the original, the pristine version of the file without any
// applied edits; and the enhanced, a version of the original with auto-enhance
// applied to it (necessary because of how slow auto-enhance is).
class PhotoCaches {
 public:
  static const QString ORIGINAL_DIR;
  static const QString ENHANCED_DIR;

  PhotoCaches(const QFileInfo& file);

  bool has_cached_original() const;
  bool has_cached_enhanced() const;

  const QFileInfo& original_file() const;
  const QFileInfo& enhanced_file() const;

  // Returns original_file() if it exists; otherwise, returns the file passed
  // to the constructor.
  const QFileInfo& pristine_file() const;

  // Moves the pristine file into .original so we don't mess it up.  Note that
  // this potentially removes the main file, so it must be followed by a copy
  // from original (or elsewhere) back to the file.
  bool cache_original();

  // Moves the file out of .original, overwriting the main file.  Note that
  // this removes the .original file.
  bool restore_original();

  // Copies the file in .original to .enhanced so it can then be enhanced.
  bool cache_enhanced_from_original();

  // Tries to overwrite the file from one of its cached versions.
  bool overwrite_from_cache(bool prefer_enhanced);

  void discard_cached_original();
  void discard_cached_enhanced();
  void discard_all();

 private:
  static bool remove(const QFileInfo& file) {
    return QFile::remove(file.filePath());
  }
  static bool rename(const QFileInfo& oldName, const QFileInfo& newName) {
    return QFile::rename(oldName.filePath(), newName.filePath());
  }
  static bool copy(const QFileInfo& oldName, const QFileInfo& newName) {
    return QFile::copy(oldName.filePath(), newName.filePath());
  }

  QFileInfo file_;
  QFileInfo original_file_;
  QFileInfo enhanced_file_;
};

#endif