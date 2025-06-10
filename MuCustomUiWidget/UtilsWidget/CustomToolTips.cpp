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
    , m_opacity(1.0)
    , m_showDuration(UIColorDefine::size::TipsShowDuration)
    , m_animationDuration(UIColorDefine::size::TipsAnimationDuration)
    , m_isAnimating(false)
    , m_targetPosition(QPoint())
    , m_borderWidth(1)
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

    // 初始化默认值
    m_tipsType = Normal;
    m_backgroundColor = UIColorDefine::background_color::ToolTipsNormal;
    m_textColor = UIColorDefine::font_color::Primary;
    m_borderColor = UIColorDefine::border_color::Default;
    m_borderWidth = UIColorDefine::size::DefaultBorderWidth;
    m_radius = UIColorDefine::size::TipsRadius;

    // 设置标签属性
    m_ui->label->setWordWrap(true);
    m_ui->labelEx->setWordWrap(true);
    m_ui->label->setMinimumHeight(30);
    m_ui->labelEx->setMinimumHeight(30);

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
            m_backgroundColor = UIColorDefine::background_color::Warning;
            break;
        case Error:
            m_backgroundColor = UIColorDefine::background_color::Error;
            break;
        case Success:
            m_backgroundColor = UIColorDefine::background_color::Success;
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


void CustomToolTips::UpdateStyle()
{
    // 主窗口样式
    QString mainStyle = QString(
                                "QWidget#CustomToolTipsClass {"
                                "   background-color: %1;"
                                "   border: %2px solid %3;"
                                "   border-radius: %4px;"
                                "   padding: 8px;"
                                "}")
                        .arg(UIColorDefine::color_convert::ToCssString(m_backgroundColor))
                        .arg(m_borderWidth)
                        .arg(UIColorDefine::color_convert::ToCssString(m_borderColor))
                        .arg(m_radius);

    // 内部frame样式
    auto frameStyle = QString(
                              "QFrame#frame {"
                              "   border: none;"
                              "   margin: 0px;"
                              "}");

    // 标签样式
    QString labelStyle = QString(
                                 "CustomLabel {"
                                 "   color: %1;"
                                 "   font-size: %2px;"
                                 "   padding: 2px 4px;"
                                 "   margin: 0px;"
                                 "}")
                         .arg(UIColorDefine::color_convert::ToCssString(m_textColor))
                         .arg(m_fontSize);

    // 合并样式
    QString style = mainStyle + frameStyle + labelStyle;
    setStyleSheet(style);

    update();
}

void CustomToolTips::ShowTips(const QPoint& pos)
{
    m_targetPosition = pos;
    
    // 停止任何正在进行的动画
    if (m_opacityAnimation->state() == QAbstractAnimation::Running)
    {
        m_opacityAnimation->stop();
    }

    // 设置窗口位置
    QSize size = sizeHint();
    QPoint targetPos = pos;

    // 确保提示框完全显示在屏幕内
    QScreen* screen = QGuiApplication::screenAt(pos);
    if (screen)
    {
        QRect screenGeometry = screen->geometry();

        // 检查右边界
        if (targetPos.x() + size.width() > screenGeometry.right())
        {
            targetPos.setX(screenGeometry.right() - size.width());
        }

        // 检查下边界
        if (targetPos.y() + size.height() > screenGeometry.bottom())
        {
            targetPos.setY(pos.y() - size.height());
        }

        // 检查左边界
        if (targetPos.x() < screenGeometry.left())
        {
            targetPos.setX(screenGeometry.left());
        }

        // 检查上边界
        if (targetPos.y() < screenGeometry.top())
        {
            targetPos.setY(screenGeometry.top());
        }
    }

    // 移动到目标位置
    move(targetPos);

    // 开始显示动画
    m_isAnimating = true;
    m_opacityAnimation->setStartValue(0.0);
    m_opacityAnimation->setEndValue(1.0);
    m_opacityAnimation->start();
    if (m_ui->labelEx->text().isEmpty())
    {
        m_ui->labelEx->hide();
        setFixedSize(this->size().width(), this->size().height() - m_ui->labelEx->height());
    }
    else
    {
        m_ui->labelEx->show();
        setFixedSize(this->size().width(), this->size().height() + m_ui->labelEx->height());
    }
    show();

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
