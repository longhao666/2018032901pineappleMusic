#include "songlist.h"

SongList::SongList()
{
    m_playSong = 0;
}

SongList::~SongList()
{

}

void SongList::addSong(std::string s)
{
    m_song.push_back(s);
}

void SongList::addLyric(std::string s)
{

}

void SongList::addSong(QString s)
{
    m_qsong.push_back(s);
}

void SongList::songClearAll()
{
    m_song.clear();
}

void SongList::qSongClearAll()
{
    m_qsong.clear();
}

void SongList::lyricClearAll()
{
    m_lyric.clear();
}

int SongList::getSongCount()
{
    return m_song.size();
}

void SongList::remoteSong(std::string s)
{

}

void SongList::remoteLyric(std::string s)
{

}

void SongList::displaySong()
{
    std::cout << m_song.size() << "lllll" << std::endl;
    for(int i=0; i<(int)m_song.size(); i++) {
        std::cout << "第"<< i << "首" << m_song.at(i) << std::endl;
    }
}

