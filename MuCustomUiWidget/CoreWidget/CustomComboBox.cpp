#include "CustomComboBox.h"
#include <QPainter>
#include <QStyleOption>

CustomComboBox::CustomComboBox(QWidget* parent)
    : QComboBox(parent)
    , m_fontColor(UIColorDefine::font_color::Primary)
    , m_fontSize(FontSize_Normal)
    , m_fontStyle(FontStyle_Normal)
    , m_backgroundType(BackgroundType_Transparent)
    , m_backgroundColor(UIColorDefine::background_color::Transparent)
    , m_itemFontColor(UIColorDefine::font_color::Primary)
    , m_itemBackgroundColor(UIColorDefine::background_color::White)
    , m_itemSpacing(2)
    , m_itemHeight(24)
    , m_borderWidth(0)
    , m_borderColor(Qt::transparent)
{
    InitializeComboBox();
    // 初始化默认边距
    setContentsMargins(0, 0, 0, 0);
}

CustomComboBox::~CustomComboBox()
{
}

void CustomComboBox::InitializeComboBox()
{
    setView(new QListView());
    UpdateStyle();
}

void CustomComboBox::SetFontColor(const QColor& color)
{
    m_fontColor = color;
    UpdateStyle();
}

void CustomComboBox::SetFontSize(const EM_FontSize& fontSize)
{
    m_fontSize = fontSize;
    UpdateStyle();
}

void CustomComboBox::SetFontStyle(const EM_FontStyle& fontStyle)
{
    m_fontStyle = fontStyle;
    UpdateStyle();
}

void CustomComboBox::SetBackgroundColor(const QColor& color)
{
    m_backgroundColor = color;
    UpdateStyle();
}

void CustomComboBox::SetBackgroundType(const EM_BackgroundType& type)
{
    m_backgroundType = type;
    UpdateStyle();
}

void CustomComboBox::SetGradientBackground(const UIColorDefine::ST_GradientColor& gradientColor)
{
    m_gradientColor = gradientColor;
    UpdateStyle();
}

void CustomComboBox::SetItemSpacing(int spacing)
{
    m_itemSpacing = spacing;
    UpdateStyle();
}

void CustomComboBox::SetItemHeight(int height)
{
    m_itemHeight = height;
    UpdateStyle();
}

void CustomComboBox::SetItemFontColor(const QColor& color)
{
    m_itemFontColor = color;
    UpdateStyle();
}

void CustomComboBox::SetItemBackgroundColor(const QColor& color)
{
    m_itemBackgroundColor = color;
    UpdateStyle();
}

void CustomComboBox::OnStyleChanged()
{
    UpdateStyle();
}

void CustomComboBox::UpdateStyle()
{
    QString style = "QComboBox { ";

    // 字体样式
    style += QString("color: %1; ").arg(UIColorDefine::color_convert::ToCssString(m_fontColor));
    style += QString("font-size: %1px; ").arg(m_fontSize);

    switch (m_fontStyle)
    {
        case FontStyle_Bold:
            style += "font-weight: bold; ";
            break;
        case FontStyle_Italic:
            style += "font-style: italic; ";
            break;
        case FontStyle_Underline:
            style += "text-decoration: underline; ";
            break;
        default:
            break;
    }

    // 背景样式
    switch (m_backgroundType)
    {
        case BackgroundType_Solid:
            style += QString("background-color: %1; ").arg(UIColorDefine::color_convert::ToCssString(m_backgroundColor));
            break;
        case BackgroundType_Gradient:
            style += QString("background: %1; ").arg(UIColorDefine::color_convert::ToGradientString(m_gradientColor.start, m_gradientColor.end));
            break;
        case BackgroundType_Transparent:
            style += "background: transparent; ";
            break;
    }

    style += "} ";

    // 下拉列表样式
    style += "QComboBox QAbstractItemView { ";
    style += QString("color: %1; ").arg(UIColorDefine::color_convert::ToCssString(m_itemFontColor));
    style += QString("background: %1; ").arg(UIColorDefine::color_convert::ToCssString(m_itemBackgroundColor));
    style += QString("spacing: %1px; ").arg(m_itemSpacing);
    style += "} ";

    // 下拉列表项样式
    style += "QComboBox::item { ";
    style += QString("height: %1px; ").arg(m_itemHeight);
    style += "} ";

    setStyleSheet(style);
}

void CustomComboBox::SetMargins(int left, int top, int right, int bottom)
{
    setContentsMargins(left, top, right, bottom);
    update();
}

void CustomComboBox::SetBorderWidth(int width)
{
    m_borderWidth = width;
    update();
}

void CustomComboBox::SetBorderColor(const QColor& color)
{
    m_borderColor = color;
    update();
}

void CustomComboBox::paintEvent(QPaintEvent* event)
{
    QComboBox::paintEvent(event);
    
    if (m_borderWidth > 0)
    {
        QPainter painter(this);
        painter.setPen(QPen(m_borderColor, m_borderWidth));
        painter.drawRect(rect().adjusted(m_borderWidth/2, m_borderWidth/2, 
                                       -m_borderWidth/2, -m_borderWidth/2));
    }
}
