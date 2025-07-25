#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ui/fileItemWidget.h"
#include "logic/fileMerger.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(FileMerger &fileMerger, QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_fileChange(void);

    void on_actionOpen_triggered();

    void on_actionExport_triggered();
    void on_actionExport_As_triggered();

private:
    Ui::MainWindow *ui;
    FileMerger &_fileMerger;

    void _updateHexView(void);
    void _updateFileList(void);

};
#endif // MAINWINDOW_H
