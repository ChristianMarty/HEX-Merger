#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include "main.h"

#include "logic/xmlReader.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&fileMerger, &FileMerger::change, this, &MainWindow::on_fileChange);

    XmlReader reader(fileMerger.settings());
    reader.readFile("C:/Users/Christian/Raumsteuerung/HEX-Merger/source/file.xml");
    fileMerger.initializeFromSettings();

    _update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fileChange()
{
    _updateFileList();
    _update();
}
/*
void MainWindow::on_merge_button_clicked()
{
    uint32_t _newKernelOffset = 0x10C00;

    QByteArray kernelStart;
    kernelStart.append((char)(_newKernelOffset&0xFF));
    kernelStart.append((char)((_newKernelOffset>>8)&0xFF));
    kernelStart.append((char)((_newKernelOffset>>16)&0xFF));
    kernelStart.append((char)((_newKernelOffset>>24)&0xFF));

    _updaterBinary.replace(0x00010064,kernelStart);

    uint32_t size = _kernelBinary.binary().at(0).data.count()-4;
    QByteArray sizeArray;
    sizeArray.append((char)(size&0xFF));
    sizeArray.append((char)((size>>8)&0xFF));
    sizeArray.append((char)((size>>16)&0xFF));
    sizeArray.append((char)((size>>24)&0xFF));

    _updaterBinary.replace(0x00010068,sizeArray);


    _output.clear();
    _output.insert(_updaterBinary.binary().at(0));

    QuCLib::HexFileParser::binaryChunk kernel = _kernelBinary.binary().at(0);
    kernel.offset += _newKernelOffset;

    _output.insert(kernel);
    _output.saveToFile(_savePath);
}
*/

void MainWindow::_update()
{
    ui->plainTextEdit_hexView->clear();

    QString text;
    for(const QuCLib::HexFileParser::BinaryChunk &item: fileMerger.outputBinary().binary()){



        for(uint16_t i = 0; i<item.data.length(); i+=16){
            QString line = QString::number((uint16_t)item.offset+i,16).toUpper().rightJustified(4,'0').prepend("0x");
            line += "  : ";

            for(uint16_t j = 0; j<16; j++){
                if(i+j>=item.data.length()) break;
                line+=" "+QString::number((uint8_t)item.data.at(i+j),16).toUpper().rightJustified(2,'0');
            }
            text.append(line+"\n");
        }

    }
    ui->plainTextEdit_hexView->setPlainText(text);
}

void MainWindow::_updateFileList()
{
    ui->listWidget_fileItems->clear();

    for(FileItem *fileItem: fileMerger.fileItemList()){
        QListWidgetItem *itemWidget = new QListWidgetItem(ui->listWidget_fileItems);
        FileItemWidget *fileItemWidget = new FileItemWidget(fileItem, ui->listWidget_fileItems);

        itemWidget->setSizeHint(fileItemWidget->sizeHint());
        ui->listWidget_fileItems->setItemWidget(itemWidget, fileItemWidget);
    }
}

void MainWindow::on_pushButton_export_clicked()
{
    QString presetPath = fileMerger.settings().output().path;
    QString path = QFileDialog::getSaveFileName(this,tr("Save HEX File"), presetPath, tr("Hex Files (*.hex)"));
    if(path.isEmpty()) return;

    fileMerger.outputBinary().saveToFile(path);
}

