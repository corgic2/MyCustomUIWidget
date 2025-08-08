#include "ProgressBarPainter.h"
#include "CustomProgressBar.h"
#include <QStyleOptionProgressBar>
#include <QStyle>
#include "StyleSystem/SkinManager.h"

ProgressBarPainter::ProgressBarPainter(CustomProgressBar* progressBar, QObject* parent)
    : QObject(parent)
    , m_progressBar(progressBar)
{
}

LinearProgressPainter::LinearProgressPainter(CustomProgressBar* progressBar, QObject* parent)
    : ProgressBarPainter(progressBar, parent)
{
}

void LinearProgressPainter::Paint(QPainter& painter, const QRect& rect)
{
    painter.setRenderHint(QPainter::Antialiasing);
    
    // 使用蓝绿色主题
    QColor backgroundColor = SkinManager::instance()->parseColorSheet("@info_color");
    QColor progressColor = SkinManager::instance()->parseColorSheet("@success_color");
    
    // 绘制背景
    painter.setBrush(backgroundColor);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect, 4, 4);
    
    // 计算进度条宽度
    int progressWidth = rect.width() * m_progressBar->GetAnimatedValue() / m_progressBar->maximum();
    if (progressWidth > 0) {
        QRect progressRect(rect.x(), rect.y(), progressWidth, rect.height());
        painter.setBrush(progressColor);
        painter.drawRoundedRect(progressRect, 4, 4);
    }
    
    // 绘制百分比文本
    if (m_progressBar->isTextVisible()) {
        QString text = QString("%1%").arg(m_progressBar->GetAnimatedValue());
        painter.setPen(SkinManager::instance()->parseColorSheet("@dark_color"));
        
        QFont font = painter.font();
        font.setPixelSize(12);
        font.setBold(true);
        painter.setFont(font);
        
        painter.drawText(rect, Qt::AlignCenter, text);
    }
}

QSize LinearProgressPainter::GetPreferredSize() const
{
    return QSize(200, 25);
}

CircularProgressPainter::CircularProgressPainter(CustomProgressBar* progressBar, QObject* parent)
    : ProgressBarPainter(progressBar, parent)
{
}

void CircularProgressPainter::Paint(QPainter& painter, const QRect& rect)
{
    painter.setRenderHint(QPainter::Antialiasing);
    
    // 确保圆环完全居中
    int size = qMin(rect.width(), rect.height());
    int centerX = rect.center().x();
    int centerY = rect.center().y();
    int radius = size / 2 - 10;
    
    // 调整绘制区域确保居中
    QRectF arcRect(centerX - radius, centerY - radius, radius * 2, radius * 2);
    
    // 使用蓝绿色主题
    QColor backgroundColor = SkinManager::instance()->parseColorSheet("@info_color");
    QColor progressColor = SkinManager::instance()->parseColorSheet("@success_color");
    
    // 背景圆环
    painter.setPen(QPen(backgroundColor, 8));
    painter.drawEllipse(arcRect);
    
    // 进度圆环
    qreal progressAngle = 360.0 * m_progressBar->GetAnimatedValue() / m_progressBar->maximum();
    
    QColor activeProgressColor = GetProgressColor();
    painter.setPen(QPen(activeProgressColor, 8));
    painter.drawArc(arcRect, 90 * 16, -progressAngle * 16);
    
    // 中心文本
    QFont font = painter.font();
    font.setPixelSize(12);
    font.setBold(true);
    painter.setFont(font);
    
    QString text = QString("%1%").arg(m_progressBar->GetAnimatedValue());
    painter.setPen(SkinManager::instance()->parseColorSheet("@dark_color"));
    painter.drawText(arcRect, Qt::AlignCenter, text);
}

QSize CircularProgressPainter::GetPreferredSize() const
{
    return QSize(100, 100);
}

QColor CircularProgressPainter::GetProgressColor() const
{
    switch (m_progressBar->GetProgressState()) {
    case EM_ProgressState::EM_PROGRESS_SUCCESS:
        return SkinManager::instance()->parseColorSheet("@success_color");
    case EM_ProgressState::EM_PROGRESS_WARNING:
        return SkinManager::instance()->parseColorSheet("@error_color");
    case EM_ProgressState::EM_PROGRESS_ERROR:
        return SkinManager::instance()->parseColorSheet("@error_color");
    default:
        return SkinManager::instance()->parseColorSheet("@progress_blue_green");
    }
}