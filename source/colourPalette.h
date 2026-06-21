#ifndef COLOUR_PALETTE_H
#define COLOUR_PALETTE_H

#include <QList>
#include <QColor>

class ColourPalette {
public:
    static inline QList<QColor> colours = {
        QColor(QRgb{0xfbe7c6}),
        QColor(QRgb{0xb4f8c8}),
        QColor(QRgb{0xa0e7e5}),
        QColor(QRgb{0xffaebc})
    };
};


#endif // COLOUR_PALETTE_H
