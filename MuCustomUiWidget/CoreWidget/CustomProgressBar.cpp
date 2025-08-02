#include "CustomProgressBar.h"
#include <QGraphicsDropShadowEffect>
#include <QLinearGradient>
#include <QRadialGradient>
#include <QPainterPath>
#include <QFontMetrics>
#include "SkinStyleLoader.h"

CustomProgressBar::CustomProgressBar(QWidget* parent)
    : QProgressBar(parent)
    , m_animation(nullptr)
    , m_stripeTimer(nullptr)
    , m_stripeOffset(0)
{
    InitializeProgressBar();
    AUTO_LOAD_SKIN_STYLE();
}

CustomProgressBar::~CustomProgressBar()
{
    if (m_animation != nullptr)
    {
        m_animation->stop();
        delete m_animation;
        m_animation = nullptr;
    }
    
    if (m_stripeTimer != nullptr)
    {
        m_stripeTimer->stop();
        delete m_stripeTimer;
        m_stripeTimer = nullptr;
    }
}

void CustomProgressBar::InitializeProgressBar()
{
    // 初始化默认值
    m_progressBarStyle = EM_ProgressBarStyle::ProgressBarStyle_Default;
    m_backgroundColor = UIColorDefine::background_color::White;
    m_progressColor = UIColorDefine::theme_color::Primary;
    m_textColor = UIColorDefine::font_color::Primary;
    m_enableGradient = false;
    m_gradientStartColor = UIColorDefine::gradient_color::Primary.start;
    m_gradientEndColor = UIColorDefine::gradient_color::Primary.end;
    m_enableAnimation = false;
    m_animationDuration = 500;
    m_textPosition = EM_TextPosition::TextPosition_Center;
    m_enableShadow = false;
    m_shadowColor = UIColorDefine::shadow_color::Default;
    m_enableBorder = false;
    m_borderColor = UIColorDefine::border_color::Default;
    m_borderWidth = 1;
    m_borderRadius = 0;
    m_enableStripes = false;
    m_stripeDirection = EM_StripeDirection::StripeDirection_LeftToRight;

    // 设置默认范围
    setRange(0, 100);
    setValue(0);

    // 初始化动画
    m_animation = new QPropertyAnimation(this, "value", this);
    m_animation->setEasingCurve(QEasingCurve::OutCubic);
    connect(m_animation, &QPropertyAnimation::finished, this, &CustomProgressBar::SlotAnimationFinished);

    // 初始化条纹动画定时器
    m_stripeTimer = new QTimer(this);
    m_stripeTimer->setInterval(50);
    connect(m_stripeTimer, &QTimer::timeout, this, &CustomProgressBar::SlotUpdateStripeAnimation);

    // 设置默认样式
    UpdateStyle();
}

void CustomProgressBar::SetProgressBarStyle(EM_ProgressBarStyle style)
{
    m_progressBarStyle = style;
    UpdateStyle();
    update();
}

CustomProgressBar::EM_ProgressBarStyle CustomProgressBar::progressBarStyle() const
{
    return m_progressBarStyle;
}

void CustomProgressBar::SetBackgroundColor(const QColor& color)
{
    m_backgroundColor = color;
    UpdateStyle();
    update();
}

QColor CustomProgressBar::backgroundColor() const
{
    return m_backgroundColor;
}

void CustomProgressBar::SetProgressColor(const QColor& color)
{
    m_progressColor = color;
    UpdateStyle();
    update();
}

QColor CustomProgressBar::progressColor() const
{
    return m_progressColor;
}

void CustomProgressBar::SetTextColor(const QColor& color)
{
    m_textColor = color;
    UpdateStyle();
    update();
}

QColor CustomProgressBar::textColor() const
{
    return m_textColor;
}

void CustomProgressBar::SetEnableGradient(bool enable)
{
    m_enableGradient = enable;
    UpdateStyle();
    update();
}

bool CustomProgressBar::isGradientEnabled() const
{
    return m_enableGradient;
}

void CustomProgressBar::SetGradientStartColor(const QColor& color)
{
    m_gradientStartColor = color;
    if (m_enableGradient)
    {
        UpdateStyle();
        update();
    }
}

QColor CustomProgressBar::gradientStartColor() const
{
    return m_gradientStartColor;
}

void CustomProgressBar::SetGradientEndColor(const QColor& color)
{
    m_gradientEndColor = color;
    if (m_enableGradient)
    {
        UpdateStyle();
        update();
    }
}

QColor CustomProgressBar::gradientEndColor() const
{
    return m_gradientEndColor;
}

void CustomProgressBar::SetEnableAnimation(bool enable)
{
    m_enableAnimation = enable;
    m_animation->setDuration(enable ? m_animationDuration : 0);
}

bool CustomProgressBar::isAnimationEnabled() const
{
    return m_enableAnimation;
}

void CustomProgressBar::SetAnimationDuration(int duration)
{
    m_animationDuration = duration;
    if (m_enableAnimation)
    {
        m_animation->setDuration(duration);
    }
}

int CustomProgressBar::animationDuration() const
{
    return m_animationDuration;
}

void CustomProgressBar::SetTextPosition(EM_TextPosition position)
{
    m_textPosition = position;
    update();
}

CustomProgressBar::EM_TextPosition CustomProgressBar::textPosition() const
{
    return m_textPosition;
}

void CustomProgressBar::SetEnableShadow(bool enable)
{
    m_enableShadow = enable;
    
    if (m_enableShadow)
    {
        auto shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(UIColorDefine::size::DefaultShadowRadius);
        shadow->setColor(m_shadowColor);
        shadow->setOffset(UIColorDefine::size::DefaultShadowOffset, UIColorDefine::size::DefaultShadowOffset);
        setGraphicsEffect(shadow);
    }
    else
    {
        setGraphicsEffect(nullptr);
    }
}

bool CustomProgressBar::isShadowEnabled() const
{
    return m_enableShadow;
}

void CustomProgressBar::SetShadowColor(const QColor& color)
{
    m_shadowColor = color;
    if (m_enableShadow)
    {
        SetEnableShadow(true);
    }
}

QColor CustomProgressBar::shadowColor() const
{
    return m_shadowColor;
}

void CustomProgressBar::SetEnableBorder(bool enable)
{
    m_enableBorder = enable;
    UpdateStyle();
    update();
}

bool CustomProgressBar::isBorderEnabled() const
{
    return m_enableBorder;
}

void CustomProgressBar::SetBorderColor(const QColor& color)
{
    m_borderColor = color;
    if (m_enableBorder)
    {
        UpdateStyle();
        update();
    }
}

QColor CustomProgressBar::borderColor() const
{
    return m_borderColor;
}

void CustomProgressBar::SetBorderWidth(int width)
{
    m_borderWidth = width;
    if (m_enableBorder)
    {
        UpdateStyle();
        update();
    }
}

int CustomProgressBar::borderWidth() const
{
    return m_borderWidth;
}

void CustomProgressBar::SetBorderRadius(int radius)
{
    m_borderRadius = radius;
    UpdateStyle();
    update();
}

int CustomProgressBar::borderRadius() const
{
    return m_borderRadius;
}

void CustomProgressBar::SetEnableStripes(bool enable)
{
    m_enableStripes = enable;
    if (enable)
    {
        SlotStartStripeAnimation();
    }
    else
    {
        SlotStopStripeAnimation();
    }
    update();
}

bool CustomProgressBar::isStripesEnabled() const
{
    return m_enableStripes;
}

void CustomProgressBar::SetStripeDirection(EM_StripeDirection direction)
{
    m_stripeDirection = direction;
    if (m_enableStripes)
    {
        update();
    }
}

CustomProgressBar::EM_StripeDirection CustomProgressBar::stripeDirection() const
{
    return m_stripeDirection;
}

void CustomProgressBar::SetValueWithAnimation(int value)
{
    if (m_enableAnimation)
    {
        m_animation->stop();
        m_animation->setStartValue(this->value());
        m_animation->setEndValue(value);
        m_animation->start();
    }
    else
    {
        setValue(value);
    }
}

void CustomProgressBar::Reset()
{
    if (m_animation != nullptr)
    {
        m_animation->stop();
    }
    setValue(minimum());
    m_stripeOffset = 0;
    update();
}

void CustomProgressBar::SlotStartStripeAnimation()
{
    if (m_stripeTimer != nullptr && !m_stripeTimer->isActive())
    {
        m_stripeTimer->start();
    }
}

void CustomProgressBar::SlotStopStripeAnimation()
{
    if (m_stripeTimer != nullptr && m_stripeTimer->isActive())
    {
        m_stripeTimer->stop();
    }
}

void CustomProgressBar::SlotAnimationFinished()
{
    emit SigAnimationFinished();
}

void CustomProgressBar::SlotUpdateStripeAnimation()
{
    m_stripeOffset = (m_stripeOffset + 2) % 20;
    update();
}

void CustomProgressBar::UpdateStyle()
{
    m_styleSheet = QString();

    // 基础样式
    m_styleSheet += QString("QProgressBar { ");
    m_styleSheet += QString("background-color: %1; ").arg(UIColorDefine::color_convert::ToCssString(m_backgroundColor));
    m_styleSheet += QString("color: %1; ").arg(UIColorDefine::color_convert::ToCssString(m_textColor));

    // 边框样式
    if (m_enableBorder)
    {
        m_styleSheet += QString("border: %1px solid %2; ")
                        .arg(m_borderWidth)
                        .arg(UIColorDefine::color_convert::ToCssString(m_borderColor));
    }
    else
    {
        m_styleSheet += "border: none; ";
    }

    // 圆角样式
    if (m_borderRadius > 0)
    {
        m_styleSheet += QString("border-radius: %1px; ").arg(m_borderRadius);
    }

    m_styleSheet += "text-align: center; } ";

    // 进度条chunk样式
    m_styleSheet += "QProgressBar::chunk { ";
    
    if (m_enableGradient)
    {
        m_styleSheet += QString("background: %1; ").arg(UIColorDefine::color_convert::ToGradientString(m_gradientStartColor, m_gradientEndColor));
    }
    else
    {
        m_styleSheet += QString("background-color: %1; ").arg(UIColorDefine::color_convert::ToCssString(m_progressColor));
    }

    if (m_borderRadius > 0)
    {
        m_styleSheet += QString("border-radius: %1px; ").arg(m_borderRadius);
    }

    m_styleSheet += "} ";

    setStyleSheet(m_styleSheet);
}

void CustomProgressBar::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect rect = this->rect();
    
    // 绘制背景
    DrawBackground(&painter, rect);
    
    // 绘制进度
    DrawProgress(&painter, rect);
    
    // 绘制条纹效果
    if (m_enableStripes)
    {
        DrawStripes(&painter, rect);
    }
    
    // 绘制文本
    if (m_textPosition != TextPosition_Hidden)
    {
        DrawText(&painter, rect);
    }
}

void CustomProgressBar::valueChanged(int value)
{
    QProgressBar::valueChanged(value);
    emit SigValueChanged(value);
}

void CustomProgressBar::DrawBackground(QPainter* painter, const QRect& rect)
{
    painter->save();
    
    QPainterPath path;
    if (m_borderRadius > 0)
    {
        path.addRoundedRect(rect, m_borderRadius, m_borderRadius);
    }
    else
    {
        path.addRect(rect);
    }
    
    painter->fillPath(path, m_backgroundColor);
    
    // 绘制边框
    if (m_enableBorder)
    {
        QPen pen(m_borderColor, m_borderWidth);
        painter->setPen(pen);
        painter->drawPath(path);
    }
    
    painter->restore();
}

void CustomProgressBar::DrawProgress(QPainter* painter, const QRect& rect)
{
    if (value() <= minimum())
    {
        return;
    }
    
    painter->save();
    
    QRect progressRect = GetProgressRect(rect);
    
    QPainterPath path;
    if (m_borderRadius > 0)
    {
        path.addRoundedRect(progressRect, m_borderRadius, m_borderRadius);
    }
    else
    {
        path.addRect(progressRect);
    }
    
    if (m_enableGradient)
    {
        QLinearGradient gradient;
        gradient.setStart(progressRect.topLeft());
        gradient.setFinalStop(progressRect.topRight());
        gradient.setColorAt(0, m_gradientStartColor);
        gradient.setColorAt(1, m_gradientEndColor);
        painter->fillPath(path, gradient);
    }
    else
    {
        painter->fillPath(path, m_progressColor);
    }
    
    painter->restore();
}

void CustomProgressBar::DrawStripes(QPainter* painter, const QRect& rect)
{
    if (value() <= minimum())
    {
        return;
    }
    
    painter->save();
    
    QRect progressRect = GetProgressRect(rect);
    painter->setClipRect(progressRect);
    
    // 设置条纹颜色（略微透明的白色）
    QColor stripeColor(255, 255, 255, 50);
    painter->setBrush(stripeColor);
    painter->setPen(Qt::NoPen);
    
    int stripeWidth = 10;
    int spacing = 10;
    
    switch (m_stripeDirection)
    {
        case StripeDirection_LeftToRight:
        case StripeDirection_RightToLeft:
        {
            int offset = (m_stripeDirection == StripeDirection_LeftToRight) ? m_stripeOffset : -m_stripeOffset;
            for (int x = progressRect.left() - stripeWidth + offset; x < progressRect.right(); x += stripeWidth + spacing)
            {
                QRect stripeRect(x, progressRect.top(), stripeWidth, progressRect.height());
                painter->drawRect(stripeRect);
            }
            break;
        }
        case StripeDirection_Diagonal:
        {
            for (int i = -progressRect.height(); i < progressRect.width() + progressRect.height(); i += stripeWidth + spacing)
            {
                QPolygon stripe;
                int x = i + m_stripeOffset;
                stripe << QPoint(x, progressRect.top())
                       << QPoint(x + stripeWidth, progressRect.top())
                       << QPoint(x + stripeWidth - progressRect.height(), progressRect.bottom())
                       << QPoint(x - progressRect.height(), progressRect.bottom());
                painter->drawPolygon(stripe);
            }
            break;
        }
    }
    
    painter->restore();
}

void CustomProgressBar::DrawText(QPainter* painter, const QRect& rect)
{
    painter->save();
    
    QString text = QString("%1%").arg(static_cast<int>((static_cast<double>(value() - minimum()) / (maximum() - minimum())) * 100));
    
    painter->setPen(m_textColor);
    painter->setFont(font());
    
    QFontMetrics fm(font());
    QRect textRect = rect;
    
    switch (m_textPosition)
    {
        case TextPosition_Center:
            painter->drawText(rect, Qt::AlignCenter, text);
            break;
        case TextPosition_Left:
            textRect.setLeft(textRect.left() + 5);
            painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);
            break;
        case TextPosition_Right:
            textRect.setRight(textRect.right() - 5);
            painter->drawText(textRect, Qt::AlignRight | Qt::AlignVCenter, text);
            break;
        case TextPosition_Outside:
            textRect.setLeft(rect.right() + 5);
            textRect.setWidth(fm.horizontalAdvance(text) + 10);
            painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, text);
            break;
        case TextPosition_Hidden:
            // 不绘制文本
            break;
    }
    
    painter->restore();
}

QRect CustomProgressBar::GetProgressRect(const QRect& rect) const
{
    if (maximum() <= minimum())
    {
        return QRect();
    }
    
    double progress = static_cast<double>(value() - minimum()) / (maximum() - minimum());
    int progressWidth = static_cast<int>(rect.width() * progress);
    
    QRect progressRect = rect;
    progressRect.setWidth(progressWidth);
    
    // 考虑边框宽度
    if (m_enableBorder)
    {
        progressRect.adjust(m_borderWidth, m_borderWidth, 0, -m_borderWidth);
    }
    
    return progressRect;
} 