#include "settings.h"

Settings::Settings(QObject *parent)
    : QObject{parent}
{}

void Settings::addInputFile(const Item &inputFileItem)
{
    _input.append(inputFileItem);
}

void Settings::setOutputFile(const Item &outputFile)
{
    _output = outputFile;
}

QList<Settings::Item> Settings::input() const
{
    return _input;
}

Settings::Item Settings::output() const
{
    return _output;
}
