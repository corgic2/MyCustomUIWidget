#include "MusicProgressBar.h"
#include <QPainter>
#include <QStyleOption>
#include <QToolTip>
#include <QLabel>
#include <QVBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QWindow>
#include "StyleSystem/SkinStyleLoader.h"
#include "StyleSystem/SkinManager.h"

MusicProgressBar::MusicProgressBar(QWidget* parent)
    : QWidget(parent)
    , m_tooltipTimer(new QTimer(this))
    , m_tooltipWidget(new QWidget(nullptr))
{
    AUTO_LOAD_SKIN_STYLE();
    Initilize();
    Connectionals();
}

MusicProgressBar::~MusicProgressBar()
{
    if (m_tooltipWidget) {
        delete m_tooltipWidget;
        m_tooltipWidget = nullptr;
    }
}

void MusicProgressBar::SetProgress(int value)
{
    if (value < 0) value = 0;
    if (value > 100) value = 100;
    
    if (m_progress != value) {
        m_progress = value;
        update();
        emit SigProgressChanged(value);
    }
}

void MusicProgressBar::SetBufferProgress(int value)
{
    if (value < 0) value = 0;
    if (value > 100) value = 100;
    
    if (m_bufferProgress != value) {
        m_bufferProgress = value;
        update();
    }
}

void MusicProgressBar::SetDuration(qint64 ms)
{
    if (m_duration != ms) {
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
    if (m_showMilliseconds != showMS) {
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
    backgroundColor.setAlpha(64);  // 25% 透明度
    bufferColor.setAlpha(128);     // 50% 透明度
    
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
    QRect playedRect = QRect(progressRect.left(), progressRect.top(), 
                            progressRect.width() * m_progress / 100, progressRect.height());
    painter.setBrush(progressColor);
    painter.drawRoundedRect(playedRect, 4, 4);
    
    // 绘制滑块
    QRect sliderRect = GetSliderRect();
    painter.setBrush(sliderColor);
    painter.drawEllipse(sliderRect);
    
    // 绘制时间文本
    QString currentTime = FormatTime(m_duration * m_progress / 100);
    QString totalTime = FormatTime(m_duration);
    QString timeText = currentTime + " / " + totalTime;
    
    QRect timeRect = GetTimeRect();
    painter.setPen(textColor);
    painter.setFont(QFont("Microsoft YaHei", 9));
    painter.drawText(timeRect, Qt::AlignRight | Qt::AlignVCenter, timeText);
}

void MusicProgressBar::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        if (m_clickJumpEnabled) {
            int newProgress = CalculateProgress(event->pos());
            SetProgress(newProgress);
            emit SigSliderPressed();
            m_isDragging = true;
        }
    }
    QWidget::mousePressEvent(event);
}

void MusicProgressBar::mouseMoveEvent(QMouseEvent* event)
{
    if (m_isDragging && m_clickJumpEnabled) {
        int newProgress = CalculateProgress(event->pos());
        SetProgress(newProgress);
    }
    
    // 更新时间提示
    if (m_isHovering || m_isDragging) {
        UpdateTooltipPosition(event->pos());
    }
    
    QWidget::mouseMoveEvent(event);
}

void MusicProgressBar::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && m_isDragging) {
        m_isDragging = false;
        emit SigSliderReleased();
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
    if (m_tooltipWidget) {
        m_tooltipWidget->hide();
    }
    update();
    QWidget::leaveEvent(event);
}

void MusicProgressBar::wheelEvent(QWheelEvent* event)
{
    // 支持鼠标滚轮调整进度
    int delta = event->angleDelta().y() / 120;  // 通常一步是120度
    int newProgress = m_progress + delta;
    if (newProgress < 0) newProgress = 0;
    if (newProgress > 100) newProgress = 100;
    SetProgress(newProgress);
    QWidget::wheelEvent(event);
}

void MusicProgressBar::keyPressEvent(QKeyEvent* event)
{
    // 支持方向键微调进度
    switch (event->key()) {
    case Qt::Key_Left:
    case Qt::Key_Down:
        SetProgress(m_progress - 1);
        break;
    case Qt::Key_Right:
    case Qt::Key_Up:
        SetProgress(m_progress + 1);
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void MusicProgressBar::Connectionals()
{
    // 连接定时器信号
    connect(m_tooltipTimer, &QTimer::timeout, [this]() {
        if (m_tooltipWidget) {
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
    if (m_tooltipWidget) {
        m_tooltipWidget->setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
        m_tooltipWidget->setAttribute(Qt::WA_TranslucentBackground);
        
        auto* layout = new QVBoxLayout(m_tooltipWidget);
        auto* label = new QLabel(m_tooltipWidget);
        label->setObjectName("tooltipLabel");
        label->setStyleSheet("QLabel {"
                            "  background-color: black;"
                            "  color: white;"
                            "  border-radius: 4px;"
                            "  padding: 4px;"
                            "  font-family: 'Microsoft YaHei';"
                            "  font-size: 10px;"
                            "}");
        layout->addWidget(label);
        layout->setContentsMargins(0, 0, 0, 0);
        m_tooltipWidget->setLayout(layout);
        m_tooltipWidget->hide();
    }
    
    // 设置定时器
    m_tooltipTimer->setSingleShot(true);
    m_tooltipTimer->setInterval(2000);  // 2秒后隐藏
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
    
    if (progressWidth <= 0) {
        return 0;
    }
    
    int x = pos.x() - progressRect.left();
    int progress = (x * 100) / progressWidth;
    
    if (progress < 0) progress = 0;
    if (progress > 100) progress = 100;
    
    return progress;
}

QString MusicProgressBar::FormatTime(qint64 ms) const
{
    if (ms <= 0) {
        return m_showMilliseconds ? "00:00.000" : "00:00";
    }
    
    qint64 totalSeconds = ms / 1000;
    qint64 minutes = totalSeconds / 60;
    qint64 seconds = totalSeconds % 60;
    qint64 milliseconds = ms % 1000;
    
    if (m_showMilliseconds) {
        return QString("%1:%2.%3")
            .arg(minutes, 2, 10, QLatin1Char('0'))
            .arg(seconds, 2, 10, QLatin1Char('0'))
            .arg(milliseconds, 3, 10, QLatin1Char('0'));
    } else {
        return QString("%1:%2")
            .arg(minutes, 2, 10, QLatin1Char('0'))
            .arg(seconds, 2, 10, QLatin1Char('0'));
    }
}

QRect MusicProgressBar::GetSliderRect() const
{
    QRect progressRect = GetProgressRect();
    int sliderSize = 12;
    int sliderX = progressRect.left() + (progressRect.width() * m_progress / 100) - sliderSize / 2;
    int sliderY = progressRect.center().y() - sliderSize / 2;
    
    // 确保滑块不会超出边界
    if (sliderX < progressRect.left() - sliderSize / 2) {
        sliderX = progressRect.left() - sliderSize / 2;
    }
    if (sliderX > progressRect.right() - sliderSize / 2) {
        sliderX = progressRect.right() - sliderSize / 2;
    }
    
    return QRect(sliderX, sliderY, sliderSize, sliderSize);
}

QRect MusicProgressBar::GetProgressRect() const
{
    int height = this->height();
    int progressHeight = 6;
    int progressY = (height - progressHeight) / 2;
    int margin = 80;  // 为时间显示留出空间
    
    return QRect(margin, progressY, width() - 2 * margin, progressHeight);
}

QRect MusicProgressBar::GetBufferRect() const
{
    QRect progressRect = GetProgressRect();
    return QRect(progressRect.left(), progressRect.top(), 
                progressRect.width() * m_bufferProgress / 100, progressRect.height());
}

QRect MusicProgressBar::GetTimeRect() const
{
    return QRect(0, 0, width(), height());
}

void MusicProgressBar::UpdateTooltipPosition(const QPoint& pos)
{
    if (!m_tooltipWidget) {
        return;
    }
    
    // 计算对应的时间
    int progress = CalculateProgress(pos);
    qint64 timeMs = m_duration * progress / 100;
    QString timeText = FormatTime(timeMs);
    
    // 更新提示文本
    auto* label = m_tooltipWidget->findChild<QLabel*>("tooltipLabel");
    if (label) {
        label->setText(timeText);
    }
    
    // 计算提示位置
    QPoint globalPos = mapToGlobal(pos);
    QSize tooltipSize = m_tooltipWidget->sizeHint();
    
    // 将提示框定位在鼠标上方
    QPoint tooltipPos(globalPos.x() - tooltipSize.width() / 2, 
                      globalPos.y() - tooltipSize.height() - 10);
    
    // 确保提示框不会超出屏幕边界
    QRect screenGeometry = QApplication::primaryScreen()->geometry();
    if (tooltipPos.x() < screenGeometry.left()) {
        tooltipPos.setX(screenGeometry.left());
    }
    if (tooltipPos.x() + tooltipSize.width() > screenGeometry.right()) {
        tooltipPos.setX(screenGeometry.right() - tooltipSize.width());
    }
    if (tooltipPos.y() < screenGeometry.top()) {
        tooltipPos.setY(globalPos.y() + 20);
    }
    
    m_tooltipWidget->move(tooltipPos);
    m_tooltipWidget->show();
    
    // 重启定时器
    m_tooltipTimer->start();
}