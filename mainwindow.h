#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QScrollArea>
#include <QMap>
#include "imagepyramid.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLabel *imageLabel;
    QMap<QString,ImagePyramid*> images;

private slots:
    void OpenFile();
    void ChangeLayer(const QString&);
    void ChangeFile(const QString&);
};
#endif // MAINWINDOW_H
