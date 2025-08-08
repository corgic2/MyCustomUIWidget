#include "CustomProgressBar.h"
#include <QDebug>
#include <QStyleOption>
#include "ProgressBarPainter.h"
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
    SwitchPainter();
}

CustomProgressBar::~CustomProgressBar() = default;

void CustomProgressBar::SetProgressValue(int value)
{
    if (value < minimum())
    {
        value = minimum();
    }
    else if (value > maximum())
    {
        value = maximum();
    }

    m_targetValue = value;

    if (m_animationEnabled && m_progressAnimation)
    {
        m_progressAnimation->setStartValue(m_animatedValue);
        m_progressAnimation->setEndValue(value);
        m_progressAnimation->start();
    }
    else
    {
        SetValueImmediately(value);
    }

    emit SigProgressValueChanged(value);
}

void CustomProgressBar::SetAnimatedValue(int value)
{
    if (m_animatedValue != value)
    {
        m_animatedValue = value;
        update();
    }
}

void CustomProgressBar::SetProgressState(EM_ProgressState state)
{
    if (m_progressState != state)
    {
        m_progressState = state;
        UpdateProgressStyle();
        emit SigProgressStateChanged(state);
        update();
    }
}

void CustomProgressBar::SetCircular(bool circular)
{
    if (m_circular != circular)
    {
        m_circular = circular;
        setAttribute(Qt::WA_OpaquePaintEvent, circular);
        SwitchPainter();
        updateGeometry();
        update();
    }
}

void CustomProgressBar::SetShowCircularRing(bool show)
{
    if (m_showCircularRing != show)
    {
        m_showCircularRing = show;
        update();
    }
}

void CustomProgressBar::SetAnimationConfig(const ST_AnimationConfig& config)
{
    m_animationConfig = config;
    if (m_progressAnimation)
    {
        m_progressAnimation->setDuration(config.m_animationDuration);
        m_progressAnimation->setEasingCurve(config.m_easingType);
    }
}

void CustomProgressBar::SetAnimationEnabled(bool enabled)
{
    m_animationEnabled = enabled;
    if (!enabled && m_progressAnimation && m_progressAnimation->state() == QAbstractAnimation::Running)
    {
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
    m_progressAnimation = std::make_unique<QPropertyAnimation>(this, "animatedValue");
    m_progressAnimation->setDuration(m_animationConfig.m_animationDuration);
    m_progressAnimation->setEasingCurve(m_animationConfig.m_easingType);

    connect(m_progressAnimation.get(), &QPropertyAnimation::finished, this, &CustomProgressBar::SlotOnAnimationFinished);
}

void CustomProgressBar::UpdateProgressStyle()
{
    QString stateName;
    switch (m_progressState)
    {
        case EM_ProgressState::EM_PROGRESS_NORMAL:
            stateName = "progress-normal";
            break;
        case EM_ProgressState::EM_PROGRESS_SUCCESS:
            stateName = "progress-success";
            break;
        case EM_ProgressState::EM_PROGRESS_WARNING:
            stateName = "progress-warning";
            break;
        case EM_ProgressState::EM_PROGRESS_ERROR:
            stateName = "progress-error";
            break;
    }

    setProperty("progress-state", stateName);
    style()->unpolish(this);
    style()->polish(this);
    update();
}

void CustomProgressBar::SwitchPainter()
{
    if (m_circular && m_showCircularRing)
    {
        m_painter = std::make_unique<CircularProgressPainter>(this);
    }
    else
    {
        m_painter = std::make_unique<LinearProgressPainter>(this);
    }
}

void CustomProgressBar::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)

    if (!m_painter)
    {
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    m_painter->Paint(painter, rect());
}

void CustomProgressBar::resizeEvent(QResizeEvent* event)
{
    QProgressBar::resizeEvent(event);
    update();
}

void CustomProgressBar::SlotOnAnimationFinished()
{
    emit SigAnimationFinished();
}
