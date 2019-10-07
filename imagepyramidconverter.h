#ifndef IMAGEPYRAMIDCONVERTER_H
#define IMAGEPYRAMIDCONVERTER_H
#include <QPixmap>
#include "imageinfo.h"

class ImagePyramidConverter
{
private:
    QVector<QImage> images;
    QImage original;
public:
    ImagePyramidConverter(QImage image);
    QVector<ImageInfo> GetPyramid();
    QImage* ConvertImage(QImage current);
};

#endif // IMAGEPYRAMIDCONVERTER_H
