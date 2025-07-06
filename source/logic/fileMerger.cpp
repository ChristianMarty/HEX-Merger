#include "fileMerger.h"

FileMerger::FileMerger(QObject *parent)
    : QObject{parent}
{}

void FileMerger::initializeFromSettings()
{
    for(const Settings::Item &item: _settings.input()){
        FileItem *fileItem = new FileItem(item);
        _fileItemList.append(fileItem);

        for(QuCLib::HexFileParser::BinaryChunk binaryChunk: fileItem->binary().binary()){
            binaryChunk.offset += item.offset;
            _outputBinary.insert(binaryChunk);
        }
    }

    emit change();
}

QuCLib::HexFileParser FileMerger::outputBinary() const
{
    return _outputBinary;
}

QList<FileItem *> FileMerger::fileItemList() const
{
    return _fileItemList;
}

Settings &FileMerger::settings()
{
    return _settings;
}

void FileMerger::_update()
{
    _outputBinary.clear();

    for(auto item: _fileItemList){
        QuCLib::HexFileParser::BinaryChunk binaryChunk = item->binary().binary().at(0);
        binaryChunk.offset = item->item().offset;

        _outputBinary.insert(binaryChunk);
    }
}
