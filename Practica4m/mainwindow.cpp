#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Práctica 4 - Programación de aplicaciones gráficas");
    setMinimumSize(600, 600);
    resize(600, 600);

    _viewer = new Viewer();

    setCentralWidget(_viewer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    QCoreApplication::exit() ;
}

void MainWindow::on_actionLoad_mesh_triggered()
{
    // Abrir un selector de archivo y cargar modelo en el visor
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Obj File"),"", tr("Obj files (*.obj)"));
    _viewer->loadModel(fileName.toLocal8Bit().data());
}

void MainWindow::on_actionActionStart_triggered()
{
    _viewer->startAnimation();
}

void MainWindow::on_actionStop_triggered()
{
    _viewer->stopAnimation();
}


void MainWindow::on_actionChange_Mode_triggered()
{
    if(_viewer->getType() == 0){
        _viewer->setType(1);
        this->actions().first()->setText("Text");
    }
    else
        _viewer->setType(0);

}
