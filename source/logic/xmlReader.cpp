#include "xmlReader.h"
#include "settings.h"

XmlReader::XmlReader(Settings &settings, QObject *parent)
    : QObject{parent}
    ,_settings{settings}
{}

void XmlReader::readFile(QString path)
{
    QFile file(path);
    if(!file.exists()){
        return;
    }
    if(!file.open(QIODevice::ReadOnly)){
        return;
    }
    _document.setContent(&file);
    file.close();

    QDomElement root = _document.documentElement();
    if(root.tagName() != "hex-merger"){
        return;
    }
    if(!root.hasAttribute("version")){
        return;
    }

    QString xmlVersion = root.attribute("version").toLower();
    if(xmlVersion != "1.0"){
        return;
    }

    QDomElement input = root.firstChildElement("input");
    while(!input.isNull()){
        _settings.addInputFile(_parseFileItem(input));
        input = input.nextSiblingElement("input");
    }

    QDomElement output = root.firstChildElement("output");
    if(!output.isNull()){
        _settings.setOutputFile(_parseFileItem(output));
    }

    return;
}

Settings::Item XmlReader::_parseFileItem(QDomElement &item)
{
    Settings::Item output;

    QDomElement name = item.firstChildElement("name");
    if(!name.isNull()){
        output.name = name.text().trimmed();
    }

    QDomElement path = item.firstChildElement("path");
    if(!path.isNull()){
        output.path = path.text().trimmed();
    }

    QDomElement offset = item.firstChildElement("offset");
    if(!offset.isNull()){
        output.offset = _parseNumber(offset.text());
    }

    QDomElement range = item.firstChildElement("range");
    if(!range.isNull()){
        output.range = _parseRange(range);
    }

    return output;
}

QuCLib::HexFileParser::Range XmlReader::_parseRange(QDomElement &item)
{
    QuCLib::HexFileParser::Range output;

    QDomElement minimum = item.firstChildElement("minimum");
    if(!minimum.isNull()){
        output.minimum = _parseNumber(minimum.text());
    }

    QDomElement maximum = item.firstChildElement("maximum");
    if(!maximum.isNull()){
        output.maximum = _parseNumber(maximum.text());
    }

    return output;
}

uint32_t XmlReader::_parseNumber(QString number)
{
    number= number.toLower().trimmed();
    uint32_t output;
    bool ok;
    if(number.startsWith("0x")){
        output = number.remove(0,2).toUInt(&ok,16);
    }else{
        output = number.toUInt(&ok,10);
    }

    if(!ok) return 0;
    return output;
}
