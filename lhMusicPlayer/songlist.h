#ifndef SONGLIST_H
#define SONGLIST_H

#include <iostream>
#include <string>
#include <vector>
#include <QStringList>

class SongList
{
public:
    SongList();
    ~SongList();
    void addSong(std::string s);
    void addLyric(std::string s);
    void addSong(QString s);
    void songClearAll();
    void qSongClearAll();
    void lyricClearAll();
    int getSongCount();
    void remoteSong(std::string s);
    void remoteLyric(std::string s);
    void displaySong();


public:
    std::vector<std::string> m_song;
    std::vector<std::string> m_lyric;
    QStringList m_qsong;
    int m_playSong;

};

#endif // SONGLIST_H
