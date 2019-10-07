#ifndef IMAGEPYRAMID_H
#define IMAGEPYRAMID_H
#include <QString>
#include "imageinfo.h"

class ImagePyramid
{
   public:
    QString fileName;
    QVector<ImageInfo> images;
    int layerNum;
    ImagePyramid(QString fileName, int layerNum, QVector<ImageInfo> images)
    {
        this->fileName = fileName;
        this->images = images;
        this->layerNum = layerNum;
    }
};

#endif // IMAGEPYRAMID_H
