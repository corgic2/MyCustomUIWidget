#include "BaseStyleWidgetInterface.h"
#include "StyleSystem/SkinManager.h"
BaseStyleWidgetInterface::BaseStyleWidgetInterface()
{
    if (!BaseWidgetSkinManagerInit)
    {
        InitSkinManager();
        BaseWidgetSkinManagerInit = true;
    }
}

BaseStyleWidgetInterface::~BaseStyleWidgetInterface()
{}

void BaseStyleWidgetInterface::InitSkinManager()
{
    // ���Ƥ������
    SkinManager::instance()->addSkinVersionInfo("default", ":/Config/Default/skin_config.json");
    SkinManager::instance()->addQrcResource(":/CustomUiWidget/CoreWidget");
    SkinManager::instance()->addQrcResource(":/CustomUiWidget/DomainWidget");
    SkinManager::instance()->addQrcResource(":/Config/Default");
    // ����Ĭ��Ƥ��
    SkinManager::instance()->setCurrentSkinId("default");
}

