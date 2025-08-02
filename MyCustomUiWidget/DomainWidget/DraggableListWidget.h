#pragma once

#include <QListWidget>
#include "../CommonDefine/UIWidgetGlobal.h"
#include "../CommonDefine/UIWidgetColorDefine.h"

/// <summary>
/// 可拖拽排序列表控件
/// </summary>
class CustomUIGlobal_API DraggableListWidget : public QListWidget
{
    Q_OBJECT
    Q_PROPERTY(bool dragEnabled READ isDragEnabled WRITE SetDragEnabled)
    Q_PROPERTY(bool dropIndicatorVisible READ isDropIndicatorVisible WRITE SetDropIndicatorVisible)
    Q_PROPERTY(QColor dropIndicatorColor READ GetDropIndicatorColor WRITE SetDropIndicatorColor)
    Q_PROPERTY(int dropIndicatorWidth READ GetDropIndicatorWidth WRITE SetDropIndicatorWidth)
    Q_PROPERTY(bool alternatingRowColors READ alternatingRowColors WRITE setAlternatingRowColors)

public:
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父窗口指针</param>
    explicit DraggableListWidget(QWidget* parent = nullptr);

    /// <summary>
    /// 析构函数
    /// </summary>
    ~DraggableListWidget();

    /// <summary>
    /// 设置是否启用拖拽
    /// </summary>
    /// <param name="enable">是否启用</param>
    void SetDragEnabled(bool enable);

    /// <summary>
    /// 设置是否显示放置指示器
    /// </summary>
    /// <param name="visible">是否显示</param>
    void SetDropIndicatorVisible(bool visible);

    /// <summary>
    /// 设置放置指示器颜色
    /// </summary>
    /// <param name="color">指示器颜色</param>
    void SetDropIndicatorColor(const QColor& color);

    /// <summary>
    /// 设置放置指示器宽度
    /// </summary>
    /// <param name="width">指示器宽度</param>
    void SetDropIndicatorWidth(int width);

    // Getters
    bool isDragEnabled() const { return m_dragEnabled; }
    bool isDropIndicatorVisible() const { return m_dropIndicatorVisible; }
    QColor GetDropIndicatorColor() const { return m_dropIndicatorColor; }
    int GetDropIndicatorWidth() const { return m_dropIndicatorWidth; }

signals:
    /// <summary>
    /// 项目顺序改变信号
    /// </summary>
    void SigOrderChanged();

protected:
    /// <summary>
    /// 拖拽进入事件
    /// </summary>
    void dragEnterEvent(QDragEnterEvent* event) override;

    /// <summary>
    /// 拖拽移动事件
    /// </summary>
    void dragMoveEvent(QDragMoveEvent* event) override;

    /// <summary>
    /// 放置事件
    /// </summary>
    void dropEvent(QDropEvent* event) override;

    /// <summary>
    /// 绘制事件
    /// </summary>
    void paintEvent(QPaintEvent* event) override;

private:
    /// <summary>
    /// 初始化控件
    /// </summary>
    void Initialize();

    /// <summary>
    /// 绘制放置指示器
    /// </summary>
    void DrawDropIndicator(QPainter& painter, const QPoint& pos);

private:
    bool m_dragEnabled;           /// 是否启用拖拽
    bool m_dropIndicatorVisible;  /// 是否显示放置指示器
    QColor m_dropIndicatorColor;  /// 放置指示器颜色
    int m_dropIndicatorWidth;     /// 放置指示器宽度
    QPoint m_dropIndicatorPos;    /// 放置指示器位置
}; 