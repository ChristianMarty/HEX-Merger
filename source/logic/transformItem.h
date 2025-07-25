#ifndef TRANSFORMITEM_H
#define TRANSFORMITEM_H

#include "QuCLib/source/hexFileParser.h"
#include "logic/settings.h"

class TransformItem
{
public:
    static void applyTransform(QuCLib::HexFileParser &binary, const Settings::Transform &transform);

private:

    static void _applySetTransform(QuCLib::HexFileParser &binary, const Settings::Transform::Setting::Set &set);

};

#endif // TRANSFORMITEM_H
