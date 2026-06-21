#include "xmlReader.h"
#include "settings.h"

#define xml_hexMerger QStringLiteral("hex-merger")
#define xml_version QStringLiteral("version")
#define xml_input QStringLiteral("input")
#define xml_output QStringLiteral("output")
#define xml_name QStringLiteral("name")
#define xml_type QStringLiteral("type")
#define xml_path QStringLiteral("path")
#define xml_offset QStringLiteral("offset")
#define xml_range QStringLiteral("range")
#define xml_set QStringLiteral("set")
#define xml_transform QStringLiteral("transform")
#define xml_minimum QStringLiteral("minimum")
#define xml_maximum QStringLiteral("maximum")

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
    if(root.tagName() != xml_hexMerger){
        return;
    }
    if(!root.hasAttribute(xml_version)){
        return;
    }

    QString xmlVersion = root.attribute(xml_version).toLower();
    if(xmlVersion != QStringLiteral("1.0")){
        return;
    }

    QDomElement input = root.firstChildElement(xml_input);
    while(!input.isNull()){
        _settings.addInputFile(_parseFileItem(input));
        input = input.nextSiblingElement(xml_input);
    }

    QDomElement output = root.firstChildElement(xml_output);
    if(!output.isNull()){
        _settings.setOutputFile(_parseFileItem(output));
    }

    return;
}

Settings::Item XmlReader::_parseFileItem(QDomElement &item)
{
    Settings::Item output;

    QDomElement name = item.firstChildElement(xml_name);
    if(!name.isNull()){
        output.name = name.text().trimmed();
    }

    QDomElement path = item.firstChildElement(xml_path);
    if(!path.isNull()){
        QFileInfo fileInfo(path.text().trimmed());
        output.path = fileInfo.absoluteFilePath();
    }

    QDomElement offset = item.firstChildElement(xml_offset);
    if(!offset.isNull()){
        output.offset = _parseNumber(offset.text());
    }

    QDomElement range = item.firstChildElement(xml_range);
    if(!range.isNull()){
        output.range = _parseRange(range);
    }

    QDomElement transform = item.firstChildElement(xml_transform);
    while(!transform.isNull()){
        output.transform.append(_parseTransformItem(transform));
        transform = transform.nextSiblingElement(xml_transform);
    }

    return output;
}

Settings::Transform XmlReader::_parseTransformItem(QDomElement &item)
{
    if(!item.hasAttribute(xml_type)){
        return Settings::Transform();
    }

    Settings::Transform transform;

    QDomElement name = item.firstChildElement(xml_name);
    if(!name.isNull()){
        transform.name = name.text().trimmed();
    }

    QString type = item.attribute(xml_type).toLower().trimmed();

    if(type == xml_set){
        transform.type = Settings::TransformType::Set;

        QDomElement input = item.firstChildElement(xml_input);
        if(!input.isNull()){
            transform.setting.set.inputValue = _parseNumber(input.text());
        }

        QDomElement output = item.firstChildElement(xml_output);
        if(!output.isNull()){
            transform.setting.set.outputAddress = _parseNumber(output.text());
        }
    }

    return transform;
}

QuCLib::HexFileParser::Range XmlReader::_parseRange(QDomElement &item)
{
    QuCLib::HexFileParser::Range output;

    QDomElement minimum = item.firstChildElement(xml_minimum);
    if(!minimum.isNull()){
        output.minimum = _parseNumber(minimum.text());
    }

    QDomElement maximum = item.firstChildElement(xml_maximum);
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
    if(number.startsWith(QStringLiteral("0x"))){
        output = number.remove(0,2).toUInt(&ok,16);
    }else{
        output = number.toUInt(&ok,10);
    }

    if(!ok) return 0;
    return output;
}
