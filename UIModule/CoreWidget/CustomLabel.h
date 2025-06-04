#pragma once

#include <QLabel>
#include <QWidget>
#include "ui_CustomLabel.h"
#include "UIWidgetColorDefine.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CustomLabelClass; };
QT_END_NAMESPACE

/// <summary>
/// 自定义标签控件类，提供丰富的样式和特效设置
/// </summary>
class CustomLabel : public QLabel
{
    Q_OBJECT

public:
    /// <summary>
    /// 字体大小枚举，定义标准字体大小集
    /// </summary>
    enum EM_FontSize
    {
        FontSize_Small      = 9,    /// 小号字体
        FontSize_Normal     = 12,   /// 正常字体
        FontSize_Medium     = 14,   /// 中等字体
        FontSize_Large      = 16,   /// 大号字体
        FontSize_ExtraLarge = 20    /// 特大字体
    };

    /// <summary>
    /// 字体样式枚举，定义文字的显示样式
    /// </summary>
    enum EM_FontStyle
    {
        FontStyle_Normal,      /// 正常样式
        FontStyle_Bold,        /// 粗体
        FontStyle_Italic,      /// 斜体
        FontStyle_Underline    /// 下划线
    };

    /// <summary>
    /// 背景类型枚举，定义标签的背景显示方式
    /// </summary>
    enum EM_BackgroundType
    {
        BackgroundType_Transparent,  /// 透明背景
        BackgroundType_Solid,        /// 纯色背景
        BackgroundType_Gradient      /// 渐变背景
    };
    /// <summary>
    /// 图片缩放模式枚举
    /// </summary>
    enum EM_ImageScaleMode
    {
        NoScale,            /// 不缩放
        ScaleToFit,        /// 适应大小
        ScaleToFill,       /// 填充
        ScaleKeepAspect    /// 保持比例
    };

public:
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父窗口指针</param>
    CustomLabel(QWidget *parent = nullptr);

    /// <summary>
    /// 析构函数
    /// </summary>
    ~CustomLabel();

    /// <summary>
    /// 设置字体颜色
    /// </summary>
    /// <param name="color">RGB颜色值</param>
    void SetFontColor(const UIColorDefine::ST_ColorRgb& color);

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
    void SetBackgroundColor(const UIColorDefine::ST_ColorRgba& color);

    /// <summary>
    /// 设置背景类型
    /// </summary>
    /// <param name="type">背景类型枚举值</param>
    void SetBackgroundType(const EM_BackgroundType& type);

    /// <summary>
    /// 设置渐变背景
    /// </summary>
    /// <param name="gradientColor">渐变色结构体</param>
    void SetGradientBackground(const UIColorDefine::ST_GradientColor& gradientColor);

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
    void EnableElide(bool enable = true);

    /// <summary>
    /// 启用边框
    /// </summary>
    /// <param name="enable">是否启用</param>
    /// <param name="color">边框颜色</param>
    /// <param name="width">边框宽度</param>
    void EnableBorder(bool enable = true, const UIColorDefine::ST_ColorRgb& color = UIColorDefine::border_color::Default, int width = 1);

    /// <summary>
    /// 启用阴影效果
    /// </summary>
    /// <param name="enable">是否启用</param>
    /// <param name="shadowColor">阴影颜色</param>
    void EnableShadow(bool enable = true, const UIColorDefine::ST_ColorRgba& shadowColor = UIColorDefine::shadow_color::Default);

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

protected:
    /// <summary>
    /// 重写大小改变事件
    /// </summary>
    void resizeEvent(QResizeEvent* event) override;

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
    Ui::CustomLabelClass* m_ui;           /// UI对象指针
    QString m_styleSheet;                  /// 样式表字符串

    UIColorDefine::ST_ColorRgb m_fontColor;        /// 字体颜色
    EM_FontSize m_fontSize;                        /// 字体大小
    EM_FontStyle m_fontStyle;                      /// 字体样式
    EM_BackgroundType m_backgroundType;            /// 背景类型
    UIColorDefine::ST_ColorRgba m_backgroundColor; /// 背景颜色
    UIColorDefine::ST_GradientColor m_gradientColor; /// 渐变色
    bool m_hasShadow;                             /// 是否有阴影
    UIColorDefine::ST_ColorRgba m_shadowColor;    /// 阴影颜色
    bool m_hasBorder;                             /// 是否有边框
    UIColorDefine::ST_ColorRgb m_borderColor;     /// 边框颜色
    int m_borderWidth;                            /// 边框宽度
    bool m_enableElide;                           /// 是否启用省略
    QPixmap m_pixmap;                  /// 图片对象
    EM_ImageScaleMode m_imageScaleMode;/// 图片缩放模式
};

