#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include "QuCLib/source/hexFileParser.h"

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = nullptr);

    struct Item {
        QString name;
        QString path;
        QuCLib::HexFileParser::Range range;
        uint32_t offset = 0;
    };

    void addInputFile(const Item &inputFileItem);
    void setOutputFile(const Item &outputFile);

    QList<Item> input() const;

    Item output() const;

private:
    QList<Item> _input;
    Item _output;
};

#endif // SETTINGS_H
