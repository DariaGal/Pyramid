#ifndef IMAGEPYRAMIDCONVERTER_H
#define IMAGEPYRAMIDCONVERTER_H
#include <QPixmap>
#include "imageinfo.h"

class ImagePyramidConverter
{
private:
    QVector<QImage> images;
    QImage original;
    QImage* ConvertImage(QImage current);
    QImage* ConvertImageSmooth(QImage);
public:
    ImagePyramidConverter(QImage image);
    QVector<ImageInfo> GetPyramid();
};

#endif // IMAGEPYRAMIDCONVERTER_H
