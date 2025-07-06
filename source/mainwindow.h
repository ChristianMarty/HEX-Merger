#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ui/fileItemWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_fileChange(void);

    void on_pushButton_export_clicked();

private:
    Ui::MainWindow *ui;

    void _update(void);
    void _updateFileList(void);

};
#endif // MAINWINDOW_H
