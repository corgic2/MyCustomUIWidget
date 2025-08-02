#pragma once

#include <QLabel>
#include <QPainter>
#include <QWidget>
#include "CustomFrame.h"
#include "../CommonDefine/UIWidgetColorDefine.h"
#include "../CommonDefine/UIWidgetGlobal.h"
/// <summary>
/// 自定义标签控件类，提供丰富的样式和特效设置
/// </summary>
class CustomUIGlobal_API CustomLabel : public QLabel
{
    Q_OBJECT

    // 使用MEMBER关键字让Qt Designer可以直接编辑这些属性
    Q_PROPERTY(QColor fontColor READ fontColor WRITE SetFontColor)
    Q_PROPERTY(EM_FontSize fontSize READ fontSize WRITE SetFontSize)
    Q_PROPERTY(EM_FontStyle fontStyle READ fontStyle WRITE SetFontStyle)
    Q_PROPERTY(EM_BackgroundType backgroundType READ backgroundType WRITE SetBackgroundType)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE SetBackgroundColor)
    Q_PROPERTY(bool hasShadow READ hasShadow WRITE EnableShadow)
    Q_PROPERTY(QColor shadowColor READ shadowColor WRITE SetShadowColor)
    Q_PROPERTY(bool hasBorder READ hasBorder WRITE EnableBorder)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE SetBorderColor)
    Q_PROPERTY(int borderWidth READ borderWidth WRITE SetBorderWidth)
    Q_PROPERTY(bool enableElide MEMBER m_enableElide WRITE SetEnableElide)
    Q_PROPERTY(EM_ImageScaleMode imageScaleMode READ imageScaleMode WRITE SetImageScaleMode)

public:
    /// <summary>
    /// 字体大小枚举，定义标准字体大小集
    /// </summary>
    enum EM_FontSize
    {
        FontSize_Small      = 9, /// 小号字体
        FontSize_Normal     = 12, /// 正常字体
        FontSize_Medium     = 14, /// 中等字体
        FontSize_Large      = 16, /// 大号字体
        FontSize_ExtraLarge = 20 /// 特大字体
    };

    Q_ENUM(EM_FontSize)

    /// <summary>
    /// 字体样式枚举，定义文字的显示样式
    /// </summary>
    enum EM_FontStyle
    {
        FontStyle_Normal, /// 正常样式
        FontStyle_Bold, /// 粗体
        FontStyle_Italic, /// 斜体
        FontStyle_Underline /// 下划线
    };

    Q_ENUM(EM_FontStyle)

    /// <summary>
    /// 背景类型枚举，定义标签的背景显示方式
    /// </summary>
    enum EM_BackgroundType
    {
        BackgroundType_Transparent, /// 透明背景
        BackgroundType_Solid, /// 纯色背景
        BackgroundType_Gradient /// 渐变背景
    };

    Q_ENUM(EM_BackgroundType)

    /// <summary>
    /// 图片缩放模式枚举
    /// </summary>
    enum EM_ImageScaleMode
    {
        NoScale, /// 不缩放
        ScaleToFit, /// 适应大小
        ScaleToFill, /// 填充
        ScaleKeepAspect, /// 保持比例
        ScaleToWidth,
        ScaleToHeight
    };

    Q_ENUM(EM_ImageScaleMode)

public:
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父窗口指针</param>
    explicit CustomLabel(QWidget* parent = nullptr);

    /// <summary>
    /// 析构函数
    /// </summary>
    ~CustomLabel() override;

    /// <summary>
    /// 设置字体颜色
    /// </summary>
    /// <param name="color">RGB颜色值</param>
    void SetFontColor(const QColor& color);

    /// <summary>
    /// 设置字体大小
    /// </summary>
    /// <param name="fontSize">字体大小枚举值</param>
    void SetFontSize(const EM_FontSize& fontSize);

    /// <summary>
    /// 设置字体样式
    /// </summary>
    /// <param name="fontStyle">字体样式枚举值</param>
    void SetFontStyle(const EM_FontStyle& fontStyle);

    /// <summary>
    /// 设置背景颜色
    /// </summary>
    /// <param name="color">RGBA颜色值</param>
    void SetBackgroundColor(const QColor& color);

    /// <summary>
    /// 设置背景类型
    /// </summary>
    /// <param name="type">背景类型枚举值</param>
    void SetBackgroundType(const EM_BackgroundType& type);

    /// <summary>
    /// 设置渐变背景
    /// </summary>
    /// <param name="gradientColor">渐变色结构体</param>
    void SetGradientBackground(const QColor& startColor, const QColor& endColor);

    /// <summary>
    /// 设置显示文本
    /// </summary>
    /// <param name="text">要显示的文本内容</param>
    void SetText(const QString& text);

    /// <summary>
    /// 设置对齐方式
    /// </summary>
    /// <param name="alignment">Qt对齐方式枚举值</param>
    void SetAlignment(Qt::Alignment alignment);

    /// <summary>
    /// 设置提示文本
    /// </summary>
    /// <param name="tip">提示文本内容</param>
    void SetToolTip(const QString& tip);

    /// <summary>
    /// 启用文本省略
    /// </summary>
    /// <param name="enable">是否启用</param>
    void SetEnableElide(bool enable = true);

    /// <summary>
    /// 启用边框
    /// </summary>
    /// <param name="enable">是否启用</param>
    /// <param name="color">边框颜色</param>
    /// <param name="width">边框宽度</param>
    void EnableBorder(bool enable = true, const QColor& color = UIColorDefine::border_color::Default, int width = 1);

    /// <summary>
    /// 启用阴影效果
    /// </summary>
    /// <param name="enable">是否启用</param>
    /// <param name="shadowColor">阴影颜色</param>
    void EnableShadow(bool enable = true, const QColor& shadowColor = UIColorDefine::shadow_color::Default);

    /// <summary>
    /// 设置图片
    /// </summary>
    /// <param name="imagePath">图片路径</param>
    /// <param name="scaleMode">缩放模式</param>
    void SetImage(const QString& imagePath, EM_ImageScaleMode scaleMode = ScaleToFit);

    /// <summary>
    /// 设置图片
    /// </summary>
    /// <param name="pixmap">图片对象</param>
    /// <param name="scaleMode">缩放模式</param>
    void SetImage(const QPixmap& pixmap, EM_ImageScaleMode scaleMode = ScaleToFit);

    /// <summary>
    /// 获取字体颜色
    /// </summary>
    QColor fontColor() const;

    /// <summary>
    /// 获取字体大小
    /// </summary>
    EM_FontSize fontSize() const;

    /// <summary>
    /// 获取字体样式
    /// </summary>
    EM_FontStyle fontStyle() const;

    /// <summary>
    /// 获取背景类型
    /// </summary>
    EM_BackgroundType backgroundType() const;

    /// <summary>
    /// 获取背景颜色
    /// </summary>
    QColor backgroundColor() const;

    /// <summary>
    /// 获取是否有阴影
    /// </summary>
    bool hasShadow() const;

    /// <summary>
    /// 获取阴影颜色
    /// </summary>
    QColor shadowColor() const;

    /// <summary>
    /// 设置阴影颜色
    /// </summary>
    void SetShadowColor(const QColor& color);

    /// <summary>
    /// 获取是否有边框
    /// </summary>
    bool hasBorder() const;

    /// <summary>
    /// 获取边框颜色
    /// </summary>
    QColor borderColor() const;

    /// <summary>
    /// 设置边框颜色
    /// </summary>
    void SetBorderColor(const QColor& color);

    /// <summary>
    /// 获取边框宽度
    /// </summary>
    int borderWidth() const;

    /// <summary>
    /// 设置边框宽度
    /// </summary>
    void SetBorderWidth(int width);

    /// <summary>
    /// 获取是否启用省略
    /// </summary>
    bool isElideEnabled() const;

    /// <summary>
    /// 获取图片缩放模式
    /// </summary>
    EM_ImageScaleMode imageScaleMode() const;

    /// <summary>
    /// 设置图片缩放模式
    /// </summary>
    void SetImageScaleMode(EM_ImageScaleMode mode);

    /// <summary>
    /// 设置边距
    /// </summary>
    /// <param name="left">左边距</param>
    /// <param name="top">上边距</param>
    /// <param name="right">右边距</param>
    /// <param name="bottom">下边距</param>
    void SetMargins(int left, int top, int right, int bottom);

protected:
    /// <summary>
    /// 重写大小改变事件
    /// </summary>
    void resizeEvent(QResizeEvent* event) override;
    /// <summary>
    /// 绘制事件
    /// </summary>
    /// <param name="event"></param>
    void paintEvent(QPaintEvent* event) override;

private slots:
    /// <summary>
    /// 样式变化槽函数
    /// </summary>
    void OnStyleChanged();

private:
    /// <summary>
    /// 初始化标签
    /// </summary>
    void InitializeLabel();

    /// <summary>
    /// 更新样式
    /// </summary>
    void UpdateStyle();

private:
    QString m_styleSheet; /// 样式表字符串
    QColor m_fontColor; /// 字体颜色
    EM_FontSize m_fontSize; /// 字体大小
    EM_FontStyle m_fontStyle; /// 字体样式
    EM_BackgroundType m_backgroundType; /// 背景类型
    QColor m_backgroundColor; /// 背景颜色
    QColor m_gradientStartColor; /// 渐变起始颜色
    QColor m_gradientEndColor; /// 渐变结束颜色
    bool m_hasShadow; /// 是否有阴影
    QColor m_shadowColor; /// 阴影颜色
    bool m_hasBorder; /// 是否有边框
    QColor m_borderColor; /// 边框颜色
    int m_borderWidth; /// 边框宽度
    bool m_enableElide; /// 是否启用省略
    QPixmap m_pixmap; /// 图片对象
    EM_ImageScaleMode m_imageScaleMode; /// 图片缩放模式
};

Q_DECLARE_METATYPE(CustomLabel::EM_BackgroundType)

Q_DECLARE_METATYPE(CustomLabel::EM_FontSize)

Q_DECLARE_METATYPE(CustomLabel::EM_FontStyle)

Q_DECLARE_METATYPE(CustomLabel::EM_ImageScaleMode)
