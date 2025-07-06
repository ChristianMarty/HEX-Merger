#include "fileItemWidget.h"
#include "ui_fileItemWidget.h"
#include <QFileInfo>

#include "main.h"

FileItemWidget::FileItemWidget(FileItem *fileItem,  QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FileItemWidget)
{
    ui->setupUi(this);
    _fileItem = fileItem;

    _update();
}

FileItemWidget::~FileItemWidget()
{
    delete ui;
}

void FileItemWidget::_update()
{
    const QFileInfo info(_fileItem->filePath());

    const QuCLib::HexFileParser &binary = _fileItem->binary();

    ui->label_path->setText(info.fileName());
    ui->label_path->setToolTip(_fileItem->filePath());

    ui->label_name->setText(_fileItem->item().name);

    ui->label_fileRange->setText(_formatRange(binary.fileAddressRange()));
    ui->label_loadedRange->setText(_formatRange(binary.binaryAddressRange()));

    ui->label_offset->setText("0x"+QString::number(_fileItem->item().offset, 16).rightJustified(8,'0').toUpper());

    ui->plainTextEdit_errors->clear();
    if(binary.errorCount()){
        ui->label_errors->setVisible(true);
        ui->line_errors->setVisible(true);
        ui->plainTextEdit_errors->setVisible(true);

        for(const QuCLib::HexFileParser::FileError &fileError: binary.errors()){
            QString line = "Line "+QString::number(fileError.lineIndex)+" :";
            line += QuCLib::HexFileParser::errorMessage(fileError);
            ui->plainTextEdit_errors->appendPlainText(line);
        }
    }else{
        ui->label_errors->setVisible(false);
        ui->line_errors->setVisible(false);
        ui->plainTextEdit_errors->setVisible(false);
    }
}

QString FileItemWidget::_formatRange(const QuCLib::HexFileParser::Range &range)
{
    QString addressRange = "0x"+QString::number(range.minimum,16).rightJustified(8,'0').toUpper();
    addressRange += " - 0x"+QString::number(range.maximum,16).rightJustified(8,'0').toUpper();

    return addressRange;
}

