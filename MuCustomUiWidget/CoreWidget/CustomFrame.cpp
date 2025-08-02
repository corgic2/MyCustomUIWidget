#include "CustomFrame.h"
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QStyleOption>

CustomFrame::CustomFrame(QWidget* parent)
    : QFrame(parent)
{
    InitializeFrame();
    AUTO_LOAD_SKIN_STYLE();
}

CustomFrame::~CustomFrame()
{
}

void CustomFrame::InitializeFrame()
{
    // 初始化默认值
    m_backgroundColor = UIColorDefine::background_color::Transparent;
    m_gradientStartColor = UIColorDefine::background_color::White;
    m_gradientEndColor = UIColorDefine::background_color::Dark;
    m_hasLeftBorder = false;
    m_hasTopBorder = false;
    m_hasRightBorder = false;
    m_hasBottomBorder = false;
    m_borderColor = UIColorDefine::border_color::Default;
    m_borderWidth = 1;
    m_padding = 0;
    m_backgroundType = BackgroundType_Transparent;
    // 设置默认样式
    UpdateStyle();
}

void CustomFrame::SetBackgroundColor(const QColor& color)
{
    m_backgroundColor = color;
    m_backgroundType = BackgroundType_Solid;
    UpdateStyle();
}

void CustomFrame::SetBackgroundType(const EM_BackgroundType& type)
{
    m_backgroundType = type;
    UpdateStyle();
}

void CustomFrame::SetGradientBackground(const QColor& startColor, const QColor& endColor)
{
    m_gradientStartColor = startColor;
    m_gradientEndColor = endColor;
    m_backgroundType = BackgroundType_Gradient;
    UpdateStyle();
}

void CustomFrame::EnableLeftBorder(bool enable)
{
    m_hasLeftBorder = enable;
    UpdateStyle();
}

void CustomFrame::EnableTopBorder(bool enable)
{
    m_hasTopBorder = enable;
    UpdateStyle();
}

void CustomFrame::EnableRightBorder(bool enable)
{
    m_hasRightBorder = enable;
    UpdateStyle();
}

void CustomFrame::EnableBottomBorder(bool enable)
{
    m_hasBottomBorder = enable;
    UpdateStyle();
}


void CustomFrame::SetPadding(int padding)
{
    m_padding = padding;
    setContentsMargins(m_padding, m_padding, m_padding, m_padding);
    UpdateStyle();
}

void CustomFrame::SetBorderWidth(int width)
{
    m_borderWidth = width;
    UpdateStyle();
}

void CustomFrame::SetBorderColor(const QColor& color)
{
    m_borderColor = color;
    UpdateStyle();
}

void CustomFrame::UpdateStyle()
{
    m_styleSheet = QString();
    // 基础样式
    m_styleSheet += QString("QFrame { ");
    // 背景样式
    switch (m_backgroundType)
    {
        case BackgroundType_Solid:
            m_styleSheet += QString("background-color: %1; ").arg(UIColorDefine::color_convert::ToCssString(m_backgroundColor));
            break;
        case BackgroundType_Gradient:
            m_styleSheet += QString("background: %1; ").arg(UIColorDefine::color_convert::ToGradientString(m_gradientStartColor, m_gradientEndColor));
            break;
        case BackgroundType_Transparent:
            m_styleSheet += "background: transparent; ";
            break;
    }
    // 边框样式
    QString borders;
    if (m_hasLeftBorder)
    {
        borders += QString("border-left: %1px solid %2; ").arg(m_borderWidth).arg(UIColorDefine::color_convert::ToCssString(m_borderColor));
    }
    if (m_hasTopBorder)
    {
        borders += QString("border-top: %1px solid %2; ").arg(m_borderWidth).arg(UIColorDefine::color_convert::ToCssString(m_borderColor));
    }
    if (m_hasRightBorder)
    {
        borders += QString("border-right: %1px solid %2; ").arg(m_borderWidth).arg(UIColorDefine::color_convert::ToCssString(m_borderColor));
    }
    if (m_hasBottomBorder)
    {
        borders += QString("border-bottom: %1px solid %2; ").arg(m_borderWidth).arg(UIColorDefine::color_convert::ToCssString(m_borderColor));
                            m_styleSheet += borders;
    }
    m_styleSheet += "} ";
    setStyleSheet(m_styleSheet);
}

void CustomFrame::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QFrame::paintEvent(event);
}
