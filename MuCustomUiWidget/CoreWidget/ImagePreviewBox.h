#pragma once

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QPainterPath>
#include <QMimeData>
#include "../CommonDefine/UIWidgetGlobal.h"
#include "../CommonDefine/UIWidgetColorDefine.h"

/// <summary>
/// 图片预览框控件
/// </summary>
class CustomUIGlobal_API ImagePreviewBox : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString imagePath READ GetImagePath WRITE SetImagePath NOTIFY SigImageChanged)
    Q_PROPERTY(EM_ScaleMode scaleMode READ GetScaleMode WRITE SetScaleMode)
    Q_PROPERTY(bool enableDragDrop READ IsDragDropEnabled WRITE SetEnableDragDrop)
    Q_PROPERTY(bool showCropHint READ IsShowCropHint WRITE SetShowCropHint)
    Q_PROPERTY(QSize cropSize READ GetCropSize WRITE SetCropSize)
    Q_PROPERTY(QColor borderColor READ GetBorderColor WRITE SetBorderColor)
    Q_PROPERTY(int borderWidth READ GetBorderWidth WRITE SetBorderWidth)
    Q_PROPERTY(QString placeholderText READ GetPlaceholderText WRITE SetPlaceholderText)

public:
    /// <summary>
    /// 缩放模式枚举
    /// </summary>
    enum EM_ScaleMode
    {
        NoScale,            /// 不缩放
        ScaleToFit,        /// 适应大小
        ScaleToFill,       /// 填充
        ScaleKeepAspect    /// 保持比例
    };
    Q_ENUM(EM_ScaleMode)

public:
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父窗口指针</param>
    explicit ImagePreviewBox(QWidget* parent = nullptr);

    /// <summary>
    /// 析构函数
    /// </summary>
    ~ImagePreviewBox();

    /// <summary>
    /// 设置图片路径
    /// </summary>
    /// <param name="path">图片路径</param>
    void SetImagePath(const QString& path);

    /// <summary>
    /// 设置图片数据
    /// </summary>
    /// <param name="pixmap">图片数据</param>
    void SetImage(const QPixmap& pixmap);

    /// <summary>
    /// 设置缩放模式
    /// </summary>
    /// <param name="mode">缩放模式</param>
    void SetScaleMode(EM_ScaleMode mode);

    /// <summary>
    /// 设置是否启用拖拽
    /// </summary>
    /// <param name="enable">是否启用</param>
    void SetEnableDragDrop(bool enable);

    /// <summary>
    /// 设置是否显示裁剪提示
    /// </summary>
    /// <param name="show">是否显示</param>
    void SetShowCropHint(bool show);

    /// <summary>
    /// 设置裁剪尺寸
    /// </summary>
    /// <param name="size">裁剪尺寸</param>
    void SetCropSize(const QSize& size);

    /// <summary>
    /// 设置边框颜色
    /// </summary>
    /// <param name="color">边框颜色</param>
    void SetBorderColor(const QColor& color);

    /// <summary>
    /// 设置边框宽度
    /// </summary>
    /// <param name="width">边框宽度</param>
    void SetBorderWidth(int width);

    /// <summary>
    /// 设置占位文本
    /// </summary>
    /// <param name="text">占位文本</param>
    void SetPlaceholderText(const QString& text);

    // Getters
    QString GetImagePath() const { return m_imagePath; }
    EM_ScaleMode GetScaleMode() const { return m_scaleMode; }
    bool IsDragDropEnabled() const { return m_enableDragDrop; }
    bool IsShowCropHint() const { return m_showCropHint; }
    QSize GetCropSize() const { return m_cropSize; }
    QColor GetBorderColor() const { return m_borderColor; }
    int GetBorderWidth() const { return m_borderWidth; }
    QString GetPlaceholderText() const { return m_placeholderText; }

signals:
    /// <summary>
    /// 图片改变信号
    /// </summary>
    /// <param name="path">新的图片路径</param>
    void SigImageChanged(const QString& path);

protected:
    /// <summary>
    /// 拖拽进入事件
    /// </summary>
    void dragEnterEvent(QDragEnterEvent* event) override;

    /// <summary>
    /// 拖拽放下事件
    /// </summary>
    void dropEvent(QDropEvent* event) override;

    /// <summary>
    /// 绘制事件
    /// </summary>
    void paintEvent(QPaintEvent* event) override;

    /// <summary>
    /// 大小改变事件
    /// </summary>
    void resizeEvent(QResizeEvent* event) override;

private:
    /// <summary>
    /// 初始化控件
    /// </summary>
    void Initialize();

    /// <summary>
    /// 更新图片显示
    /// </summary>
    void UpdateImage();

    /// <summary>
    /// 绘制裁剪提示
    /// </summary>
    /// <param name="painter">画笔</param>
    void DrawCropHint(QPainter& painter);

private:
    QString m_imagePath;           /// 图片路径
    QPixmap m_originalPixmap;      /// 原始图片
    QPixmap m_scaledPixmap;        /// 缩放后的图片
    EM_ScaleMode m_scaleMode;      /// 缩放模式
    bool m_enableDragDrop;         /// 是否启用拖拽
    bool m_showCropHint;           /// 是否显示裁剪提示
    QSize m_cropSize;              /// 裁剪尺寸
    QColor m_borderColor;          /// 边框颜色
    int m_borderWidth;             /// 边框宽度
    QString m_placeholderText;     /// 占位文本
}; 