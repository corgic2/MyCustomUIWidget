#pragma once

#include <QProgressBar>
#include <QPropertyAnimation>
#include <QTimer>
#include <QWidget>
#include "../CommonDefine/UIWidgetColorDefine.h"
#include "../CommonDefine/UIWidgetGlobal.h"

/// <summary>
/// 进度条状态枚举
/// </summary>
enum class EM_ProgressState {
    EM_PROGRESS_NORMAL = 0,
    EM_PROGRESS_SUCCESS,
    EM_PROGRESS_WARNING,
    EM_PROGRESS_ERROR
};

/// <summary>
/// 进度条动画配置结构体
/// </summary>
struct ST_AnimationConfig {
    bool m_enableAnimation = true;
    int m_animationDuration = 500;
    QEasingCurve::Type m_easingType = QEasingCurve::OutCubic;
};

/// <summary>
/// 自定义进度条控件类，提供丰富的样式和动画效果
/// </summary>
class CustomUIGlobal_API CustomProgressBar : public QProgressBar
{
    Q_OBJECT
    Q_PROPERTY(int animatedValue READ GetAnimatedValue WRITE SetAnimatedValue)
    Q_PROPERTY(EM_ProgressState progressState READ GetProgressState WRITE SetProgressState)
    Q_PROPERTY(bool circular READ GetCircular WRITE SetCircular)

public:
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父窗口指针</param>
    explicit CustomProgressBar(QWidget* parent = nullptr);

    /// <summary>
    /// 析构函数
    /// </summary>
    ~CustomProgressBar() override;

    /// <summary>
    /// 设置进度值（带动画效果）
    /// </summary>
    /// <param name="value">进度值（0-100）</param>
    void SetProgressValue(int value);

    /// <summary>
    /// 获取当前动画值
    /// </summary>
    /// <returns>当前动画值</returns>
    int GetAnimatedValue() const;

    /// <summary>
    /// 设置动画值（内部使用）
    /// </summary>
    /// <param name="value">动画值</param>
    void SetAnimatedValue(int value);

    /// <summary>
    /// 设置进度条状态
    /// </summary>
    /// <param name="state">进度条状态</param>
    void SetProgressState(EM_ProgressState state);

    /// <summary>
    /// 获取进度条状态
    /// </summary>
    /// <returns>当前状态</returns>
    EM_ProgressState GetProgressState() const;

    /// <summary>
    /// 设置是否为圆环进度条
    /// </summary>
    /// <param name="circular">是否为圆环</param>
    void SetCircular(bool circular);

    /// <summary>
    /// 获取是否为圆环进度条
    /// </summary>
    /// <returns>是否为圆环</returns>
    bool GetCircular() const;

    /// <summary>
    /// 设置动画配置
    /// </summary>
    /// <param name="config">动画配置</param>
    void SetAnimationConfig(const ST_AnimationConfig& config);

    /// <summary>
    /// 获取动画配置
    /// </summary>
    /// <returns>当前动画配置</returns>
    ST_AnimationConfig GetAnimationConfig() const;

    /// <summary>
    /// 启用/禁用动画效果
    /// </summary>
    /// <param name="enabled">是否启用</param>
    void SetAnimationEnabled(bool enabled);

    /// <summary>
    /// 立即完成动画（无动画效果）
    /// </summary>
    /// <param name="value">目标值</param>
    void SetValueImmediately(int value);

signals:
    /// <summary>
    /// 进度值改变信号
    /// </summary>
    /// <param name="value">新的进度值</param>
    void SigProgressValueChanged(int value);

    /// <summary>
    /// 动画完成信号
    /// </summary>
    void SigAnimationFinished();

    /// <summary>
    /// 状态改变信号
    /// </summary>
    /// <param name="state">新的状态</param>
    void SigProgressStateChanged(EM_ProgressState state);

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void SlotOnAnimationFinished();

private:
    void InitializeAnimation();
    void UpdateProgressStyle();
    void DrawLinearProgress(QPainter& painter, const QRect& rect);
    void DrawCircularProgress(QPainter& painter, const QRect& rect);

private:
    int m_animatedValue = 0;
    int m_targetValue = 0;
    EM_ProgressState m_progressState = EM_ProgressState::EM_PROGRESS_NORMAL;
    bool m_circular = false;
    bool m_animationEnabled = true;
    ST_AnimationConfig m_animationConfig;
    QPropertyAnimation* m_progressAnimation = nullptr;
    QTimer* m_pulseTimer = nullptr;
    int m_pulseValue = 0;
};
