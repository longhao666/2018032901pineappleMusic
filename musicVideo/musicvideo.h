#ifndef MUSICVIDEO_H
#define MUSICVIDEO_H

#include "musicvideo_global.h"
#include <QWidget>

class MUSICVIDEOSHARED_EXPORT MusicVideo : public QWidget
{
    Q_OBJECT
public:
    MusicVideo(QWidget *parent = 0);
    ~MusicVideo();
};

#endif // MUSICVIDEO_H
