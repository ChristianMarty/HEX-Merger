#ifndef XMLREADER_H
#define XMLREADER_H

#include <QObject>
#include <QtXml>

#include "settings.h"

class XmlReader : public QObject
{
    Q_OBJECT
public:
    explicit XmlReader(Settings &settings, QObject *parent = nullptr);

    void readFile(QString path);

signals:

private:
    QDomDocument _document;
    QDomElement _root;

    Settings::Item _parseFileItem(QDomElement &item);
    Settings::Transform _parseTransformItem(QDomElement &item);

    QuCLib::HexFileParser::Range _parseRange(QDomElement &item);
    uint32_t _parseNumber(QString number);


    Settings &_settings;
};

#endif // XMLREADER_H
