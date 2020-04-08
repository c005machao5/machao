#ifndef SCROLLTEXT_H
#define SCROLLTEXT_H


#include <QLabel>
#include <QTimer>

class ScrollText :public QLabel
{
    Q_OBJECT
public:
    enum Direction{
        none = 0,
        up = 1,
        down = 2,
        left = 3,
        right = 4
    };
    explicit ScrollText(int x,int y,QLabel* parent);

    void startScroll();
    void stopScroll();

    Direction getDirection() const;
    void setDirection(const Direction &value);

signals:
    void outOfRange();

private:
    Direction direction;
    QTimer* timer;

private slots:
    void onTimeout();
};

#endif // SCROLLTEXT_H
