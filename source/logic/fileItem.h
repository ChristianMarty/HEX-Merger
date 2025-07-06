#ifndef FILEITEM_H
#define FILEITEM_H

#include <QObject>
#include "QuCLib/source/hexFileParser.h"
#include "settings.h"

class FileItem : public QObject
{
    Q_OBJECT
public:
    explicit FileItem(const Settings::Item &item, QObject *parent = nullptr);

    QString filePath() const;
    const QuCLib::HexFileParser::Range &addressRange(void) const;

    QuCLib::HexFileParser &binary();
    Settings::Item item() const;

signals:
    void updated();

private:
    Settings::Item _item;
    QuCLib::HexFileParser _binary;
    uint16_t _offset = 0;

};

#endif // FILEITEM_H
