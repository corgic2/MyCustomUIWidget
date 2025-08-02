#include "CustomLabel.h"
#include <QGraphicsDropShadowEffect>
#include "SkinStyleLoader.h"

CustomLabel::CustomLabel(QWidget* parent)
    : QLabel(parent)
{
    InitializeLabel();
    AUTO_LOAD_SKIN_STYLE();
}

CustomLabel::~CustomLabel()
{
}

void CustomLabel::InitializeLabel()
{
    // 初始化默认值
    m_fontColor = UIColorDefine::font_color::Primary;
    m_fontSize = EM_FontSize::FontSize_Normal;
    m_fontStyle = EM_FontStyle::FontStyle_Normal;
    m_backgroundType = EM_BackgroundType::BackgroundType_Transparent;
    m_backgroundColor = UIColorDefine::background_color::Transparent;
    m_gradientStartColor = UIColorDefine::background_color::White;
    m_gradientEndColor = UIColorDefine::background_color::Dark;
    m_hasShadow = false;
    m_shadowColor = UIColorDefine::shadow_color::Default;
    m_hasBorder = false;
    m_borderColor = UIColorDefine::border_color::Default;
    m_borderWidth = 1;
    m_enableElide = false;
    m_imageScaleMode = EM_ImageScaleMode::ScaleToFit;

    // 设置默认样式
    UpdateStyle();
}

void CustomLabel::SetFontColor(const QColor& color)
{
    m_fontColor = color;
    UpdateStyle();
}

void CustomLabel::SetBackgroundColor(const QColor& color)
{
    m_backgroundColor = color;
    m_backgroundType = EM_BackgroundType::BackgroundType_Solid;
    UpdateStyle();
}

void CustomLabel::SetGradientBackground(const QColor& startColor, const QColor& endColor)
{
    m_gradientStartColor = startColor;
    m_gradientEndColor = endColor;
    m_backgroundType = EM_BackgroundType::BackgroundType_Gradient;
    UpdateStyle();
}

void CustomLabel::EnableShadow(bool enable, const QColor& shadowColor)
{
    m_hasShadow = enable;
    m_shadowColor = shadowColor;

    if (m_hasShadow)
    {
        auto shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(10);
        shadow->setColor(m_shadowColor);
        shadow->setOffset(0, 2);
        setGraphicsEffect(shadow);
    }
    else
    {
        setGraphicsEffect(nullptr);
    }

    UpdateStyle();
}

void CustomLabel::UpdateStyle()
{
    m_styleSheet = QString();

    // 基础样式
    m_styleSheet += QString("QLabel { color: %1; ").arg(UIColorDefine::color_convert::ToCssString(m_fontColor));
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
    if (m_hasBorder)
    {
        m_styleSheet += QString("border: %1px solid %2; ")
                        .arg(m_borderWidth)
                        .arg(UIColorDefine::color_convert::ToCssString(m_borderColor));
    }

    m_styleSheet += "} ";

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

void CustomLabel::SetEnableElide(bool enable)
{
    m_enableElide = enable;
    if (m_enableElide)
    {
        setWordWrap(false);
    }
}

void CustomLabel::EnableBorder(bool enable, const QColor& color, int width)
{
    m_hasBorder = enable;
    m_borderColor = color;
    m_borderWidth = width;
    UpdateStyle();
}

CustomLabel::EM_ImageScaleMode CustomLabel::imageScaleMode() const
{
    return m_imageScaleMode;
}

void CustomLabel::SetImageScaleMode(EM_ImageScaleMode mode)
{
    m_imageScaleMode = mode;
    UpdateStyle();
}

void CustomLabel::resizeEvent(QResizeEvent* event)
{
    QLabel::resizeEvent(event);
    if (!m_pixmap.isNull())
    {
        SetImage(m_pixmap, m_imageScaleMode);
    }
    if (m_enableElide && !text().isEmpty())
    {
        SetText(text());
    }
}

void CustomLabel::OnStyleChanged()
{
    UpdateStyle();
}

void CustomLabel::SetImage(const QString& imagePath, EM_ImageScaleMode scaleMode)
{
    QPixmap pixmap(imagePath);
    SetImage(pixmap, scaleMode);
}

void CustomLabel::SetImage(const QPixmap& pixmap, EM_ImageScaleMode scaleMode)
{
    if (pixmap.isNull())
    {
        return;
    }

    m_imageScaleMode = scaleMode;
    QSize targetSize = size();

    switch (m_imageScaleMode)
    {
        case ScaleToFit:
            setPixmap(pixmap.scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            break;
        case ScaleToFill:
            setPixmap(pixmap.scaled(targetSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            break;
        case ScaleToWidth:
            setPixmap(pixmap.scaledToWidth(targetSize.width(), Qt::SmoothTransformation));
            break;
        case ScaleToHeight:
            setPixmap(pixmap.scaledToHeight(targetSize.height(), Qt::SmoothTransformation));
            break;
    }
}

void CustomLabel::paintEvent(QPaintEvent* event)
{
    if (m_enableElide && !text().isEmpty())
    {
        QPainter painter(this);
        QFontMetrics fm = fontMetrics();
        QString elidedText = fm.elidedText(text(), Qt::ElideRight, width());
        painter.drawText(rect(), alignment(), elidedText);
    }
    else
    {
        QLabel::paintEvent(event);
    }
}

QColor CustomLabel::fontColor() const
{
    return m_fontColor;
}

CustomLabel::EM_FontSize CustomLabel::fontSize() const
{
    return m_fontSize;
}

CustomLabel::EM_FontStyle CustomLabel::fontStyle() const
{
    return m_fontStyle;
}

CustomLabel::EM_BackgroundType CustomLabel::backgroundType() const
{
    return m_backgroundType;
}

QColor CustomLabel::backgroundColor() const
{
    return m_backgroundColor;
}

bool CustomLabel::hasShadow() const
{
    return m_hasShadow;
}

QColor CustomLabel::shadowColor() const
{
    return m_shadowColor;
}

void CustomLabel::SetShadowColor(const QColor& color)
{
    m_shadowColor = color;
    UpdateStyle();
}
bool CustomLabel::hasBorder() const
{
    return m_hasBorder;
}

QColor CustomLabel::borderColor() const
{
    return m_borderColor;
}

void CustomLabel::SetBorderColor(const QColor& color)
{
    m_borderColor = color;
    UpdateStyle();
}

int CustomLabel::borderWidth() const
{
    return m_borderWidth;
}

void CustomLabel::SetBorderWidth(int width)
{
    m_borderWidth = width;
    UpdateStyle();
}

bool CustomLabel::isElideEnabled() const
{
    return m_enableElide;
}
