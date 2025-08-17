#pragma once
#include <QWidget>
#include <QTimer>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include "../CommonDefine/UIWidgetGlobal.h"
#include "../CommonDefine/BaseDefine/BaseStyleWidgetInterface.h"

/// <summary>
/// 音乐播放进度条控件类，支持点击/拖动调整进度，显示缓冲进度和时间提示
/// </summary>
class CustomUIGlobal_API MusicProgressBar : public QWidget, public BaseStyleWidgetInterface
{
    Q_OBJECT
    Q_PROPERTY(qint64 position READ GetPosition WRITE SetPosition NOTIFY SigPositionChanged)
    Q_PROPERTY(qint64 bufferPosition READ GetBufferPosition WRITE SetBufferPosition)
    Q_PROPERTY(qint64 duration READ GetDuration WRITE SetDuration)
    Q_PROPERTY(bool clickJumpEnabled READ IsClickJumpEnabled WRITE EnableClickJump)
    Q_PROPERTY(bool showMilliseconds READ IsShowMilliseconds WRITE SetTimeFormat)

public:
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父窗口指针</param>
    explicit MusicProgressBar(QWidget* parent = nullptr);

    /// <summary>
    /// 析构函数
    /// </summary>
    ~MusicProgressBar() override;

    /// <summary>
    /// 获取当前位置（毫秒）
    /// </summary>
    qint64 GetPosition() const { return m_position; }

    /// <summary>
    /// 获取缓冲位置（毫秒）
    /// </summary>
    qint64 GetBufferPosition() const { return m_bufferPosition; }

    /// <summary>
    /// 获取总时长（毫秒）
    /// </summary>
    qint64 GetDuration() const { return m_duration; }

    /// <summary>
    /// 是否启用点击跳转功能
    /// </summary>
    bool IsClickJumpEnabled() const { return m_clickJumpEnabled; }

    /// <summary>
    /// 是否显示毫秒
    /// </summary>
    bool IsShowMilliseconds() const { return m_showMilliseconds; }

    /// <summary>
    /// 设置是否显示毫秒
    /// </summary>
    void SetTimeFormat(bool showMS);

public slots:
    /// <summary>
    /// 设置当前位置（毫秒）
    /// </summary>
    /// <param name="position">位置值（毫秒）</param>
    void SetPosition(qint64 position);

    /// <summary>
    /// 设置缓冲位置（毫秒）
    /// </summary>
    /// <param name="position">缓冲位置值（毫秒）</param>
    void SetBufferPosition(qint64 position);

    /// <summary>
    /// 设置总时长（毫秒）
    /// </summary>
    /// <param name="ms">总时长</param>
    void SetDuration(qint64 ms);

    /// <summary>
    /// 启用/禁用点击跳转功能
    /// </summary>
    /// <param name="enable">是否启用</param>
    void EnableClickJump(bool enable);

signals:
    /// <summary>
    /// 位置改变信号
    /// </summary>
    /// <param name="position">新的位置值（毫秒）</param>
    void SigPositionChanged(qint64 position);

    /// <summary>
    /// 寻求位置信号
    /// </summary>
    /// <param name="position">寻求的位置值（毫秒）</param>
    void SigSeekRequested(qint64 position);

    /// <summary>
    /// 开始交互信号
    /// </summary>
    void SigSliderPressed();

    /// <summary>
    /// 结束交互信号
    /// </summary>
    void SigSliderReleased();

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

    /// <summary>
    /// 信号槽连接
    /// </summary>
    void Connectionals() override;

    /// <summary>
    /// 初始化
    /// </summary>
    void Initilize() override;

    /// <summary>
    /// 基类函数修改样式
    /// </summary>
    void ApplyFormatStyle() override;

private:
    /// <summary>
    /// 计算进度百分比（根据鼠标位置）
    /// </summary>
    /// <param name="pos">鼠标位置</param>
    /// <returns>进度百分比（0-100）</returns>
    int CalculateProgress(const QPoint& pos) const;

    /// <summary>
    /// 格式化时间显示
    /// </summary>
    /// <param name="ms">毫秒数</param>
    /// <returns>格式化后的时间字符串</returns>
    QString FormatTime(qint64 ms) const;

    /// <summary>
    /// 获取滑块矩形区域
    /// </summary>
    /// <returns>滑块矩形</returns>
    QRect GetSliderRect() const;

    /// <summary>
    /// 获取进度条矩形区域
    /// </summary>
    /// <returns>进度条矩形</returns>
    QRect GetProgressRect() const;

    /// <summary>
    /// 获取缓冲进度条矩形区域
    /// </summary>
    /// <returns>缓冲进度条矩形</returns>
    QRect GetBufferRect() const;

    /// <summary>
    /// 获取时间显示矩形区域
    /// </summary>
    /// <returns>时间显示矩形</returns>
    QRect GetTimeRect() const;

    /// <summary>
    /// 更新时间提示位置
    /// </summary>
    /// <param name="pos">鼠标位置</param>
    void UpdateTooltipPosition(const QPoint& pos);

private:
    qint64 m_position = 0;              ///< 当前位置（毫秒）
    qint64 m_bufferPosition = 0;        ///< 缓冲位置（毫秒）
    qint64 m_duration = 0;           ///< 总时长（毫秒）
    bool m_clickJumpEnabled = true;  ///< 是否启用点击跳转
    bool m_showMilliseconds = false; ///< 是否显示毫秒
    bool m_isDragging = false;       ///< 是否正在拖动
    bool m_isHovering = false;       ///< 是否悬停
    QPoint m_lastMousePos;           ///< 上次鼠标位置
    QTimer* m_tooltipTimer = nullptr;///< 时间提示定时器
    QWidget* m_tooltipWidget = nullptr; ///< 时间提示控件
};