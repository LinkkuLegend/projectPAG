#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "viewer.h"

namespace Ui
{
    class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow *ui;

    Viewer* _viewer;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:

public slots:

private slots:
    void on_actionExit_triggered();
    void on_actionLoad_mesh_triggered();
    void on_actionUse_Octree_triggered();
};

#endif // MAINWINDOW_H
