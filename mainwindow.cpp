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
    QObject::connect(ui->comboBoxLayer, SIGNAL(currentIndexChanged(const QString&)), this,SLOT(ChangeLayer(const QString&)));
    QObject::connect(ui->comboBoxFile, SIGNAL(currentTextChanged(const QString&)),this, SLOT(ChangeFile(const QString&)));

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
        images.insert(name,new ImagePyramid(name,pyramid.count(),pyramid));

        ui->comboBoxFile->addItem(name);
        ui->comboBoxFile->setCurrentText(name);

        ui->comboBoxLayer->clear();
        for(int i = 0; i < pyramid.count(); i++)
            ui->comboBoxLayer->addItem(QString::number(i));

        ui->labelSize->setText(QString::number(image.width())+"x"+QString::number(image.height()));
    }
}

void MainWindow::ChangeLayer(const QString& layer)
{
    QString fileName = ui->comboBoxFile->currentText();
    ImageInfo imageInfo = images[fileName]->images[layer.toInt()];
    imageLabel->setPixmap(QPixmap::fromImage(imageInfo.image));
    imageLabel->resize(imageLabel->sizeHint());
    ui->labelSize->setText(QString::number(imageInfo.image.width())+"x"+QString::number(imageInfo.image.height()));
}

void MainWindow::ChangeFile(const QString& fileName)
{
    ImageInfo imageInfo = images[fileName]->images[0];
    int layersNum = images[fileName]->layerNum;

    ui->comboBoxLayer->clear();
    for(int i = 0; i < layersNum; i++)
        ui->comboBoxLayer->addItem(QString::number(i));
    ui->comboBoxLayer->setCurrentIndex(0);

    imageLabel->setPixmap(QPixmap::fromImage(imageInfo.image));
    imageLabel->resize(imageLabel->sizeHint());
    ui->labelSize->setText(QString::number(imageInfo.image.width())+"x"+QString::number(imageInfo.image.height()));
}

MainWindow::~MainWindow()
{
    delete imageLabel;
    delete ui;
}

