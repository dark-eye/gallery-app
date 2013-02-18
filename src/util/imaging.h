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
 * Lucas Beeler <lucas@yorba.org>
 */

#ifndef GALLERY_UTIL_IMAGING_H_
#define GALLERY_UTIL_IMAGING_H_

#include <QColor>
#include <QImage>
#include <QVector4D>

/*!
 * \brief clampi
 * \param i
 * \param min
 * \param max
 * \return
 */
inline int clampi(int i, int min, int max) {
  return (i < min) ? min : ((i > max) ? max : i);
}

/*!
 * \brief clampf
 * \param x
 * \param min
 * \param max
 * \return
 */
inline float clampf(float x, float min, float max) {
  return (x < min) ? min : ((x > max) ? max : x);
}

/*!
 * \brief The HSVTransformation class
 */
class HSVTransformation {
 public:
  HSVTransformation() { }
  virtual ~HSVTransformation() { }

  virtual QColor transform_pixel(const QColor& pixel_color) const;
  virtual bool is_identity() const = 0;

 protected:
  int remap_table_[256];
};

/*!
 * \brief The IntensityHistogram class
 */
class IntensityHistogram {
 public:
  IntensityHistogram(const QImage& basis_image);
  virtual ~IntensityHistogram() { }

  float get_cumulative_probability(int level);

 private:
  int counts_[256];
  float probabilities_[256];
  float cumulative_probabilities_[256];
};

/*!
 * \brief The ToneExpansionTransformation class
 */
class ToneExpansionTransformation : public virtual HSVTransformation {
  static const float DEFAULT_LOW_DISCARD_MASS;
  static const float DEFAULT_HIGH_DISCARD_MASS;

 public:
  ToneExpansionTransformation(IntensityHistogram h, float low_discard_mass =
    -1.0f, float high_discard_mass = -1.0f);
  virtual ~ToneExpansionTransformation() { }

  bool is_identity() const;

  float low_discard_mass() const;
  float high_discard_mass() const;

 private:
  void build_remap_table();

  int low_kink_;
  int high_kink_;
  float low_discard_mass_;
  float high_discard_mass_;
};

/*!
 * \brief The HermiteGammaApproximationFunction class
 */
class HermiteGammaApproximationFunction {
 public:
  HermiteGammaApproximationFunction(float user_interval_upper);
  virtual ~HermiteGammaApproximationFunction() { }

  float evaluate(float x);

 private:
  float x_scale_;
  float nonzero_interval_upper_;
};

/*!
 * \brief The ShadowDetailTransformation class
 */
class ShadowDetailTransformation : public virtual HSVTransformation {
  static const float MAX_EFFECT_SHIFT;
  static const float MIN_TONAL_WIDTH;
  static const float MAX_TONAL_WIDTH;
  static const float TONAL_WIDTH;

 public:
  ShadowDetailTransformation(float intensity);

  bool is_identity() const;

 private:
  float intensity_;
};

/*!
 * \brief The AutoEnhanceTransformation class
 */
class AutoEnhanceTransformation : public virtual HSVTransformation {
  static const int SHADOW_DETECT_MIN_INTENSITY;
  static const int SHADOW_DETECT_MAX_INTENSITY;
  static const int SHADOW_DETECT_INTENSITY_RANGE;
  static const int EMPIRICAL_DARK;
  static const float SHADOW_AGGRESSIVENESS_MUL;

 public:
  AutoEnhanceTransformation(const QImage& basis_image);
  virtual ~AutoEnhanceTransformation();

  QColor transform_pixel(const QColor& pixel_color) const;
  bool is_identity() const;

 private:
  ShadowDetailTransformation* shadow_transform_;
  ToneExpansionTransformation* tone_expansion_transform_;
};

/*!
 * \brief The ColorBalance class changes the colors in one go.
 * The brightnes, contrast saturation and hue value can be changed through one function.
 */
class ColorBalance
{
public:
    ColorBalance(qreal brightness, qreal contrast, qreal saturation, qreal hue);

    QColor transform_pixel(const QColor& pixel_color) const;

private:
    QVector4D transformBrightnes(const QVector4D& pixel) const;
    QVector4D transformContrast(const QVector4D& pixel) const;
    QVector4D transformSaturation(const QVector4D& pixel) const;
    QVector4D transformHue(const QVector4D& pixel) const;

    QVector4D h1;
    QVector4D h2;
    QVector4D h3;
    QVector4D s1;
    QVector4D s2;
    QVector4D s3;
    QVector4D b1;
    QVector4D b2;
    QVector4D b3;
    QVector4D c1;
    QVector4D c2;
    QVector4D c3;
};

#endif  // GALLERY_UTIL_IMAGING_H_

