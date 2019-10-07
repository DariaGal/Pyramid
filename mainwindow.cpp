#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QImageReader>
#include <QLayout>
#include <QGraphicsView>
#include "imageinfo.h"
#include "imagepyramidconverter.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->action_OpenFile,SIGNAL(triggered()),this, SLOT(OpenFile()));

    imageLabel = new QLabel;
    ui->scrollArea->setWidget(imageLabel);
    imageLabel->setScaledContents(true);
}
void MainWindow::OpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"", tr("Images (*.jpg *.png)"));

    if(fileName != "")
    {
        QFileInfo fileInfo(fileName);
        QString name = fileInfo.fileName();

        QImageReader reader(fileName);
        QImage image = reader.read();
        if(image.isNull())
        {
            QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
            tr("Cannot load %1.").arg(QDir::toNativeSeparators(fileName)));
            return;
        }

        imageLabel->setPixmap(QPixmap::fromImage(image));
        imageLabel->resize(imageLabel->sizeHint());
        ImagePyramidConverter pyramidConverter = ImagePyramidConverter(image);
        QVector<ImageInfo> pyramid = pyramidConverter.GetPyramid();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

