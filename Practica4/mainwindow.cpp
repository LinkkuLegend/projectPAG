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
    QString fileName = QFileDialog::getOpenFileName(this,
                           tr("Open mesh"), ".",
                           tr("Compatible model files (*.obj)"));

    _viewer->loadModel(fileName.toUtf8().data());
}

void MainWindow::on_actionUse_Octree_triggered()
{
    _viewer->useOctree(!_viewer->octreeUsed());
    //Buscar la acción para cambiar el nombre
    QList<QAction*> aux = this->findChildren<QAction*>("actionUse_Octree");
    QAction* act = aux.first();

    //Poner el nombre que corresponda
    if ( _viewer->octreeUsed())
        act->setIconText("Use Bounding Box");
    else
        act->setIconText("Use Octree");
}
