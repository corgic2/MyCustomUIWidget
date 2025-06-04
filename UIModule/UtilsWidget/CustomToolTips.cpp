#include "CustomToolTips.h"
#include <QApplication>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QPainterPath>
#include <QScreen>

CustomToolTips* CustomToolTipsManager::s_instance = nullptr;

CustomToolTips::CustomToolTips(QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::CustomToolTipsClass())
    , m_hideTimer(new QTimer(this))
    , m_opacityAnimation(nullptr)
    , m_position(Bottom)
    , m_tipsType(Normal)
    , m_fontSize(UIColorDefine::size::TipsFontSize)
    , m_radius(UIColorDefine::size::TipsRadius)
    , m_hasShadow(true)
    , m_opacity(1.0)
    , m_showDuration(UIColorDefine::size::TipsShowDuration)
    , m_animationDuration(UIColorDefine::size::TipsAnimationDuration)
    , m_isAnimating(false)
    , m_targetPosition(QPoint())
{
    InitializeUI();
    SetupAnimation();
}

CustomToolTips::~CustomToolTips()
{
    SAFE_DELETE_POINTER_VALUE(m_ui);
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

void CustomToolTips::InitializeUI()
{
    m_ui->setupUi(this);
    setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose, false);

    // 修正：使用正确的颜色定义
    m_backgroundColor = UIColorDefine::background_color::ToolTipsNormal;
    m_textColor = UIColorDefine::font_color::Primary;

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

void CustomToolTips::SetToolTips(const QString& str)
{
    m_ui->label->setText(str);
    m_ui->label_2->hide();
    adjustSize();
}

void CustomToolTips::SetToolTipsEx(const QString& str)
{
    m_ui->label_2->setText(str);
    m_ui->label_2->show();
    adjustSize();
}

void CustomToolTips::SetTipsType(EM_TipsType type)
{
    m_tipsType = type;

    // 根据类型设置相应的样式
    switch (type)
    {
        case Info:
            SetBackgroundColor(UIColorDefine::background_color::ToolTipsInfo);
            SetTextColor(UIColorDefine::font_color::Info);
            break;
        case Warning:
            SetBackgroundColor(UIColorDefine::background_color::ToolTipsWarning);
            SetTextColor(UIColorDefine::font_color::Warning);
            break;
        case Error:
            SetBackgroundColor(UIColorDefine::background_color::ToolTipsError);
            SetTextColor(UIColorDefine::font_color::Error);
            break;
        case Success:
            SetBackgroundColor(UIColorDefine::background_color::ToolTipsSuccess);
            SetTextColor(UIColorDefine::font_color::Success);
            break;
        default:
            SetBackgroundColor(UIColorDefine::background_color::ToolTipsNormal);
            SetTextColor(UIColorDefine::font_color::Primary);
            break;
    }
}

void CustomToolTips::SetPosition(EM_TipsPosition position)
{
    m_position = position;
    if (isVisible())
    {
        QPoint currentPos = pos();
        move(CalculatePosition(currentPos, size()));
    }
}

void CustomToolTips::SetBackgroundColor(const UIColorDefine::ST_ColorRgba& color)
{
    m_backgroundColor = color;
    UpdateStyle();
}

void CustomToolTips::SetTextColor(const UIColorDefine::ST_ColorRgb& color)
{
    m_textColor = color;
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
    UpdateStyle();
}

void CustomToolTips::UpdateStyle()
{
    QString style = QString(
                            "QFrame#frame {"
                            "   background-color: %1;"
                            "   border-radius: %2px;"
                            "}"
                            "QLabel {"
                            "   color: %3;"
                            "   font-size: %4px;"
                            "   padding: 5px;"
                            "}")
                    .arg(m_backgroundColor.ToQString())
                    .arg(m_radius)
                    .arg(m_textColor.ToQString())
                    .arg(m_fontSize);

    m_ui->frame->setStyleSheet(style);

    if (m_hasShadow)
    {
        auto shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(10);
        shadow->setColor(UIColorDefine::shadow_color::Light.ToQString());
        shadow->setOffset(0, 2);
        m_ui->frame->setGraphicsEffect(shadow);
    }
    else
    {
        m_ui->frame->setGraphicsEffect(nullptr);
    }
}

void CustomToolTips::ShowTips(const QPoint& pos)
{
    m_targetPosition = pos;
    QPoint showPos = CalculatePosition(pos, size());
    move(showPos);

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
        m_opacityAnimation->setStartValue(opacity());
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

QPoint CustomToolTips::CalculatePosition(const QPoint& targetPos, const QSize& targetSize)
{
    QPoint pos = targetPos;
    QScreen* screen = QApplication::screenAt(targetPos);
    if (!screen)
    {
        return pos;
    }

    QRect screenGeometry = screen->geometry();

    switch (m_position)
    {
        case TopLeft:
            pos.setX(targetPos.x());
            pos.setY(targetPos.y() - targetSize.height());
            break;
        case Top:
            pos.setX(targetPos.x() - targetSize.width() / 2);
            pos.setY(targetPos.y() - targetSize.height());
            break;
        case TopRight:
            pos.setX(targetPos.x() - targetSize.width());
            pos.setY(targetPos.y() - targetSize.height());
            break;
        case Left:
            pos.setX(targetPos.x() - targetSize.width());
            pos.setY(targetPos.y() - targetSize.height() / 2);
            break;
        case Right:
            pos.setX(targetPos.x());
            pos.setY(targetPos.y() - targetSize.height() / 2);
            break;
        case BottomLeft:
            pos.setX(targetPos.x());
            pos.setY(targetPos.y());
            break;
        case Bottom:
            pos.setX(targetPos.x() - targetSize.width() / 2);
            pos.setY(targetPos.y());
            break;
        case BottomRight:
            pos.setX(targetPos.x() - targetSize.width());
            pos.setY(targetPos.y());
            break;
    }

    // 屏幕边界处理
    if (pos.x() + targetSize.width() > screenGeometry.right())
    {
        pos.setX(screenGeometry.right() - targetSize.width());
    }
    if (pos.x() < screenGeometry.left())
    {
        pos.setX(screenGeometry.left());
    }
    if (pos.y() + targetSize.height() > screenGeometry.bottom())
    {
        pos.setY(screenGeometry.bottom() - targetSize.height());
    }
    if (pos.y() < screenGeometry.top())
    {
        pos.setY(screenGeometry.top());
    }

    return pos;
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

// CustomToolTipsManager 实现
CustomToolTips* CustomToolTipsManager::GetInstance()
{
    if (!s_instance)
    {
        s_instance = new CustomToolTips(nullptr);
    }
    return s_instance;
}

void CustomToolTipsManager::ShowTips(const QString& text, QWidget* widget,
                                     CustomToolTips::EM_TipsType type)
{
    CustomToolTips* tips = GetInstance();
    tips->SetToolTips(text);
    tips->SetTipsType(type);
    tips->ShowTipsForWidget(widget);
}
