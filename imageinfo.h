#ifndef IMAGEINFO_H
#define IMAGEINFO_H
#include <QVector>
#include <QImage>

class ImageInfo
{
public:
    int layer;
    int width;
    int height;
    QImage image;
    ImageInfo(int layer, int width, int height, QImage image)
    {
        this->layer = layer;
        this->width = width;
        this->height = height;
        this->image = image;
    }
};

#endif // IMAGEINFO_H
