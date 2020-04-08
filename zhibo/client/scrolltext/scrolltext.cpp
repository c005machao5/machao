#include "scrolltext.h"
#include <QDebug>

ScrollText::ScrollText(int x, int y,QLabel *parent)
    : QLabel(parent),
      direction(none),
      timer(new QTimer(this))
{
    this->move(x,y);
    this->setAttribute(Qt::WA_TranslucentBackground);

    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(onTimeout()));
}

void ScrollText::startScroll()
{
    if(direction == none) return;

    timer->start(10);
}

void ScrollText::stopScroll()
{
    timer->stop();
    this->hide();
}

ScrollText::Direction ScrollText::getDirection() const
{
    return direction;
}

void ScrollText::setDirection(const Direction &value)
{
    direction = value;
}
void ScrollText::onTimeout()
{
    QPoint position = this->pos();
    QWidget* pa = static_cast<QWidget*>(this->parent());

    switch(direction){
    case ScrollText::none:
        break;
    case ScrollText::up:
    {
        position += QPoint(0, -1);
        if(position.y() + this->height() < 0){
            position = QPoint(position.x(), pa->height());
            emit outOfRange();
        }
    }
        break;
    case ScrollText::down:
    {
        position += QPoint(0, 1);
        if(position.y() > pa->height()){
            position = QPoint(position.x(), -this->height());
            emit outOfRange();
        }
    }
        break;
    case ScrollText::left:
    {
        position += QPoint(-1, 0);
        if(position.x() < -this->width()){
            position = QPoint(pa->width(), position.y());
            emit outOfRange();
        }
    }
        break;
    case ScrollText::right:
    {
        position += QPoint(1, 0);
        if(position.x() > pa->width()){
            position = QPoint(-this->width(), position.y());
            emit outOfRange();
        }
    }
        break;
    }

    this->move(position);
}


