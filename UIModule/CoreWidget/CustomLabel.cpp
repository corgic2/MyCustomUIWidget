#include "CustomLabel.h"
#include <QGraphicsDropShadowEffect>

CustomLabel::CustomLabel(QWidget* parent)
    : QLabel(parent)
    , m_ui(new Ui::CustomLabelClass())
{
    InitializeLabel();
}

CustomLabel::~CustomLabel()
{
    delete m_ui;
}

void CustomLabel::InitializeLabel()
{
    // 初始化默认值
    m_fontColor = UIColorDefine::font_color::Primary;
    m_fontSize = EM_FontSize::FontSize_Normal;
    m_fontStyle = EM_FontStyle::FontStyle_Normal;
    m_backgroundType = EM_BackgroundType::BackgroundType_Transparent;
    m_backgroundColor = UIColorDefine::background_color::Transparent;
    m_hasShadow = false;
    m_shadowColor = UIColorDefine::shadow_color::Default;
    m_hasBorder = false;
    m_borderColor = UIColorDefine::border_color::Default;
    m_borderWidth = 1;
    m_enableElide = false;

    // 设置默认样式
    UpdateStyle();
}

void CustomLabel::SetFontColor(const UIColorDefine::ST_ColorRgb& color)
{
    m_fontColor = color;
    UpdateStyle();
}

void CustomLabel::SetBackgroundColor(const UIColorDefine::ST_ColorRgba& color)
{
    m_backgroundColor = color;
    m_backgroundType = EM_BackgroundType::BackgroundType_Solid;
    UpdateStyle();
}

void CustomLabel::SetGradientBackground(const UIColorDefine::ST_GradientColor& gradientColor)
{
    m_gradientColor = gradientColor;
    m_backgroundType = EM_BackgroundType::BackgroundType_Gradient;
    UpdateStyle();
}

void CustomLabel::EnableShadow(bool enable, const UIColorDefine::ST_ColorRgba& shadowColor)
{
    m_hasShadow = enable;
    m_shadowColor = shadowColor;

    if (enable)
    {
        auto shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(5);
        shadow->setColor(QColor(m_shadowColor.r, m_shadowColor.g, m_shadowColor.b, m_shadowColor.a));
        shadow->setOffset(2, 2);
        setGraphicsEffect(shadow);
    }
    else
    {
        setGraphicsEffect(nullptr);
    }
}

void CustomLabel::UpdateStyle()
{
    m_styleSheet = QString();

    // 基础样式
    m_styleSheet += QString("QLabel { color: %1; ").arg(m_fontColor.ToQString());
    m_styleSheet += QString("font-size: %1pt; ").arg(m_fontSize);

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
            m_styleSheet += QString("background-color: %1; ").arg(m_backgroundColor.ToQString());
            break;
        case BackgroundType_Gradient:
            m_styleSheet += QString("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
                                    "stop:0 %1, stop:1 %2); ")
                            .arg(m_gradientColor.start.ToQString())
                            .arg(m_gradientColor.end.ToQString());
            break;
        case BackgroundType_Transparent:
            m_styleSheet += "background-color: transparent; ";
            break;
    }

    // 边框样式
    if (m_hasBorder)
    {
        m_styleSheet += QString("border: %1px solid %2; ")
                        .arg(m_borderWidth)
                        .arg(m_borderColor.ToQString());
    }

    m_styleSheet += "}";
    setStyleSheet(m_styleSheet);
}

void CustomLabel::SetFontSize(const EM_FontSize& fontSize)
{
    m_fontSize = fontSize;
    UpdateStyle();
}

void CustomLabel::SetFontStyle(const EM_FontStyle& fontStyle)
{
    m_fontStyle = fontStyle;
    UpdateStyle();
}

void CustomLabel::SetBackgroundType(const EM_BackgroundType& type)
{
    m_backgroundType = type;
    UpdateStyle();
}

void CustomLabel::SetText(const QString& text)
{
    if (m_enableElide)
    {
        QString elidedText = fontMetrics().elidedText(text, Qt::ElideRight, width());
        QLabel::setText(elidedText);
    }
    else
    {
        QLabel::setText(text);
    }
}

void CustomLabel::SetAlignment(Qt::Alignment alignment)
{
    setAlignment(alignment);
}

void CustomLabel::SetToolTip(const QString& tip)
{
    setToolTip(tip);
}

void CustomLabel::EnableElide(bool enable)
{
    m_enableElide = enable;
    // 如果已经有文本，重新应用省略
    if (!text().isEmpty())
    {
        SetText(text());
    }
}

void CustomLabel::EnableBorder(bool enable, const UIColorDefine::ST_ColorRgb& color, int width)
{
    m_hasBorder = enable;
    m_borderColor = color;
    m_borderWidth = width;
    UpdateStyle();
}

void CustomLabel::resizeEvent(QResizeEvent* event)
{
    QLabel::resizeEvent(event);
    if (m_enableElide && !text().isEmpty())
    {
        SetText(text());  // 重新应用省略
    }
}

void CustomLabel::OnStyleChanged()
{
}
