#include "MusicProgressBar.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QLabel>
#include <QPainter>
#include <QScreen>
#include <QStyleOption>
#include <QToolTip>
#include <QVBoxLayout>
#include <QWindow>
#include "StyleSystem/SkinManager.h"
#include "StyleSystem/SkinStyleLoader.h"

MusicProgressBar::MusicProgressBar(QWidget* parent)
    : QWidget(parent), m_tooltipTimer(new QTimer(this)), m_tooltipWidget(new QWidget(nullptr))
{
    AUTO_LOAD_SKIN_STYLE();
    Initilize();
    Connectionals();
}

MusicProgressBar::~MusicProgressBar()
{
    if (m_tooltipWidget)
    {
        delete m_tooltipWidget;
        m_tooltipWidget = nullptr;
    }
}

void MusicProgressBar::SetPosition(qint64 position)
{
    if (position < 0)
    {
        position = 0;
    }
    if (m_duration > 0 && position > m_duration)
    {
        position = m_duration;
    }

    if (m_position != position)
    {
        m_position = position;
        update();
        emit SigPositionChanged(position);
    }
}

void MusicProgressBar::SetBufferPosition(qint64 position)
{
    if (position < 0)
    {
        position = 0;
    }
    if (m_duration > 0 && position > m_duration)
    {
        position = m_duration;
    }

    if (m_bufferPosition != position)
    {
        m_bufferPosition = position;
        update();
    }
}

void MusicProgressBar::SetDuration(qint64 ms)
{
    if (m_duration != ms)
    {
        m_duration = ms;
        update();
    }
}

void MusicProgressBar::EnableClickJump(bool enable)
{
    m_clickJumpEnabled = enable;
}

void MusicProgressBar::SetTimeFormat(bool showMS)
{
    if (m_showMilliseconds != showMS)
    {
        m_showMilliseconds = showMS;
        update();
    }
}

void MusicProgressBar::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 获取颜色配置
    QColor backgroundColor = SkinManager::instance()->parseColorSheet("@disabled_color");
    QColor progressColor = SkinManager::instance()->parseColorSheet("@success_color");
    QColor bufferColor = SkinManager::instance()->parseColorSheet("@info_color");
    QColor sliderColor = SkinManager::instance()->parseColorSheet("@dark_color");
    QColor textColor = SkinManager::instance()->parseColorSheet("@dark_color");

    // 设置透明度
    backgroundColor.setAlpha(64); // 25% 透明度
    bufferColor.setAlpha(128);    // 50% 透明度

    // 绘制背景
    QRect progressRect = GetProgressRect();
    painter.setPen(Qt::NoPen);
    painter.setBrush(backgroundColor);
    painter.drawRoundedRect(progressRect, 4, 4);

    // 绘制缓冲进度
    QRect bufferRect = GetBufferRect();
    painter.setBrush(bufferColor);
    painter.drawRoundedRect(bufferRect, 4, 4);

    // 绘制已播放进度
    int progressPercent = (m_duration > 0) ? static_cast<int>((m_position * 100) / m_duration) : 0;
    auto playedRect = QRect(progressRect.left(), progressRect.top(), progressRect.width() * progressPercent / 100, progressRect.height());
    painter.setBrush(progressColor);
    painter.drawRoundedRect(playedRect, 4, 4);

    // 绘制滑块
    QRect sliderRect = GetSliderRect();
    painter.setBrush(sliderColor);
    painter.drawEllipse(sliderRect);

    // 绘制时间文本
    QString currentTime = FormatTime(m_position);
    QString totalTime = FormatTime(m_duration);
    QString timeText = currentTime + " / " + totalTime;

    QRect timeRect = GetTimeRect();
    painter.setPen(textColor);
    painter.setFont(QFont("Microsoft YaHei", 9));
    painter.drawText(timeRect, Qt::AlignRight | Qt::AlignVCenter, timeText);
}

void MusicProgressBar::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (m_clickJumpEnabled)
        {
            int progressPercent = CalculateProgress(event->pos());
            qint64 newPosition = (m_duration > 0) ? (m_duration * progressPercent / 100) : 0;
            SetPosition(newPosition);
            emit SigSeekRequested(newPosition);
            emit SigSliderPressed();
            m_isDragging = true;
        }
    }
    QWidget::mousePressEvent(event);
}

void MusicProgressBar::mouseMoveEvent(QMouseEvent* event)
{
    if (m_isDragging && m_clickJumpEnabled)
    {
        int progressPercent = CalculateProgress(event->pos());
        qint64 newPosition = (m_duration > 0) ? (m_duration * progressPercent / 100) : 0;
        SetPosition(newPosition);
        emit SigSeekRequested(newPosition);
    }

    // 更新时间提示
    if (m_isHovering || m_isDragging)
    {
        UpdateTooltipPosition(event->pos());
    }

    QWidget::mouseMoveEvent(event);
}

void MusicProgressBar::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && m_isDragging)
    {
        m_isDragging = false;
        emit SigSliderReleased();
        // 发出最终位置信号
        emit SigSeekRequested(m_position);
    }
    QWidget::mouseReleaseEvent(event);
}

void MusicProgressBar::enterEvent(QEvent* event)
{
    m_isHovering = true;
    update();
    QWidget::enterEvent(event);
}

void MusicProgressBar::leaveEvent(QEvent* event)
{
    m_isHovering = false;
    if (m_tooltipWidget)
    {
        m_tooltipWidget->hide();
    }
    update();
    QWidget::leaveEvent(event);
}

void MusicProgressBar::wheelEvent(QWheelEvent* event)
{
    // 支持鼠标滚轮调整进度
    int delta = event->angleDelta().y() / 120; // 通常一步是120度
    int progressPercent = static_cast<int>((m_duration > 0) ? (m_position * 100 / m_duration) : 0);
    progressPercent += delta;
    if (progressPercent < 0)
    {
        progressPercent = 0;
    }
    if (progressPercent > 100)
    {
        progressPercent = 100;
    }

    qint64 newPosition = (m_duration > 0) ? (m_duration * progressPercent / 100) : 0;
    SetPosition(newPosition);
    emit SigSeekRequested(newPosition);
    QWidget::wheelEvent(event);
}

void MusicProgressBar::keyPressEvent(QKeyEvent* event)
{
    // 支持方向键微调进度
    switch (event->key())
    {
        case Qt::Key_Left:
        case Qt::Key_Down:
        {
            int progressPercent = static_cast<int>((m_duration > 0) ? (m_position * 100 / m_duration) : 0);
            progressPercent -= 1;
            if (progressPercent < 0)
            {
                progressPercent = 0;
            }
            qint64 newPosition = (m_duration > 0) ? (m_duration * progressPercent / 100) : 0;
            SetPosition(newPosition);
            emit SigSeekRequested(newPosition);
            break;
        }
        case Qt::Key_Right:
        case Qt::Key_Up:
        {
            int progressPercent = static_cast<int>((m_duration > 0) ? (m_position * 100 / m_duration) : 0);
            progressPercent += 1;
            if (progressPercent > 100)
            {
                progressPercent = 100;
            }
            qint64 newPosition = (m_duration > 0) ? (m_duration * progressPercent / 100) : 0;
            SetPosition(newPosition);
            emit SigSeekRequested(newPosition);
            break;
        }
        default:
            QWidget::keyPressEvent(event);
    }
}

void MusicProgressBar::Connectionals()
{
    // 连接定时器信号
    connect(m_tooltipTimer, &QTimer::timeout, [this]()
    {
        if (m_tooltipWidget)
        {
            m_tooltipWidget->hide();
        }
        m_tooltipTimer->stop();
    });
}

void MusicProgressBar::Initilize()
{
    // 设置默认大小
    setMinimumHeight(30);
    setMaximumHeight(30);

    // 初始化时间提示控件
    if (m_tooltipWidget)
    {
        m_tooltipWidget->setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
        m_tooltipWidget->setAttribute(Qt::WA_TranslucentBackground);

        auto* layout = new QVBoxLayout(m_tooltipWidget);
        auto* label = new QLabel(m_tooltipWidget);
        label->setObjectName("tooltipLabel");
        label->setStyleSheet("QLabel {" "  background-color: black;" "  color: white;" "  border-radius: 4px;" "  padding: 4px;" "  font-family: 'Microsoft YaHei';" "  font-size: 10px;" "}");
        layout->addWidget(label);
        layout->setContentsMargins(0, 0, 0, 0);
        m_tooltipWidget->setLayout(layout);
        m_tooltipWidget->hide();
    }

    // 设置定时器
    m_tooltipTimer->setSingleShot(true);
    m_tooltipTimer->setInterval(2000); // 2秒后隐藏
}

void MusicProgressBar::ApplyFormatStyle()
{
    // 重新应用样式
    style()->unpolish(this);
    style()->polish(this);
    update();
}

int MusicProgressBar::CalculateProgress(const QPoint& pos) const
{
    QRect progressRect = GetProgressRect();
    int progressWidth = progressRect.width();

    if (progressWidth <= 0)
    {
        return 0;
    }

    int x = pos.x() - progressRect.left();
    int progress = (x * 100) / progressWidth;

    if (progress < 0)
    {
        progress = 0;
    }
    if (progress > 100)
    {
        progress = 100;
    }

    return progress;
}

QString MusicProgressBar::FormatTime(qint64 ms) const
{
    if (ms <= 0)
    {
        return m_showMilliseconds ? "00:00.000" : "00:00";
    }

    qint64 totalSeconds = ms / 1000;
    qint64 minutes = totalSeconds / 60;
    qint64 seconds = totalSeconds % 60;
    qint64 milliseconds = ms % 1000;

    if (m_showMilliseconds)
    {
        return QString("%1:%2.%3").arg(minutes, 2, 10, QLatin1Char('0')).arg(seconds, 2, 10, QLatin1Char('0')).arg(milliseconds, 3, 10, QLatin1Char('0'));
    }
    else
    {
        return QString("%1:%2").arg(minutes, 2, 10, QLatin1Char('0')).arg(seconds, 2, 10, QLatin1Char('0'));
    }
}

QRect MusicProgressBar::GetSliderRect() const
{
    QRect progressRect = GetProgressRect();
    int sliderSize = 12;
    int progressPercent = (m_duration > 0) ? static_cast<int>((m_position * 100) / m_duration) : 0;
    int sliderX = progressRect.left() + (progressRect.width() * progressPercent / 100) - sliderSize / 2;
    int sliderY = progressRect.center().y() - sliderSize / 2;

    // 确保滑块不会超出边界
    if (sliderX < progressRect.left() - sliderSize / 2)
    {
        sliderX = progressRect.left() - sliderSize / 2;
    }
    if (sliderX > progressRect.right() - sliderSize / 2)
    {
        sliderX = progressRect.right() - sliderSize / 2;
    }

    return QRect(sliderX, sliderY, sliderSize, sliderSize);
}

QRect MusicProgressBar::GetProgressRect() const
{
    int height = this->height();
    int progressHeight = 6;
    int progressY = (height - progressHeight) / 2;
    int margin = 80; // 为时间显示留出空间

    // 确保进度条宽度不为负数
    int progressWidth = width() - 2 * margin;
    if (progressWidth < 0)
        progressWidth = 0;

    return QRect(margin, progressY, progressWidth, progressHeight);
}

QRect MusicProgressBar::GetBufferRect() const
{
    QRect progressRect = GetProgressRect();
    int bufferPercent = (m_duration > 0) ? static_cast<int>((m_bufferPosition * 100) / m_duration) : 0;
    return QRect(progressRect.left(), progressRect.top(), progressRect.width() * bufferPercent / 100, progressRect.height());
}

QRect MusicProgressBar::GetTimeRect() const
{
    return QRect(0, 0, width(), height());
}

void MusicProgressBar::UpdateTooltipPosition(const QPoint& pos)
{
    if (!m_tooltipWidget)
    {
        return;
    }

    // 计算对应的时间
    int progressPercent = CalculateProgress(pos);
    qint64 timeMs = (m_duration > 0) ? (m_duration * progressPercent / 100) : 0;
    QString timeText = FormatTime(timeMs);

    // 更新提示文本
    auto* label = m_tooltipWidget->findChild<QLabel*>("tooltipLabel");
    if (label)
    {
        label->setText(timeText);
    }

    // 计算提示位置
    QPoint globalPos = mapToGlobal(pos);
    QSize tooltipSize = m_tooltipWidget->sizeHint();

    // 将提示框定位在鼠标上方
    QPoint tooltipPos(globalPos.x() - tooltipSize.width() / 2, globalPos.y() - tooltipSize.height() - 10);

    // 确保提示框不会超出屏幕边界
    QRect screenGeometry = QApplication::primaryScreen()->geometry();
    if (tooltipPos.x() < screenGeometry.left())
    {
        tooltipPos.setX(screenGeometry.left());
    }
    if (tooltipPos.x() + tooltipSize.width() > screenGeometry.right())
    {
        tooltipPos.setX(screenGeometry.right() - tooltipSize.width());
    }
    if (tooltipPos.y() < screenGeometry.top())
    {
        tooltipPos.setY(globalPos.y() + 20);
    }

    m_tooltipWidget->move(tooltipPos);
    m_tooltipWidget->show();

    // 重启定时器
    m_tooltipTimer->start();
}
