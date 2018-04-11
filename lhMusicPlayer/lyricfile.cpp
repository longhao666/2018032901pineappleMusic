#include "lyricfile.h"
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>

SongLyric::SongLyric() {

}

SongLyric::~SongLyric() {

}

bool SongLyric::getLyric(const char *path) {
    std::ifstream t;
    int length = 0;
    char *str1[100]={0};
    int sec,min;
    int time2[5]={0,0,0,0,0};
    int i = 0,j = 0,k=0;
    t.open(path); // open input file
    if(!t) {
        printf("open failed");
        return false;
    }
    t.seekg(0,std::ios::end); // go to the end
    length = t.tellg(); // report location (this is the length)
    t.seekg(0,std::ios::beg);// go back to the beginning
    char* buffer = new char[length];// allocate memory for a buffer of appropriate dimension
    t.read(buffer,length);// read the whole file into the buffer
    t.close();// close file handle
//    std::cout << buffer << std::endl;
    str1[j]=strtok(buffer,"\r\n");
    while(str1[j]!=NULL){
        str1[++j]=strtok(NULL,"\r\n");
    }
    lrc[-4] = std::string(str1[0]);
    lrc[-3] = std::string(str1[1]);
    lrc[-2] = std::string(str1[2]);
    lrc[-1] = std::string(str1[3]);
    for(i=4;i<j;i++){
        while(*str1[i]=='['){
            sscanf(str1[i],"[%2d:%2d",&min,&sec);
            time2[k++]=min*60+sec;
            str1[i]+=10;
        }
        for(;k>0;k--){
            lrc[time2[k-1]] = std::string(str1[i]);
        }
    }
    delete buffer;
    lrcCount = (int)lrc.size();
#if 0
    for(std::map<int, std::string>::iterator it=lrc.begin(); it!=lrc.end(); it++) {
        std::cout << it->first << "    " << it->second << std::endl;
    }
#endif
    return true;

}
