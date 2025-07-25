#ifndef COLOURPALETTE_H
#define COLOURPALETTE_H

#include <QObject>
#include <QList>
#include <QColor>

class ColourPalette {
public:
    static inline QList<QColor> colours = {
        QColor("#fbe7c6"),
        QColor("#b4f8c8"),
        QColor("#a0e7e5"),
        QColor("#ffaebc")
    };
};


#endif // COLOURPALETTE_H
