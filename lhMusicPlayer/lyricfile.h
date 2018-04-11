#ifndef LYRICFILE_H
#define LYRICFILE_H

#include <QtCore/qglobal.h>
#include <map>
#include <string>

typedef std::map<int, std::string> LRC;

class Q_DECL_EXPORT SongLyric
{
public:
    SongLyric();
    ~SongLyric();
    bool getLyric(const char *path);

public:
    int lrcCount = 0;
    LRC lrc;
};



#endif // LYRICFILE_H
