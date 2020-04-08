#include "widgetmanager.h"

WidgetManager::WidgetManager()
    :loginWidget(nullptr),
      hallWidget(nullptr),
      roomWidget(nullptr),
      chargeWidget(nullptr),
      giftWidget(nullptr)
{
    //loginWidget = new LoginWidget;

}

LoginWidget *WidgetManager::getLoginWidget()
{
    if(nullptr == loginWidget)
            loginWidget = new LoginWidget;
    return loginWidget;
}
HallWidget *WidgetManager::getHallWidget()
{
    if(nullptr == hallWidget)
            hallWidget = new HallWidget;
    return hallWidget;
}
RoomWidget *WidgetManager::getRoomWidget()
{
    if(nullptr == roomWidget)
            roomWidget = new RoomWidget;
    return roomWidget;
}

ChargeWidget *WidgetManager::getChargeWidget()
{
    if(nullptr == chargeWidget)
            chargeWidget = new ChargeWidget;
    return chargeWidget;
}

GiftWidget *WidgetManager::getGiftWidget()
{
    if(nullptr == giftWidget)
            giftWidget = new GiftWidget;
    return giftWidget;
}
WidgetManager* WidgetManager::instance = nullptr;

WidgetManager *WidgetManager::getInstance()
{
    if(instance == nullptr) instance = new WidgetManager;
    return instance;
}
