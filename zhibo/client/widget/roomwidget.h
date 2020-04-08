#ifndef ROOMWIDGET_H
#define ROOMWIDGET_H

#include <QWidget>
#include <QCloseEvent>
#include <QStringList>
#include <QListWidgetItem>

#include <QString>
#include "video/xincamera.h"

namespace Ui {
class RoomWidget;
}

class RoomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RoomWidget(QWidget *parent = 0);
    ~RoomWidget();

    QString getRoomname() const;
    void setRoomname(const QString &value);

    QString getUsername() const;
    void setUsername(const QString &value);

    void appendText(const QString& text);
    void refleshUsername(QStringList userList);
    void sendScrollText(const QString& text);
    void sendScrollGift(const QString &text);

    int getPort() const;
    void setPort(int value);

    void myInit(); //初始化界面，清空界面用

private:
    Ui::RoomWidget *ui;

    QString roomname;
    QString username;
    int port;
    XinCamera *cmr;
protected:
    virtual void closeEvent(QCloseEvent* event);

private slots:
    void on_leIput_returnPressed();
    void on_pushButton_clicked();

    void on_checkBox_stateChanged(int arg1);
    void on_btnSend_clicked();

    void on_cbCamera_stateChanged(int arg1);
};

#endif // ROOMWIDGET_H
