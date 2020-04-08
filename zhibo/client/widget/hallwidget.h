#ifndef HALLWIDGET_H
#define HALLWIDGET_H

#include <QWidget>
#include <QCloseEvent>
#include <QStringList>
#include <QListWidgetItem>


namespace Ui {
class HallWidget;
}

class HallWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HallWidget(QWidget *parent = 0);
    ~HallWidget();

    void refleshRoomname(QStringList roomList);

private:
    Ui::HallWidget *ui;

protected:
    virtual void closeEvent(QCloseEvent *event);
    virtual void showEvent(QShowEvent *event);
    virtual void hideEvent(QHideEvent *event);


private slots:
    void on_btnCreate_clicked();
    void on_lwRoom_itemDoubleClicked(QListWidgetItem *item);
    void on_btnCharge_clicked();
};

#endif // HALLWIDGET_H
