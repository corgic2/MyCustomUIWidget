#include "CustomFrame.h"
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QStyleOption>
#include "StyleSystem/SkinStyleLoader.h"

CustomFrame::CustomFrame(QWidget* parent)
    : QFrame(parent), m_frameFormat(EM_CustomFrameFormat::EM_Normal)
{
    AUTO_LOAD_SKIN_STYLE();
    Initilize();
    Connectionals();
}

CustomFrame::~CustomFrame()
{
}

CustomFrame::EM_CustomFrameFormat CustomFrame::GetFrameFormat() const
{
    return m_frameFormat;
}

void CustomFrame::SetFrameFormat(EM_CustomFrameFormat format)
{
    if (m_frameFormat != format)
    {
        m_frameFormat = format;
        ApplyFormatStyle();
    }
}

void CustomFrame::Connectionals()
{
}

void CustomFrame::Initilize()
{
}

void CustomFrame::ApplyFormatStyle()
{
    QString str;
    // 根据格式设置对应的样式类
    switch (m_frameFormat)
    {
        case EM_CustomFrameFormat::EM_Normal:
            str = "EM_Normal";
            break;
        case EM_CustomFrameFormat::EM_Card:
            str = "EM_Card";
            break;
        case EM_CustomFrameFormat::EM_Panel:
            str = "EM_Panel";
            break;
        case EM_CustomFrameFormat::EM_Shadow:
            str = "EM_Shadow";
            break;
        case EM_CustomFrameFormat::EM_Raised:
            str = "EM_Raised";
            break;
        case EM_CustomFrameFormat::EM_Sunken:
            str = "EM_Sunken";
            break;
        case EM_CustomFrameFormat::EM_Line:
            str = "EM_Line";
            break;
        case EM_CustomFrameFormat::EM_None:
            str = "EM_None";
            break;
    }
    SetStyleFormatStr(str);
    //// 重新应用样式
    this->style()->unpolish(this);
    this->style()->polish(this);
    this->update();
}
