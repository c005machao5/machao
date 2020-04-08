#ifndef GIFTWIDGET_H
#define GIFTWIDGET_H

#include <QWidget>

namespace Ui {
class GiftWidget;
}

class GiftWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GiftWidget(QWidget *parent = 0);
    ~GiftWidget();

    QString getRoomname() const;
    void setRoomname(const QString &value);

    QString getUsername() const;
    void setUsername(const QString &value);

private slots:
    void on_btnHeart_clicked();

    void on_btnCar_clicked();

    void on_btnRocket_clicked();

    void on_btnDunker_clicked();

private:
    Ui::GiftWidget *ui;

    QString roomname;
    QString username;
};

#endif // GIFTWIDGET_H
