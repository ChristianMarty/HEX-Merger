#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include "main.h"

#include "logic/xmlReader.h"
#include "colourPalette.h"

MainWindow::MainWindow(FileMerger &fileMerger, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,_fileMerger{fileMerger}
{
    ui->setupUi(this);

    // "C:/Users/Christian/Raumsteuerung/HEX-Merger/source/file.hexmerger"
    // "C:/Users/Christian/Raumsteuerung/RoomBus/pc/kernelUpdate/merger.hexmerger"

    connect(&_fileMerger, &FileMerger::change, this, &MainWindow::on_fileChange);

    on_fileChange();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString path = QFileDialog::getOpenFileName(this,tr("Open Merger File"), "", tr("Settings (*.hexmerger)"));
    if(path.isEmpty()) return;

    _fileMerger.clearSettings();
    XmlReader reader(_fileMerger.settings());
    reader.readFile(path);
    _fileMerger.initializeFromSettings();
}

void MainWindow::on_fileChange()
{
    _updateFileList();
    _updateHexView();
}

void MainWindow::_updateHexView()
{
    ui->textEdit_hexView->clear();

    int coloursIndex = 0;

    QString text;
    for(const QuCLib::HexFileParser::BinaryChunk &item: _fileMerger.outputBinary().binary()){

        QString line = "<pre style=\"margin: 0; background-color:"+ColourPalette::colours[coloursIndex].name(QColor::HexRgb)+";\">";

        for(uint16_t i = 0; i<item.data.length(); i+=16){
            line += QString::number((uint16_t)item.offset+i,16).toUpper().rightJustified(8,'0').prepend("0x");
            line += "  : ";

            for(uint16_t j = 0; j<16; j++){
                if(i+j>=item.data.length()) break;
                line+=" "+QString::number((uint8_t)item.data.at(i+j),16).toUpper().rightJustified(2,'0');
                if(j==7) line += " ";
            }
            line += "\n";
        }
        line = line.mid(0,line.length()-1);
        line += "</pre>";
        text += line;

        coloursIndex++;
    }
    ui->textEdit_hexView->setHtml(text);
}

void MainWindow::_updateFileList()
{
    ui->listWidget_fileItems->clear();

    int coloursIndex = 0;

    for(FileItem *fileItem: _fileMerger.fileItemList()){
        QListWidgetItem *itemWidget = new QListWidgetItem(ui->listWidget_fileItems);
        FileItemWidget *fileItemWidget = new FileItemWidget(fileItem, ui->listWidget_fileItems);

        fileItemWidget->setBackground(ColourPalette::colours[coloursIndex].name(QColor::HexRgb));

        itemWidget->setSizeHint(fileItemWidget->sizeHint());
        ui->listWidget_fileItems->setItemWidget(itemWidget, fileItemWidget);

        coloursIndex++;
    }
}

void MainWindow::on_actionExport_triggered()
{
    QString path = _fileMerger.settings().output().path;
    if(path.isEmpty()) return;

    _fileMerger.outputBinary().saveToFile(path);
}

void MainWindow::on_actionExport_As_triggered()
{
    QString presetPath = _fileMerger.settings().output().path;
    QString path = QFileDialog::getSaveFileName(this,tr("Save HEX File"), presetPath, tr("Hex Files (*.hex)"));
    if(path.isEmpty()) return;

    _fileMerger.outputBinary().saveToFile(path);
}

