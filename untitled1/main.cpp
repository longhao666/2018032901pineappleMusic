#include <iostream>
#include <fstream>
#include <cstdio>
//#include <ofstream>
#include <string>
#include <vector>
#include <streambuf>
#include <sstream>
#include <map>
#include <cstring>

using namespace std;

void fun2() {

    char buf[10] = {10,10,10,10,10,10,10,10,10,10};

    char str[] = "hello world!123";

    FILE *fp = fopen("tt1.dat","w+");
    if(fp == NULL) {
        printf("open is filed!");
        exit(-1);
    }
    fwrite(str,1,10,fp);
    fclose(fp);

    FILE *fp1 = fopen("tt2.dat","wb+");
    if(fp1 == NULL) {
        printf("open is filed!");
        exit(-1);
    }
    fwrite(str,10,1,fp);
    fclose(fp1);
}

void fun1() {
    int A[ 3 ][ 10 ];
    int i, j;
    ifstream input( "m1.txt", ios::in | ios::out);
    if( ! input )
    {
        cerr << "Open input file error!" << endl;
        exit( -1 );
    }
    ofstream output( "output.txt", ios::out );
    if( ! output )
    {
        cerr << "Open output file error!" << endl;
        exit( -1 );
    }
    for( i = 0; i < 3; i++ )
    {
        for( j = 0 ; j < 10; j++ )
        {
            input >> A[ i ][ j ];
        }
    }
    for( i = 0; i < 3; i++ )
    {
        for( j = 0 ; j < 10; j++ )
        {
            cout << A[ i ][ j ] <<" ";
        }
        cout << endl;
    }
    for( i = 0; i < 3; i++ )
    {
        for( j = 0 ; j < 10; j++ )
        {
            output << A[ i ][ j ] <<" ";
        }
        output << "\r\n";
    }
    input.close();
    output.close();
}

void fun3() {
#if 0
    fstream lrc;
    lrc.open("./kk.txt");
    lrc << "longhao";
    lrc.close();
#endif
#if 0
    ofstream b1;
    b1.open("./b1/txt");
    b1 << "hello";
    b1.close();
#endif
#if 0
    fstream lrc;
    lrc.open("./kk.txt");
    lrc << "longhao";
    lrc.close();
#endif
#if 0
    ofstream b1;
    b1.open("./b1/txt");
    b1 << "hello";
    b1.close();
#endif

    fstream t1("m3.txt", ios::out);
    if( ! t1 )
    {
        cerr << "Open m4.txt file error!" << endl;
        exit( -1 );
    }
    t1 << "bbhello";
    t1.close();

    fstream t2("./lrc/easy_love.lrc", ios::in);
    if( ! t2 )
    {
        cerr << "Open ./lrc/easy_love.lrc file error!" << endl;
        exit( -1 );
    }
    string s1("");
    string s2("");
    t2 >> s1;
    t2 >> s2;
    cout << s1 << s2 << " + 123" <<endl;
    t2.close();

    ofstream b1;
    b1.open("./b1.txt");
    if( ! t1 )
    {
        cout << "Open ./ll/b1.txt file error!" << endl;
        exit( -1 );
    }
    b1 << "hellojjbbbbbbbbbbbbbjj";
    b1.close();
}

void fun4();
void fun5();
void fun6();
void fun7();

int main()
{
    cout << "Hello World!" << endl;


//    fun1();
//    fun2();
//    fun3();
//    fun4();
    fun7();

    return 0;
}

void fun4() {
    std::vector<std::string> lrcString;
    fstream t2("./lrc/lonely_songing.lrc", ios::in);
    if( ! t2 )
    {
        cerr << "Open ./lrc/easy_love.lrc file error!" << endl;
        exit( -1 );
    }
    std::string str;
    while(t2 >> str) {
        lrcString.push_back(str);
        std::cout << str << std::endl;
    }
    t2.close();

}

void fun5() {
#if 0
    //使用char接收---#include<fstream>
    #include<fstream>
    std::ifstream t;
    int length = 0;
    t.open("./lrc/easy_love.lrc"); // open input file
    t.seekg(0,std::ios::end); // go to the end
    length = t.tellg(); // report location (this is the length)
    t.seekg(0,std::ios::beg);// go back to the beginning
    char* buffer = new char[length];// allocate memory for a buffer of appropriate dimension
    t.read(buffer,length);// read the whole file into the buffer
    t.close();// close file handle
    std::cout << buffer << std::endl;
#endif
#if 1
    //使用string接收

//    std::ifstream t("./lrc/easy_love.lrc");
//    std::string str((std::istreambuf_iterator<char>(t)),
//                    std::istreambuf_iterator<char>());
//    std::cout << str;
//    std::cout.flush();

    std::ifstream t("./lrc/easy_love.lrc");
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string contents(buffer.str());
    std::cout << contents;
    std::cout.flush();
#endif
}

void fun6() {
    std::map<int, string> lrc = {
                    { 2015, "Jim" },
                    { 2016, "Tom" },
                    { 2017, "Bob" },
                    { 2014, "kom" }};

    for(std::map<int, std::string>::iterator it=lrc.begin(); it!=lrc.end(); it++) {
        std::cout << it->first << "    " << it->second << std::endl;
    }

    std::map<string, string> lrc1 = {
                    { "方法", "Jim" },
                    { "安抚", "Tom" },
                    { "能否", "Bob" },
                    { "巅峰", "kom" }};

    for(std::map<string, std::string>::iterator it=lrc1.begin(); it!=lrc1.end(); it++) {
        std::cout << it->first << "    " << it->second << std::endl;
    }
}

void fun7() {
    std::map<int, std::string> lrc;
    std::ifstream t;
    int length = 0;
    char *str1[100]={0};
    int sec,min;
    int time2[5]={0,0,0,0,0};
    int i = 0,j = 0,k=0;
    t.open("./lrc/easy_love.lrc"); // open input file
    if(!t) {
        std::cout << "open failed" << std::endl;
        exit(-1);
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
    int c = lrc.size();
    std::cout << c << std::endl;
    for(std::map<int, std::string>::iterator it=lrc.begin(); it!=lrc.end(); it++) {
        std::cout << it->first << "    " << it->second << std::endl;
    }
    lrc.clear();
    c = lrc.size();
    std::cout << c << std::endl;
    if(lrc.empty()) {
        std::cout << "cNULL" << std::endl;
    }
}
