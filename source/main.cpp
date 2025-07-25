#include "mainwindow.h"

#include <QApplication>
#include "logic/xmlReader.h"
#include "logic/fileMerger.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FileMerger fileMerger;
    if(argc > 1){
        QString settingsPath = QString(argv[1]);
        if(!settingsPath.isEmpty()){
            XmlReader reader(fileMerger.settings());
            reader.readFile(settingsPath);
            fileMerger.initializeFromSettings();
        }
    }

    MainWindow w{fileMerger};
    w.show();
    return a.exec();
}
