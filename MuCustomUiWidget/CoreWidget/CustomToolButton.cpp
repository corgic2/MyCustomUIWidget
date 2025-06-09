#include "CustomToolButton.h"
#include <QEvent>
#include <QPainter>
#include <QPen>

CustomToolButton::CustomToolButton(QWidget* parent)
    : QToolButton(parent)
    , m_borderWidth(0)
    , m_borderColor(Qt::transparent)
{
    InitializeButton();
    // 初始化默认边距
    setContentsMargins(0, 0, 0, 0);
}

CustomToolButton::~CustomToolButton()
{
    SAFE_DELETE_POINTER_VALUE(m_tips);
}

void CustomToolButton::InitializeButton()
{
    // 初始化默认值
    m_fontColor = UIColorDefine::font_color::Primary;
    m_fontSize = 12;
    m_fontStyle = FontStyle_Normal;
    m_backgroundType = BackgroundType_Transparent;
    m_backgroundColor = UIColorDefine::background_color::Transparent;
    m_gradientStartColor = UIColorDefine::background_color::Light;
    m_gradientEndColor = UIColorDefine::background_color::Dark;
    m_padding = 5;
    m_tipsType = CustomToolTips::Normal;

    // 创建提示框
    m_tips = new CustomToolTips(this);
    m_tips->hide();

    UpdateStyle();
}

void CustomToolButton::SetToolTipsText(const QString& text)
{
    m_toolTipsText = text;
    m_tips->SetToolTips(text);
}

void CustomToolButton::SetToolTipsExText(const QString& text)
{
    m_toolTipsExText = text;
    m_tips->SetToolTipsEx(text);
}

void CustomToolButton::SetTipsType(CustomToolTips::EM_TipsType type)
{
    m_tipsType = type;
    m_tips->SetTipsType(type);
}

void CustomToolButton::SetFontColor(const QColor& color)
{
    m_fontColor = color;
    UpdateStyle();
}

void CustomToolButton::SetFontSize(int size)
{
    m_fontSize = size;
    UpdateStyle();
}

void CustomToolButton::SetFontStyle(const EM_FontStyle& style)
{
    m_fontStyle = style;
    UpdateStyle();
}

void CustomToolButton::SetBackgroundColor(const QColor& color)
{
    m_backgroundColor = color;
    m_backgroundType = BackgroundType_Solid;
    UpdateStyle();
}

void CustomToolButton::SetBackgroundType(const EM_BackgroundType& type)
{
    m_backgroundType = type;
    UpdateStyle();
}

void CustomToolButton::SetGradientBackground(const QColor& startColor, const QColor& endColor)
{
    m_gradientStartColor = startColor;
    m_gradientEndColor = endColor;
    m_backgroundType = BackgroundType_Gradient;
    UpdateStyle();
}

void CustomToolButton::SetPadding(int padding)
{
    m_padding = padding;
    UpdateStyle();
}

void CustomToolButton::SetMargins(int left, int top, int right, int bottom)
{
    setContentsMargins(left, top, right, bottom);
    update();
}

void CustomToolButton::SetBorderWidth(int width)
{
    m_borderWidth = width;
    update();
}

void CustomToolButton::SetBorderColor(const QColor& color)
{
    m_borderColor = color;
    update();
}

void CustomToolButton::UpdateStyle()
{
    m_styleSheet = QString();

    // 基础样式
    m_styleSheet += QString("QToolButton { color: %1; ").arg(UIColorDefine::color_convert::ToCssString(m_fontColor));
    m_styleSheet += QString("font-size: %1pt; ").arg(m_fontSize);
    m_styleSheet += QString("padding: %1px; ").arg(m_padding);

    // 字体样式
    switch (m_fontStyle)
    {
        case FontStyle_Bold:
            m_styleSheet += "font-weight: bold; ";
            break;
        case FontStyle_Italic:
            m_styleSheet += "font-style: italic; ";
            break;
        case FontStyle_Underline:
            m_styleSheet += "text-decoration: underline; ";
            break;
        default:
            break;
    }

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
            // 添加悬停和按下状态的背景色
            m_styleSheet += QString(
                "QToolButton:hover { background-color: %1; } "
                "QToolButton:pressed { background-color: %2; }")
                .arg(UIColorDefine::color_convert::ToCssString(UIColorDefine::background_color::HoverBackground))
                .arg(UIColorDefine::color_convert::ToCssString(UIColorDefine::background_color::PressedBackground));
            break;
    }

    m_styleSheet += "} ";

    setStyleSheet(m_styleSheet);
}

void CustomToolButton::enterEvent(QEvent* event)
{
    QToolButton::enterEvent(event);
    if (!m_toolTipsText.isEmpty())
    {
        QPoint pos = mapToGlobal(QPoint(0, height()));
        m_tips->ShowTips(pos);
    }
}

void CustomToolButton::leaveEvent(QEvent* event)
{
    QToolButton::leaveEvent(event);
    m_tips->hide();
}

void CustomToolButton::OnStyleChanged()
{
    UpdateStyle();
}

QString CustomToolButton::toolTipsText() const
{
    return m_toolTipsText;
}

QString CustomToolButton::toolTipsExText() const
{
    return m_toolTipsExText;
}

CustomToolTips::EM_TipsType CustomToolButton::tipsType() const
{
    return m_tipsType;
}

QColor CustomToolButton::fontColor() const
{
    return m_fontColor;
}

int CustomToolButton::fontSize() const
{
    return m_fontSize;
}

CustomToolButton::EM_FontStyle CustomToolButton::fontStyle() const
{
    return m_fontStyle;
}

QColor CustomToolButton::backgroundColor() const
{
    return m_backgroundColor;
}

CustomToolButton::EM_BackgroundType CustomToolButton::backgroundType() const
{
    return m_backgroundType;
}

int CustomToolButton::padding() const
{
    return m_padding;
}

void CustomToolButton::paintEvent(QPaintEvent* event)
{
    QToolButton::paintEvent(event);
    
    if (m_borderWidth > 0)
    {
        QPainter painter(this);
        painter.setPen(QPen(m_borderColor, m_borderWidth));
        painter.drawRect(rect().adjusted(m_borderWidth/2, m_borderWidth/2, 
                                       -m_borderWidth/2, -m_borderWidth/2));
    }
}
