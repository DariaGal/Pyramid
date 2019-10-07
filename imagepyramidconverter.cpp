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
        QImage *newImage = ConvertImageSmooth(current);
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
QImage* ImagePyramidConverter::ConvertImageSmooth(QImage current)
{
    double window[3][3] = {{0.5,0.75,0.5},
                          {0.75,1.0,0.75},
                          {0.5,0.75,0.5}};
    int newWidth = (current.width()%2 ==0) ? current.width()/2 : current.width()/2+1;
    int newHeight = (current.height()%2 ==0) ? current.height()/2 : current.height()/2+1;

    QImage *newImage = new QImage(newWidth, newHeight,QImage::Format_RGB32);
    int iNew=0, jNew=0;
    for(int y = 0; y < current.height(); y=y+2)
    {
        jNew=0;
        for(int x = 0; x < current.width(); x=x+2)
        {
            if(x > 0 && x< current.width()-1 && y > 0 && y < current.height() - 1)
            {
                double rTotal = 0;
                double gTotal = 0;
                double bTotal = 0;
                int i=0, j=0;
                for(int a = x-1; a <= x+1; a++)
                {
                    j=0;
                    for(int b = y-1; b <= y+1; b++)
                    {
                        QColor color = current.pixel(a,b);
                        rTotal+= color.red() * window[i][j];
                        gTotal+= color.green() * window[i][j];
                        bTotal+= color.blue() * window[i][j];
                        j++;
                    }
                    i++;
                }
                QColor color = QColor((int)rTotal/6,(int)gTotal/6,(int)bTotal/6);
                newImage->setPixelColor(jNew,iNew,color);
            }
            else
            {
                QColor color = current.pixel(x,y);
                newImage->setPixelColor(jNew,iNew,color);
            }
            jNew++;
        }
        iNew++;
    }
    return newImage;
}
