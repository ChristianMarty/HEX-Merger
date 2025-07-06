#include "fileItem.h"

FileItem::FileItem(const Settings::Item &item, QObject *parent)
    : QObject{parent}
    ,_item{item}
{
    _binary.clear();
    _binary.setMemorySize(_item.range.minimum, _item.range.maximum);
    _binary.setAddressGapSize(0x2000);
    _binary.setAddressAlignment(16);

    _binary.load(_item.path);
}

QString FileItem::filePath() const
{
    return _item.path;
}

const QuCLib::HexFileParser::Range &FileItem::addressRange() const
{
    return _binary.fileAddressRange();
}

QuCLib::HexFileParser &FileItem::binary()
{
    return _binary;
}

Settings::Item FileItem::item() const
{
    return _item;
}
