#ifndef FILEITEMWIDGET_H
#define FILEITEMWIDGET_H

#include <QWidget>
#include "logic/fileItem.h"

namespace Ui {
class FileItemWidget;
}

class FileItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileItemWidget(FileItem *fileItem, QWidget *parent = nullptr);
    ~FileItemWidget();

private slots:

private:
    Ui::FileItemWidget *ui;

    void _update(void);

    FileItem *_fileItem = nullptr;

    QString _formatRange(const QuCLib::HexFileParser::Range &range);
};

#endif // FILEITEMWIDGET_H
