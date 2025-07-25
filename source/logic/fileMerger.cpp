#include "fileMerger.h"
#include "transformItem.h"

FileMerger::FileMerger(QObject *parent)
    : QObject{parent}
{}

void FileMerger::initializeFromSettings()
{
    qDeleteAll(_fileItemList);
    _fileItemList.clear();
    _outputBinary.clear();

    for(const Settings::Item &item: _settings.input()){
        FileItem *fileItem = new FileItem(item);
        _fileItemList.append(fileItem);

        for(QuCLib::HexFileParser::BinaryChunk binaryChunk: fileItem->binary().binary()){
            binaryChunk.offset += item.offset;
            _outputBinary.insert(binaryChunk);
        }
    }


    for(const Settings::Transform &transform: _settings.output().transform){
        TransformItem::applyTransform(_outputBinary, transform);
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

void FileMerger::clearSettings()
{
    _settings = Settings();
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
