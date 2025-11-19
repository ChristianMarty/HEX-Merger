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

    QFileInfo fileInfo(path);
    QDir::setCurrent(fileInfo.absolutePath());

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
        QFileInfo fileInfo(path.text().trimmed());
        output.path = fileInfo.absoluteFilePath();
    }

    QDomElement offset = item.firstChildElement("offset");
    if(!offset.isNull()){
        output.offset = _parseNumber(offset.text());
    }

    QDomElement range = item.firstChildElement("range");
    if(!range.isNull()){
        output.range = _parseRange(range);
    }

    QDomElement transform = item.firstChildElement("transform");
    while(!transform.isNull()){
        output.transform.append(_parseTransformItem(transform));
        transform = transform.nextSiblingElement("transform");
    }

    return output;
}

Settings::Transform XmlReader::_parseTransformItem(QDomElement &item)
{
    if(!item.hasAttribute("type")){
        return Settings::Transform();
    }

    Settings::Transform transform;

    QDomElement name = item.firstChildElement("name");
    if(!name.isNull()){
        transform.name = name.text().trimmed();
    }

    QString type = item.attribute("type").toLower().trimmed();

    if(type == "set"){
        transform.type = Settings::TransformType::Set;

        QDomElement input = item.firstChildElement("input");
        if(!input.isNull()){
            transform.setting.set.inputValue = _parseNumber(input.text());
        }

        QDomElement output = item.firstChildElement("output");
        if(!output.isNull()){
            transform.setting.set.outputAddress = _parseNumber(output.text());
        }
    }

    return transform;
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
