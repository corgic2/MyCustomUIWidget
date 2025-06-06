#include "CustomToolTips.h"
#include <QApplication>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QPainterPath>
#include <QScreen>

CustomToolTips::CustomToolTips(QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::CustomToolTipsClass)
    , m_hideTimer(new QTimer(this))
    , m_opacityAnimation(nullptr)
    , m_tipsType(Normal)
    , m_fontSize(UIColorDefine::size::TipsFontSize)
    , m_radius(UIColorDefine::size::TipsRadius)
    , m_hasShadow(false)
    , m_opacity(1.0)
    , m_showDuration(UIColorDefine::size::TipsShowDuration)
    , m_animationDuration(UIColorDefine::size::TipsAnimationDuration)
    , m_isAnimating(false)
    , m_targetPosition(QPoint())
    , m_borderWidth(1)
    , m_shadowRadius(10)
    , m_shadowOffset(QPoint(0, 2))
{
    m_ui->setupUi(this);
    InitializeWidget();
    SetupAnimation();
}

CustomToolTips::~CustomToolTips()
{
    delete m_ui;
}

void CustomToolTips::leaveEvent(QEvent* event)
{
    QWidget::leaveEvent(event);
    m_hideTimer->start(m_showDuration);
}

void CustomToolTips::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);
}

void CustomToolTips::InitializeWidget()
{
    // 设置窗口属性
    setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    // 初始化默认值
    m_tipsType = Normal;
    m_backgroundColor = UIColorDefine::background_color::ToolTipsNormal;
    m_textColor = UIColorDefine::font_color::Primary;
    m_borderColor = UIColorDefine::border_color::Default;
    m_borderWidth = UIColorDefine::size::DefaultBorderWidth;
    m_radius = UIColorDefine::size::TipsRadius;
    m_hasShadow = false;
    m_shadowColor = UIColorDefine::shadow_color::Default;
    m_shadowOffset = QPoint(0, 2);
    m_shadowRadius = UIColorDefine::size::DefaultShadowRadius;

    m_hideTimer->setSingleShot(true);
    connect(m_hideTimer, &QTimer::timeout, this, &CustomToolTips::HideTips);

    UpdateStyle();
}

void CustomToolTips::SetupAnimation()
{
    m_opacityAnimation = new QPropertyAnimation(this, "opacity", this);
    m_opacityAnimation->setDuration(m_animationDuration);
    m_opacityAnimation->setEasingCurve(QEasingCurve::OutCubic);
}

void CustomToolTips::SetToolTips(const QString& text)
{
    m_ui->label->setText(text);
}


void CustomToolTips::SetToolTipsEx(const QString& text)
{
    m_ui->labelEx->setText(text);
    m_ui->labelEx->setVisible(!text.isEmpty());
}

void CustomToolTips::SetTipsType(EM_TipsType type)
{
    m_tipsType = type;
    switch (type)
    {
        case Info:
            m_backgroundColor = UIColorDefine::background_color::ToolTipsInfo;
            break;
        case Warning:
            m_backgroundColor = UIColorDefine::background_color::ToolTipsWarning;
            break;
        case Error:
            m_backgroundColor = UIColorDefine::background_color::ToolTipsError;
            break;
        case Success:
            m_backgroundColor = UIColorDefine::background_color::ToolTipsSuccess;
            break;
        default:
            m_backgroundColor = UIColorDefine::background_color::ToolTipsNormal;
            break;
    }
    UpdateStyle();
}

void CustomToolTips::SetBackgroundColor(const QColor& color)
{
    m_backgroundColor = color;
    UpdateStyle();
}

void CustomToolTips::SetTextColor(const QColor& color)
{
    m_textColor = color;
    UpdateStyle();
}

void CustomToolTips::SetBorderColor(const QColor& color)
{
    m_borderColor = color;
    UpdateStyle();
}

void CustomToolTips::SetFontSize(int size)
{
    m_fontSize = size;
    UpdateStyle();
}

void CustomToolTips::SetRadius(int radius)
{
    m_radius = radius;
    UpdateStyle();
}

void CustomToolTips::SetShowDuration(int msecs)
{
    m_showDuration = msecs;
}

void CustomToolTips::SetAnimationDuration(int msecs)
{
    m_animationDuration = msecs;
    if (m_opacityAnimation)
    {
        m_opacityAnimation->setDuration(msecs);
    }
}

void CustomToolTips::EnableShadow(bool enable)
{
    m_hasShadow = enable;

    if (m_hasShadow)
    {
        auto shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(m_shadowRadius);
        shadow->setColor(m_shadowColor);
        shadow->setOffset(m_shadowOffset.x(), m_shadowOffset.y());
        setGraphicsEffect(shadow);
    }
    else
    {
        setGraphicsEffect(nullptr);
    }

    UpdateStyle();
}

void CustomToolTips::SetShadowColor(const QColor& color)
{
    m_shadowColor = color;
    if (m_hasShadow)
    {
        auto shadow = qobject_cast<QGraphicsDropShadowEffect*>(graphicsEffect());
        if (shadow)
        {
            shadow->setColor(m_shadowColor);
        }
    }
}

void CustomToolTips::SetShadowOffset(const QPoint& offset)
{
    m_shadowOffset = offset;
    if (m_hasShadow)
    {
        auto shadow = qobject_cast<QGraphicsDropShadowEffect*>(graphicsEffect());
        if (shadow)
        {
            shadow->setOffset(m_shadowOffset.x(), m_shadowOffset.y());
        }
    }
}

void CustomToolTips::SetShadowRadius(int radius)
{
    m_shadowRadius = radius;
    if (m_hasShadow)
    {
        auto shadow = qobject_cast<QGraphicsDropShadowEffect*>(graphicsEffect());
        if (shadow)
        {
            shadow->setBlurRadius(m_shadowRadius);
        }
    }
}

void CustomToolTips::UpdateStyle()
{
    QString style = QString(
        "QWidget#CustomToolTipsClass {"
        "   background-color: %1;"
        "   color: %2;"
        "   border: %3px solid %4;"
        "   border-radius: %5px;"
        "}")
                    .arg(UIColorDefine::color_convert::ToCssString(m_backgroundColor))
                    .arg(UIColorDefine::color_convert::ToCssString(m_textColor))
        .arg(m_borderWidth)
                    .arg(UIColorDefine::color_convert::ToCssString(m_borderColor))
        .arg(m_radius);

    setStyleSheet(style);
}

void CustomToolTips::ShowTips(const QPoint& pos)
{
    m_targetPosition = pos;
    // 停止任何正在进行的动画
    if (m_opacityAnimation->state() == QAbstractAnimation::Running)
    {
        m_opacityAnimation->stop();
    }

    m_isAnimating = true;
    m_opacityAnimation->setStartValue(0.0);
    m_opacityAnimation->setEndValue(1.0);
    show();
    m_opacityAnimation->start();

    // 设置自动隐藏定时器
    m_hideTimer->start(m_showDuration);
    
    emit ToolTipsShown();
}

void CustomToolTips::ShowTipsForWidget(QWidget* widget, const QPoint& offset)
{
    if (!widget)
    {
        return;
    }

    QPoint pos = widget->mapToGlobal(QPoint(0, 0));
    pos += offset;
    ShowTips(pos);
}

void CustomToolTips::HideTips()
{
    if (!m_isAnimating)
    {
        m_isAnimating = true;
        m_opacityAnimation->setStartValue(m_opacity);
        m_opacityAnimation->setEndValue(0.0);
        connect(m_opacityAnimation, &QPropertyAnimation::finished,
                this, &CustomToolTips::OnHideAnimationFinished);
        m_opacityAnimation->start();
    }
}

void CustomToolTips::enterEvent(QEvent* event)
{
    QWidget::enterEvent(event);
    m_hideTimer->stop();
}

void CustomToolTips::setOpacity(qreal opacity)
{
    m_opacity = opacity;
    setWindowOpacity(opacity);
}

void CustomToolTips::OnHideAnimationFinished()
{
    if (m_opacity <= 0.0)
    {
        hide();
        emit ToolTipsHidden();
    }
}
