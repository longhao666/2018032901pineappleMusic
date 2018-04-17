#include "musicplayer.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MusicPlayer m;
    m.show();
    return a.exec();
}
