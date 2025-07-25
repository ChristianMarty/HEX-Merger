#include "transformItem.h"


void TransformItem::applyTransform(QuCLib::HexFileParser &binary, const Settings::Transform &transform)
{
    switch(transform.type){
        case Settings::TransformType::Undefined: break;
        case Settings::TransformType::Set: _applySetTransform(binary, transform.setting.set); break;
    }
}

void TransformItem::_applySetTransform(QuCLib::HexFileParser &binary, const Settings::Transform::Setting::Set &set)
{
    uint32_t value = set.inputValue;
    QByteArray valueArray;
    valueArray.append((char)(value&0xFF));
    valueArray.append((char)((value>>8)&0xFF));
    valueArray.append((char)((value>>16)&0xFF));
    valueArray.append((char)((value>>24)&0xFF));

    binary.replace(set.outputAddress, valueArray);
}
