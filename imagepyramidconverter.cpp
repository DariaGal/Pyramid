#include "imagepyramidconverter.h"
#include <QDebug>
ImagePyramidConverter::ImagePyramidConverter(QImage image)
{
    original = image;
    images.push_back(image);
}

QVector<ImageInfo> ImagePyramidConverter::GetPyramid()
{
    QVector<ImageInfo> pyramid;
    QImage current = original;
    int layer = 0;
    while(current.width() > 1 && current.height() > 1)
    {
        pyramid.push_back(ImageInfo(layer,current.width(),current.height(),current));
        QImage *newImage = ConvertImage(current);
        current = *newImage;
        layer++;
    }
    return pyramid;
}

QImage* ImagePyramidConverter::ConvertImage(QImage current)
{
    int newWidth = (current.width()%2 ==0) ? current.width()/2 : current.width()/2+1;
    int newHeight = (current.height()%2 ==0) ? current.height()/2 : current.height()/2+1;

    QImage *newImage = new QImage(newWidth, newHeight,QImage::Format_RGB32);
    int i=0, j=0;
    for(int y = 0; y < current.height(); y=y+2)
    {
        j=0;
        for(int x = 0; x < current.width(); x=x+2)
        {
            QColor color = current.pixel(x,y);
            newImage->setPixelColor(j,i,color);
            j++;
        }
        i++;
    }
    return newImage;
}
