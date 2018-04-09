#include "music.h"
#include "ui_music.h"
#include <QFileDialog>
#include <QDebug>
#include <QFileInfo>
#include <QStringList>
#include <QSound>
#include <QString>
#include <QPaintEvent>
#include <QPainter>
Music::Music(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Music)
{
    ui->setupUi(this);

    this->lastTime = 0;

//    this->setWindowFlags((Qt::FramelessWindowHint));//将窗口边框去掉生成无边框的窗口
    //this->setWindowOpacity(0.2);//设置透明度  这个是可以的
    //this->setAttribute(Qt::WA_TranslucentBackground,true);
    ui->textEditShowIrc->setFocusPolicy(Qt::NoFocus);
    ui->textEditShowMes->setFocusPolicy(Qt::NoFocus);
    this->setAttribute(Qt::WA_TranslucentBackground, true);//设置属性
    //this->setGeometry(40,60,700,400);
    this->currentFlag = 0;//当前歌曲
    this->backNum = 0;
    this->volumvFlag = 20;
    ui->horizontalSliderVolumn->setValue(this->volumvFlag);
    this->songInfo.curTime = 0;
    this->songInfo.percent = 0;
    this->songInfo.songLen = 0;


    this->process = new QProcess();
    connect(this->process,SIGNAL(readyReadStandardOutput()),this,
            SLOT(getMessage()));
    process->setProcessChannelMode(QProcess::MergedChannels);

    this->musicPath ="../music/";//音乐路径
    this->Dir = (this->musicPath);//找到路径
    getFile(this->Dir);//将歌词歌名保存

    ircPath="../lrc/";//歌词路径
    dirLrc=(ircPath);
    getFile(dirLrc);//保留歌词文件名

    this->timer = new QTimer(this);
    connect(this->timer,SIGNAL(timeout()),
            this,SLOT(doTimeOut()));

    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(pressList(int)));
    connect(ui->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,
            SLOT(pressListPlay(QListWidgetItem*)));

}

Music::~Music()
{
    delete this->process;
    delete ui;
}

void Music::paintEvent(QPaintEvent *)
{
    const char *backGround[10]={
                           "../image/n14.png",
                           "../image/n2.png",
                           "../image/n4.png",
                           //"../image/n12.png",
                           "../image/b8.png",
                           //"../image/n10.png",
                           "../image/n9.png",
                           "../image/n3.png",
                           "../image/n1.png",
                           "../image/n8.png",
                           "../image/n5.png",
                           //"../image/n11.png",
                           "../image/n15.png"
    };
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),
                       QPixmap(backGround[this->backNum]));
}

void Music::getFile(QDir &dir)
{
    QFileInfo *finfo;
    static int j=0;
    bool findSong = false;
   // bool next = false;



    if(dir == this->Dir)//保存歌名
    {
        qDebug()<<"music==="<<this->Dir.count();
        for(int i= 0;i<this->Dir.count();i++)
        {
            finfo = new QFileInfo(Dir.filePath(Dir[i]));
            if(finfo->fileName()==".")//linux的隐藏文件去掉"." 和".."
                continue;
            if(finfo->fileName()==QString(".."))
                continue;
            for(QMap<int,QListWidgetItem *>::const_iterator find = songMap.begin();
            find != songMap.end(); find++)
            {
                QListWidgetItem * findItem = find.value();
                //qDebug()<<"findItem.text = "<<findItem->text();
                if(findItem->text() == finfo->fileName())
                {
                     findSong = true;
                     break;
                }
                else
                {
                     findSong = false;
                }
            }

//            if(findSong == true && this->backNum != 0)
//            {
//                qDebug()<<"++++++++++++++++";

//                for(int i = 0 ; i<songMap.count();i++)
//                {

//                    this->item = new QListWidgetItem(ui->listWidget);
//                    QFont font;
//                    font.setPointSize(12);
//                    font.setBold(true);
//                    font.setFamily("隶书");
//                    this->item->setFont(font);

//                    if(this->backNum == 1)
//                    {
//                        this->item->setTextColor(Qt::blue);

//                    }
//                    if(this->backNum == 2)
//                    {
//                        this->item->setTextColor(Qt::magenta);

//                    }
//                    if(this->backNum == 3)
//                    {
//                        this->item->setTextColor(Qt::red);

//                    }
//                    if(this->backNum == 4)
//                    {
//                        this->item->setTextColor(Qt::red);

//                    }
//                    if(this->backNum == 5)
//                    {
//                        this->item->setTextColor(Qt::green);
//                    }


//                    QListWidgetItem * findItem = this->songMap.value(i);;
//                    //qDebug()<<"findItem.text = "<<findItem->text();

//                    this->item->setText(findItem->text());
//                    //this->songMap.insert(i,this->item);
//                }
//            }

            if(findSong == false)
            {
                //next = true;

                {
                   this->item = new QListWidgetItem(ui->listWidget);
                   QFont font;
                   font.setPointSize(12);
                   font.setFamily("黑体");
                   font.setBold(true);
                   this->item->setFont(font);
                   if(this->backNum == 0)
                   {
                       this->item->setTextColor(Qt::black);
                   }
//                   if(this->backNum == 1)
//                   {
//                       this->item->setTextColor(Qt::blue);

//                   }
//                   if(this->backNum == 2)
//                   {
//                       this->item->setTextColor(Qt::magenta);

//                   }
//                   if(this->backNum == 3)
//                   {
//                       this->item->setTextColor(Qt::red);

//                   }
//                   if(this->backNum == 4)
//                   {
//                       this->item->setTextColor(Qt::red);

//                   }
//                   if(this->backNum == 5)
//                   {
//                       this->item->setTextColor(Qt::green);
//                   }
                }


                this->item->setText(finfo->fileName());
                this->songMap.insert(j,this->item);
                j++;
             }




        }
        //songMap = songMap2;
    }

    if(dir == this->dirLrc)
    {
        j=0;
        for(int i=0;i<dirLrc.count();i++)
        {
            finfo = new QFileInfo(dirLrc[i]);
            if(finfo->fileName()==".")
                continue;
            else if(finfo->fileName()=="..")
                continue;
            else
            {
                if(finfo->fileName().section('.',-1)=="lrc")
                {
                    lrcMap.insert(j,finfo->fileName().toUtf8());
                    j++;
                }
            }
        }
    }

}

void Music::initPlay()
{

    for(int i=0;i<this->songMap.count();i++)
    {
        if(songMap[i]->isSelected() == true)
        {
             break;
        }
    }
    QString cmd="./mplayer_arm -slave -quiet -zoom "+musicPath;
    //mplayer_arm是MPLAYER的可执行文件
    cmd=cmd+songMap[this->currentFlag]->text();
    songMap[this->currentFlag]->setSelected(true);//当前被选中的歌
    qDebug()<<"cmd = "<<cmd;
    process->start(cmd);
    timer->start(100);

    ui->textEditShowIrc->clear();

    if(readLrcFile(songMap[this->currentFlag]->text())==1)
       showIrc();
    else
    {
       ui->textEditShowIrc->setText("没有找到相对应的歌词");
    }

}

void Music::doTimeOut()//往进程中写入命令
{
    process->write("get_time_pos\n");
    process->write("get_percent_pos\n");
    process->write("get_time_length\n");
    process->write("get_meta_title\n");
    process->write("get_meta_album\n");
    process->write("get_meta_artist\n");


}

void Music::getMessage()
{
    while(this->process->canReadLine())
    {
        QString msg = this->process->readLine();
//        qDebug()<<"msg===="<<msg;
        if(msg.startsWith("ANS_TIME_POSITION"))
        {
            msg.remove(0, 18);//杀掉多余的内
            this->songInfo.curTime = msg.toFloat();

        }
        if(msg.startsWith("ANS_LENGTH"))
        {
            msg.remove(0, 11); // vire ANS_LENGTH=
            this->songInfo.songLen = msg.toFloat();
            //qDebug()<<"lenth==="<<this->songInfo.songLen;
        }

        if(msg.startsWith("ANS_PERCENT_POSITION=")) //当前播放百分比
        {
            msg.remove(0, 21); //
            songInfo.percent=msg.toInt();
        }
        if(msg.startsWith("ANS_META_TITLE=")) //歌曲名
        {
            msg.remove(0, 15); //
            msg.replace(QByteArray("'"), QByteArray(""));
            msg.replace(QByteArray(" "), QByteArray(""));
            msg.replace(QByteArray("\n"), QByteArray(""));//去掉换行等
            msg.replace(QByteArray("\r"), QByteArray(""));
            songInfo.fileName=msg;
        }
        if(msg.startsWith("ANS_META_ALBUM=")) //专辑
        {
            msg.remove(0, 16); //
            msg.replace(QByteArray("'"), QByteArray(""));
            msg.replace(QByteArray(" "), QByteArray(""));
            msg.replace(QByteArray("\n"), QByteArray(""));
            msg.replace(QByteArray("\r"), QByteArray(""));
            songInfo.album=msg;
        }
        if(msg.startsWith("ANS_META_ARTIST=")) //演唱者
        {
            msg.remove(0, 16); // ANS_PERCENT_POSITION=
            msg.replace(QByteArray("'"), QByteArray(""));
            msg.replace(QByteArray(" "), QByteArray(""));
            msg.replace(QByteArray("\n"), QByteArray(""));
            msg.replace(QByteArray("\r"), QByteArray(""));
            songInfo.artist=msg;
        }
        showMessage();//显示歌曲相关信息
    }
}

void Music::showMessage()
{
    int currentTime = int(this->songInfo.curTime);
    int h = currentTime/60;
    int m = currentTime%60;

    int songLen = this->songInfo.songLen;
    int hL = songLen/60;
    int mL = songLen%60;
    ui->textEditShowMes->setFontPointSize(8);
    ui->textEditShowMes->setTextColor(Qt::blue);
    ui->textEditShowMes->setText(QString("歌名:%1").arg(songInfo.fileName));
    ui->textEditShowMes->append(QString("作者:%1").arg(songInfo.artist));
    ui->textEditShowMes->append(QString("专辑:")+songInfo.album);
    ui->textEditShowMes->append(QString("歌曲总时间%1:%2").arg(hL).arg(mL));
    ui->textEditShowMes->append(QString("歌曲播放时间%1:%2").arg(h).arg(m));
    ui->horizontalSlider->setValue(songInfo.percent);
    showIrc();//显示歌词


//    int b = int (this->songInfo.curTime);

//    if(b == (this->songInfo.songLen-22))
//    {

//        this->songInfo.curTime = 0;

//       // qDebug()<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<this->currentFlag;
//        if(this->currentFlag < (this->Dir.count()-3))
//            this->currentFlag++;

//        this->process->close();
//        this->initPlay();
//       //return;
//    }

    int a = int (this->songInfo.curTime);

    if(a == (this->songInfo.songLen-1))
    {

        this->songInfo.curTime = 0;

       // qDebug()<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<this->currentFlag;
        if(this->currentFlag < (this->Dir.count()-3))
            this->currentFlag++;

        this->process->close();
        this->initPlay();
       //return;
    }
}

void Music::showIrc()
{
//    if(readLrcFile(songMap[this->currentFlag]->text())!=1)
//        break;

    ui->textEditShowIrc->setFontPointSize(9);
    if(lrcMap.count()<=0)
        return ;
    float t=songInfo.curTime;
    static float tn=-1;
    QMap<float,QString>::iterator i;//用来存储当前歌曲
    if(tn==t)
        return ;
    static int num=0;
     QString str ;


     //if(lrcMap[t-5] != NULL)
     //{

    if( lrcMap[t] != NULL)
    //if(str != lrcMap[t] )
    {
          qDebug()<<"*******"<<lrcMap[t]<<"t==="<<t<<"aaat=="<<this->lastTime;

        //qDebug()<<"t===="<<t<<"tn========="<<tn;
        //qDebug()<<"lrcmap===="<<lrcMap[t];
       // str = lrcMap[t];
      if(num==0)
        {
          ui->textEditShowIrc->setTextColor(QColor(Qt::magenta));
          ui->textEditShowIrc->setText(lrcMap[t]);
          i=lrcMap.find(t);//存储当前的歌词
          //qDebug()<<"%%%%%%%%%%%%%"<<"t==="<<t;
          tn=t;num++;
        }
      else if(num==1)
      {
          //qDebug()<<"####&&&&&&&&&&&&&&&&&&&&&#"<<lrcMap[t];
          ui->textEditShowIrc->setTextColor(QColor(Qt::blue));
          ui->textEditShowIrc->setText(lrcMap[ tn]);
          ui->textEditShowIrc->setTextColor(QColor(Qt::magenta));
          ui->textEditShowIrc->append(lrcMap[t]);
          tn=t;num++;
      }
      else if(num==2)
      {
          //qDebug()<<"@@@@@@@@@@@@@@@@@@@@@@@"<<lrcMap[t];
          ui->textEditShowIrc->setTextColor(QColor(Qt::blue));
          ui->textEditShowIrc->setText(lrcMap[ tn ]);
          ui->textEditShowIrc->setTextColor(QColor(Qt::magenta));
          ui->textEditShowIrc->append(lrcMap[t]);
          ui->textEditShowIrc->setTextColor(QColor(Qt::blue));
          i=lrcMap.find(t);//找到当前的歌词 并存储
          if( ((i++).value()!=NULL) && (i!=lrcMap.end()))//i++显示
            ui->textEditShowIrc->append( i.value() );
          tn=t;num++;
          //qDebug()<<"i==22222===="<<i.value();
      }
      else if(num==3)
      {
          //qDebug()<<"@@@@@@@@@@@@@@@@@@@@@@@"<<lrcMap[t];
          ui->textEditShowIrc->setTextColor(QColor(Qt::blue));
          ui->textEditShowIrc->setText(lrcMap[ tn ]);
          ui->textEditShowIrc->setTextColor(QColor(Qt::magenta));
          ui->textEditShowIrc->append(lrcMap[t]);
           if( t < (this->lastTime))
          {
             ui->textEditShowIrc->setTextColor(QColor(Qt::blue));
             i=lrcMap.find(t);//找到当前的歌词 并存储
             if( ((i++).value()!=NULL) && (i!=lrcMap.end()))//i++显示
               ui->textEditShowIrc->append( i.value() );
             tn=t;
             if( ((i++).value()!=NULL) && (i!=lrcMap.end()))//i++显示
               ui->textEditShowIrc->append( i.value() );
           }
//           if(t>this->aaaaat+1)
//           {
//               ui->textEditShowIrc->clear();
//           }

      }
    }
// }

//    ui->textEditShowIrc->update();
}

int Music::readLrcFile(QString lrcName)
{
    lrcName.replace(".mp3",".lrc");
    QString filePath=ircPath+lrcName;
    QString text;
    QString msg;
    QString tm;
    float lrcTime=0;
    QFile lrcFile(filePath);
    QMapIterator<float,QString> i(lrcMap);

    for(;i.hasNext();)
    {
        lrcMap.remove(i.peekNext().key());
        i.next();
    }

    if(lrcFile.open(QIODevice::ReadOnly)==false)
    {
        return 0;
    }

    QTextStream stream(&lrcFile);

   // while(!lrcFile.atEnd())

    while(stream.atEnd()==0)//还没到尾
    {

        text=stream.readLine();

        int i=0;
        //qDebug()<<"text===="<<text.section(']',-1);
        if((msg=text.section(']',-1)).isEmpty()==true)//从后面数倒数第一，倒数第二
        {
           continue;
        }

        while((tm=text.section('[',-1-i,-1-i)).isEmpty()==false)
        {
            //qDebug()<<"isdigit==========="<<tm[0].isDigit()<<tm[0]<<tm.left(2)<<tm.at(3)<<tm.at(4);
            if(tm[0].isDigit()==false)
                lrcTime=0;
            if(tm[0].isDigit()==true)
            {
                lrcTime=(tm.left(2).toInt())*60+(QString(tm.at(3)).toInt())*10
                        +QString(tm.at(4)).toInt()
                        +(QString(tm.at(6)).toFloat()*0.1);
                msg.replace(QByteArray("\r"), QByteArray(""));
                msg.replace(QByteArray("\n"), QByteArray(""));


                if(lrcTime>=this->lastTime)
                    this->lastTime = lrcTime;
              //  qDebug()<<lrcTime<<msg;
            }
           // QString msg = QTextCodec::codecForName("GB2312")->toUnicode(msg.toLatin1());
            lrcMap.insert(lrcTime,msg);
            i++;

        }
    }
    return 1;
}

QStringList Music::readFile(QString fileName)
{
    QStringList list;
        QFile file(QString("../lrc/%1").arg(fileName));
        if(file.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&file);
            while(!stream.atEnd())
            {
                //line+=stream.readLine();//原来的返回类型
                list.append(stream.readLine());//将字符串追加
            }
        }
        return list;
}

void Music::on_pushButton_2_clicked()
{
    this->process->close();
    this->close();
}

void Music::on_pushButtonStart_clicked()//开始
{
    //ui->pushButton->setEnabled(false);
    static bool start=true;

    if(this->backNum == 3)
    {
        QIcon icon;
        if(start==true)
        {
          icon.addFile(QString::fromUtf8("../image/play1.png"), QSize(), QIcon::Normal, QIcon::Off);
          ui->pushButtonStart->setIcon(icon);
          //process->write("mute 1\n");//静音

          start=false;
          this->timer->stop();
          this->process->write("pause\n");
        }
        else
        {
            start=true;
            icon.addFile(QString::fromUtf8("../image/pause1.png"), QSize(), QIcon::Normal, QIcon::Off);
            ui->pushButtonStart->setIcon(icon);

            initPlay();

            ///process->write("mute 0\n");
        }
    }

    else if(this->backNum == 1 ||this->backNum == 4)
    {
        QIcon icon;
        if(start==true)
        {
          icon.addFile(QString::fromUtf8("../image/2.png"), QSize(), QIcon::Normal, QIcon::Off);
          ui->pushButtonStart->setIcon(icon);
          //process->write("mute 1\n");//静音
          start=false;
          this->timer->stop();
          this->process->write("pause\n");

        }
        else
        {
            start=true;
            icon.addFile(QString::fromUtf8("../image/1.png"), QSize(), QIcon::Normal, QIcon::Off);
            ui->pushButtonStart->setIcon(icon);

            initPlay();

            ///process->write("mute 0\n");
        }
    }

    else if(this->backNum == 9)
    {
        QIcon icon;
        if(start==true)
        {
          icon.addFile(QString::fromUtf8("../image/play.png"), QSize(), QIcon::Normal, QIcon::Off);
          ui->pushButtonStart->setIcon(icon);
          //process->write("mute 1\n");//静音
          start=false;
          this->timer->stop();
          this->process->write("pause\n");
        }
        else
        {
            start=true;
            icon.addFile(QString::fromUtf8("../image/pause.png"), QSize(), QIcon::Normal, QIcon::Off);
            ui->pushButtonStart->setIcon(icon);


            initPlay();

            ///process->write("mute 0\n");
        }
    }
    else
    {
        QIcon icon;
        if(start==true)
        {
          icon.addFile(QString::fromUtf8("../image/pausee.png"), QSize(), QIcon::Normal, QIcon::Off);
          ui->pushButtonStart->setIcon(icon);
          //process->write("mute 1\n");//静音

          start=false;
          this->timer->stop();
          this->process->write("pause\n");
        }
        else
        {
            start=true;
            icon.addFile(QString::fromUtf8("../image/playy.png"), QSize(), QIcon::Normal, QIcon::Off);
            ui->pushButtonStart->setIcon(icon);

            ///process->write("mute 0\n");
            initPlay();

        }
    }



}

void Music::on_pushButton_4_clicked()//重新开始
{
      this->process->close();
      initPlay();
//    this->timer->stop();
//    this->process->close();
//    this->timer->stop();
//    this->process->write("pause\n");

}

void Music::pressListPlay(QListWidgetItem *item)
{

    //qDebug()<<"***********"<<item->;//<<this->songMap[item->text()];
    this->process->close();
    this->initPlay();


//     ui->textEditShowIrc->clear();

    if(readLrcFile(item->text())==1)
       showIrc();
    else
    {
        ui->textEditShowIrc->setText("没有找到相对应的歌词");
    }

}

void Music::pressList(int a)
{
    //qDebug()<<"^^^^^^^^^^^^^"<<a;
    this->currentFlag = a;
}


void Music::on_horizontalSlider_valueChanged(int value)
{
    //qDebug()<<"%%%%%%%%%%%%%%%%"<<this->songInfo.songLen<<"value========"
            //<<value<<"curren=="<<this->songInfo.curTime<<"percent==="<<this->songInfo.percent;
    float a = this->songInfo.songLen/100;
    float b = a*(value-this->songInfo.percent);
    ui->horizontalSlider->setValue(value);
    this->process->write(QString("seek "+QString::number(b)+"\n").toUtf8());

}

void Music::on_pushButton_5_clicked()//上一首
{
    ui->textEditShowIrc->setText("");
    if(this->currentFlag != 0)
        this->currentFlag--;

    this->process->close();
    this->initPlay();
}

void Music::on_pushButton_7_clicked()//下一首
{
    qDebug()<<"clear====";
    ui->textEditShowIrc->clear();;
    qDebug()<<"dir========"<<this->Dir.count()<<
            this->currentFlag;
    if(this->currentFlag < (this->Dir.count()-3))
        this->currentFlag++;

    this->process->close();
    this->initPlay();
//    if(readLrcFile(item->text())==1)
//       showIrc();
//    else
//    {
//        ui->textEditShowIrc->setText("没有找到相对应的歌词");
//    }
}



void Music::on_pushButton_clicked()
{
    this->backNum ++;
    if(this->backNum == 10)
        this->backNum = 0;
    //getFile(this->Dir);//将歌词歌名保存
     //ui->listWidget->clear();
     //getFile(this->Dir);//将歌词歌名保存
     //this->songMap.clear();
    if(this->backNum == 1)
    {
//        QPalette p;
//        p.setColor(QPalette::Text,Qt::blue);
//        ui->listWidget->setPalette(p);
        ui->pushButtonStart->setIcon(QIcon("../image/1.png"));
        ui->pushButton_4->setIcon(QIcon("../image/2.png"));
        ui->pushButton_5->setIcon(QIcon("../image/3.png"));
        ui->pushButton_7->setIcon(QIcon("../image/4.png"));
        ui->pushButtonVolumn->setIcon(QIcon("../image/sond7.png"));
    }

    else if(this->backNum == 3)
    {
        ui->pushButtonStart->setIcon(QIcon("../image/pause1.png"));
        ui->pushButton_4->setIcon(QIcon("../image/play1.png"));
        ui->pushButton_5->setIcon(QIcon("../image/skipBackward1.png"));
        ui->pushButton_7->setIcon(QIcon("../image/skipForward1.png"));
        ui->pushButtonVolumn->setIcon(QIcon("../image/v1.png"));
    }

    else if(this->backNum == 9)
    {
        ui->pushButtonStart->setIcon(QIcon("../image/pause.png"));
        ui->pushButton_4->setIcon(QIcon("../image/play.png"));
        ui->pushButton_5->setIcon(QIcon("../image/next.png"));
        ui->pushButton_7->setIcon(QIcon("../image/previous.png"));
        ui->pushButtonVolumn->setIcon(QIcon("../image/sond7.png"));
    }

    else if(this->backNum == 4)
    {
        ui->pushButtonStart->setIcon(QIcon("../image/1.png"));
        ui->pushButton_4->setIcon(QIcon("../image/2.png"));
        ui->pushButton_5->setIcon(QIcon("../image/3.png"));
        ui->pushButton_7->setIcon(QIcon("../image/4.png"));
        ui->pushButtonVolumn->setIcon(QIcon("../image/sond7.png"));
    }

    else
    {
        ui->pushButtonStart->setIcon(QIcon("../image/playy.png"));
        ui->pushButton_4->setIcon(QIcon("../image/pausee.png"));
        ui->pushButton_5->setIcon(QIcon("../image/back.png"));
        ui->pushButton_7->setIcon(QIcon("../image/front.png"));
        ui->pushButtonVolumn->setIcon(QIcon("../image/mute_1.png"));
    }



    this->update();
}

void Music::on_horizontalSliderVolumn_valueChanged(int value)
{
    static bool volum=true;
    qDebug()<<"!!!!!!!!!!!!!!"<<value;
    if(value<=10&&volum==true)
    {
        process->write("mute 1\n");//静音
        volum = false;

    }
    else if(volum == false)
    {
       process->write("mute 0\n");
       int a = value/5;
       process->write(QString("volume "+QString::number(a)+"\n").toUtf8());
       volum = true;
    }

}


void Music::on_pushButtonVolumn_clicked()
{
    qDebug()<<"vol &&&&&&& static";
    static bool volum=true;


    if(this->backNum == 9)
    {
        QIcon icon;
        if(volum==true)
        {
          icon.addFile(QString::fromUtf8("../image/v2.png"), QSize(), QIcon::Normal, QIcon::Off);
          ui->pushButtonVolumn->setIcon(icon);
          process->write("mute 1\n");//静音
          volum=false;
        }
        else
        {
            volum=true;
            icon.addFile(QString::fromUtf8("../image/v1.png"), QSize(), QIcon::Normal, QIcon::Off);
            ui->pushButtonVolumn->setIcon(icon);
            process->write("mute 0\n");
        }
    }

    else if(this->backNum == 1 ||this->backNum == 4||this->backNum == 11)
    {
        QIcon icon;
        if(volum==true)
        {
          icon.addFile(QString::fromUtf8("../image/sound.png"), QSize(), QIcon::Normal, QIcon::Off);
          ui->pushButtonVolumn->setIcon(icon);
          process->write("mute 1\n");//静音
          volum=false;
        }
        else
        {
            volum=true;
            icon.addFile(QString::fromUtf8("../image/sond7.png"), QSize(), QIcon::Normal, QIcon::Off);
            ui->pushButtonVolumn->setIcon(icon);
            process->write("mute 0\n");
        }
    }

    else
    {
        QIcon icon;
        if(volum==true)
        {
          icon.addFile(QString::fromUtf8("../image/mute_0.png"), QSize(), QIcon::Normal, QIcon::Off);
          ui->pushButtonVolumn->setIcon(icon);
          process->write("mute 1\n");//静音
          volum=false;
        }
        else
        {
            volum=true;
            icon.addFile(QString::fromUtf8("../image/mute_1.png"), QSize(), QIcon::Normal, QIcon::Off);
            ui->pushButtonVolumn->setIcon(icon);
            process->write("mute 0\n");
        }
    }
}
