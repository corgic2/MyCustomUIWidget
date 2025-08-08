#include "CustomProgressBar.h"
#include <QGraphicsDropShadowEffect>
#include <QLinearGradient>
#include <QRadialGradient>
#include <QPainterPath>
#include <QFontMetrics>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>
#include "StyleSystem/SkinStyleLoader.h"

CustomProgressBar::CustomProgressBar(QWidget* parent)
    : QProgressBar(parent)
{
    AUTO_LOAD_SKIN_STYLE();
    
    setTextVisible(true);
    setAlignment(Qt::AlignCenter);
    setMinimum(0);
    setMaximum(100);
    
    InitializeAnimation();
    UpdateProgressStyle();
}

CustomProgressBar::~CustomProgressBar()
{
    if (m_progressAnimation) {
        m_progressAnimation->stop();
        delete m_progressAnimation;
        m_progressAnimation = nullptr;
    }
    
    if (m_pulseTimer) {
        m_pulseTimer->stop();
        delete m_pulseTimer;
        m_pulseTimer = nullptr;
    }
}

void CustomProgressBar::SetProgressValue(int value)
{
    if (value < minimum()) {
        value = minimum();
    } else if (value > maximum()) {
        value = maximum();
    }
    
    m_targetValue = value;
    
    if (m_animationEnabled && m_progressAnimation) {
        m_progressAnimation->setStartValue(m_animatedValue);
        m_progressAnimation->setEndValue(value);
        m_progressAnimation->start();
    } else {
        SetValueImmediately(value);
    }
    
    emit SigProgressValueChanged(value);
}

int CustomProgressBar::GetAnimatedValue() const
{
    return m_animatedValue;
}

void CustomProgressBar::SetAnimatedValue(int value)
{
    if (m_animatedValue != value) {
        m_animatedValue = value;
        update();
    }
}

void CustomProgressBar::SetProgressState(EM_ProgressState state)
{
    if (m_progressState != state) {
        m_progressState = state;
        UpdateProgressStyle();
        emit SigProgressStateChanged(state);
        update();
    }
}

CustomProgressBar::EM_ProgressState CustomProgressBar::GetProgressState() const
{
    return m_progressState;
}

void CustomProgressBar::SetCircular(bool circular)
{
    if (m_circular != circular) {
        m_circular = circular;
        setAttribute(Qt::WA_OpaquePaintEvent, circular);
        updateGeometry();
        update();
    }
}

bool CustomProgressBar::GetCircular() const
{
    return m_circular;
}

void CustomProgressBar::SetAnimationConfig(const ST_AnimationConfig& config)
{
    m_animationConfig = config;
    if (m_progressAnimation) {
        m_progressAnimation->setDuration(config.m_animationDuration);
        m_progressAnimation->setEasingCurve(config.m_easingType);
    }
}

CustomProgressBar::ST_AnimationConfig CustomProgressBar::GetAnimationConfig() const
{
    return m_animationConfig;
}

void CustomProgressBar::SetAnimationEnabled(bool enabled)
{
    m_animationEnabled = enabled;
    if (!enabled && m_progressAnimation && m_progressAnimation->state() == QAbstractAnimation::Running) {
        m_progressAnimation->stop();
        SetValueImmediately(m_targetValue);
    }
}

void CustomProgressBar::SetValueImmediately(int value)
{
    m_animatedValue = value;
    setValue(value);
    update();
}

void CustomProgressBar::InitializeAnimation()
{
    m_progressAnimation = new QPropertyAnimation(this, "animatedValue");
    m_progressAnimation->setDuration(m_animationConfig.m_animationDuration);
    m_progressAnimation->setEasingCurve(m_animationConfig.m_easingType);
    
    connect(m_progressAnimation, &QPropertyAnimation::finished, this, &CustomProgressBar::SlotOnAnimationFinished);
}

void CustomProgressBar::UpdateProgressStyle()
{
    switch (m_progressState) {
    case EM_ProgressState::EM_PROGRESS_NORMAL:
        setProperty("progress-state", "progress-normal");
        break;
    case EM_ProgressState::EM_PROGRESS_SUCCESS:
        setProperty("progress-state", "progress-success");
        break;
    case EM_ProgressState::EM_PROGRESS_WARNING:
        setProperty("progress-state", "progress-warning");
        break;
    case EM_ProgressState::EM_PROGRESS_ERROR:
        setProperty("progress-state", "progress-error");
        break;
    }
    
    style()->unpolish(this);
    style()->polish(this);
    update();
}

void CustomProgressBar::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    if (m_circular) {
        DrawCircularProgress(painter, rect());
    } else {
        DrawLinearProgress(painter, rect());
    }
}

void CustomProgressBar::resizeEvent(QResizeEvent* event)
{
    QProgressBar::resizeEvent(event);
    update();
}

void CustomProgressBar::DrawLinearProgress(QPainter& painter, const QRect& rect)
{
    QStyleOptionProgressBar option;
    option.initFrom(this);
    option.rect = rect;
    option.minimum = minimum();
    option.maximum = maximum();
    option.progress = m_animatedValue;
    option.text = text();
    option.textVisible = isTextVisible();
    option.textAlignment = alignment();
    
    style()->drawControl(QStyle::CE_ProgressBar, &option, &painter, this);
}

void CustomProgressBar::DrawCircularProgress(QPainter& painter, const QRect& rect)
{
    int size = qMin(rect.width(), rect.height());
    int centerX = rect.center().x();
    int centerY = rect.center().y();
    int radius = size / 2 - 10;
    
    QRectF arcRect(centerX - radius, centerY - radius, radius * 2, radius * 2);
    
    // 背景圆环
    painter.setPen(QPen(QColor(200, 200, 200), 8));
    painter.drawEllipse(arcRect);
    
    // 进度圆环
    qreal progressAngle = 360.0 * m_animatedValue / maximum();
    
    QColor progressColor;
    switch (m_progressState) {
    case EM_ProgressState::EM_PROGRESS_SUCCESS:
        progressColor = QColor(40, 167, 69);
        break;
    case EM_ProgressState::EM_PROGRESS_WARNING:
        progressColor = QColor(255, 193, 7);
        break;
    case EM_ProgressState::EM_PROGRESS_ERROR:
        progressColor = QColor(220, 53, 69);
        break;
    default:
        progressColor = QColor(0, 123, 255);
        break;
    }
    
    painter.setPen(QPen(progressColor, 8));
    painter.drawArc(arcRect, 90 * 16, -progressAngle * 16);
    
    // 中心文本
    QFont font = painter.font();
    font.setPixelSize(12);
    font.setBold(true);
    painter.setFont(font);
    
    QString text = QString("%1%").arg(m_animatedValue);
    painter.setPen(Qt::black);
    painter.drawText(arcRect, Qt::AlignCenter, text);
}

void CustomProgressBar::SlotOnAnimationFinished()
{
    emit SigAnimationFinished();
}

