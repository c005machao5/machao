#ifndef WIDGETMANAGER_H
#define WIDGETMANAGER_H

#include "loginwidget.h"
#include "hallwidget.h"
#include "roomwidget.h"
#include "chargewidget.h"
#include "giftwidget.h"

class WidgetManager
{
private:
    WidgetManager();
    static WidgetManager* instance;

    LoginWidget* loginWidget;
    HallWidget* hallWidget ;
    RoomWidget* roomWidget;
    ChargeWidget* chargeWidget;
    GiftWidget* giftWidget;

public:
    static WidgetManager* getInstance();
    LoginWidget *getLoginWidget();
    HallWidget *getHallWidget();
    RoomWidget *getRoomWidget();
    ChargeWidget *getChargeWidget();
    GiftWidget *getGiftWidget();
};

#endif // WIDGETMANAGER_H
