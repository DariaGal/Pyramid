#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QImageReader>
#include <QLayout>
#include <QGraphicsView>
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
    QImageReader reader(fileName);
    if(fileName != "")
    {
        QImageReader reader(fileName);
        QImage image = reader.read();
        if(image.isNull())
        {
            QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
            tr("Cannot load %1.").arg(QDir::toNativeSeparators(fileName)));
        }
        ui->comboBox->addItem(fileName);
        imageLabel->setPixmap(QPixmap::fromImage(image));
        imageLabel->resize(imageLabel->sizeHint());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

