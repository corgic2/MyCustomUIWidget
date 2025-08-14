#pragma once
#include <QString>
static bool BaseWidgetSkinManagerInit = false;
class BaseStyleWidgetInterface
{
public:
    BaseStyleWidgetInterface();
    virtual ~BaseStyleWidgetInterface();
    QString GetStyleFormatStr() const
    {
        return m_styleFormatStr;
    }
    void SetStyleFormatStr(QString text)
    {
        m_styleFormatStr = text;
    }
    virtual void ApplyFormatStyle() = 0;
protected:
    virtual void Connectionals() = 0;
    virtual void Initilize() = 0;
    QString m_styleFormatStr;
private:
    static void InitSkinManager();
};

