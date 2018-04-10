#include "videowidget.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QDebug>

#define LHDEBUG 0

VideoWidget::VideoWidget(QWidget *parent)
    : QVideoWidget(parent)
{
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    QPalette p = palette();
    p.setColor(QPalette::Window, Qt::black);
    setPalette(p);

    setAttribute(Qt::WA_OpaquePaintEvent);
}

void VideoWidget::keyPressEvent(QKeyEvent *event)
{
    //Qt::Key_Escape  0x01000000
    //isFullScreen() 是否全屏,默认为false
    //== > & > &&
#if LHDEBUG
//    qDebug() << "1isFullScreen() =" << isFullScreen();
#endif
    if (event->key() == Qt::Key_Escape && isFullScreen()) {

#if LHDEBUG
    qDebug() << "2isFullScreen() =" << isFullScreen();
#endif
        //设置成非全屏
        setFullScreen(false);
        event->accept();
    } else if (event->key() == Qt::Key_Enter && event->modifiers() & Qt::Key_Alt) {
#if LHDEBUG
    qDebug() << "3isFullScreen() =" << isFullScreen();
#endif
        setFullScreen(!isFullScreen());
        event->accept();
    } else {
#if LHDEBUG
    qDebug() << "4isFullScreen() =" << isFullScreen();
#endif
        QVideoWidget::keyPressEvent(event);
    }
#if LHDEBUG
    qDebug() << "5isFullScreen() =" << isFullScreen();
#endif
}

/**
 * @brief VideoWidget::mouseDoubleClickEvent
 * @param event
 * 双击视频播放框全屏(播放视频的全屏,不是软件全屏)
 */
void VideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    setFullScreen(!isFullScreen());
    event->accept();
}

/**
 * @brief VideoWidget::mousePressEvent
 * @param event
 * 点击视频播放框可以触发这个事件
 */
void VideoWidget::mousePressEvent(QMouseEvent *event)
{
#if 1
    qDebug() << event->x() << event->y();
    qDebug() << "event->x() << event->y()";
    qDebug() << event;
    qDebug() << &event << &(*event);
#endif
    QVideoWidget::mousePressEvent(event);
}

