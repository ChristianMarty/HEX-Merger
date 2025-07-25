#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include "QuCLib/source/hexFileParser.h"

class Settings
{
public:
    explicit Settings(void);

    enum class TransformType{
        Undefined,
        Set
    };

    struct Transform {
        QString name;
        TransformType type = TransformType::Undefined;
        union Setting {
            struct Set {
                uint32_t inputValue;
                uint32_t outputAddress;
            }set;
        } setting;
    };

    struct Item {
        QString name;
        QString path;
        QuCLib::HexFileParser::Range range;
        uint32_t offset = 0;
        QList<Transform> transform;
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
