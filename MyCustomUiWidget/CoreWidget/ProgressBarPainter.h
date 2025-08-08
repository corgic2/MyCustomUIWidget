#pragma once
#include <QObject>
#include <QPainter>
#include <QRect>

class CustomProgressBar;

/// <summary>
/// 进度条绘制器基类
/// </summary>
class ProgressBarPainter : public QObject
{
    Q_OBJECT

public:
    explicit ProgressBarPainter(CustomProgressBar* progressBar, QObject* parent = nullptr);
    virtual ~ProgressBarPainter() = default;

    virtual void Paint(QPainter& painter, const QRect& rect) = 0;
    virtual QSize GetPreferredSize() const = 0;

protected:
    CustomProgressBar* m_progressBar = nullptr;
};

/// <summary>
/// 线性进度条绘制器
/// </summary>
class LinearProgressPainter : public ProgressBarPainter
{
    Q_OBJECT

public:
    explicit LinearProgressPainter(CustomProgressBar* progressBar, QObject* parent = nullptr);
    void Paint(QPainter& painter, const QRect& rect) override;
    QSize GetPreferredSize() const override;
};

/// <summary>
/// 圆形进度条绘制器
/// </summary>
class CircularProgressPainter : public ProgressBarPainter
{
    Q_OBJECT

public:
    explicit CircularProgressPainter(CustomProgressBar* progressBar, QObject* parent = nullptr);
    void Paint(QPainter& painter, const QRect& rect) override;
    QSize GetPreferredSize() const;
    QColor GetProgressColor() const;
};