#ifndef FILEMERGER_H
#define FILEMERGER_H

#include <QObject>
#include "QuCLib/source/hexFileParser.h"
#include "logic/fileItem.h"
#include "settings.h"

class FileMerger : public QObject
{
    Q_OBJECT
public:
    explicit FileMerger(QObject *parent = nullptr);

    QuCLib::HexFileParser outputBinary() const;
    QList<FileItem *> fileItemList() const;

    Settings &settings();
    void clearSettings(void);
    void initializeFromSettings(void);

signals:
    void change(void);

private:
    Settings _settings;
    QList <FileItem*> _fileItemList;

    QuCLib::HexFileParser _outputBinary;

    void _update(void);
};

#endif // FILEMERGER_H
