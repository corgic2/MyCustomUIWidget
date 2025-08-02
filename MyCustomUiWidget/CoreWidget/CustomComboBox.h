#pragma once

#include <QComboBox>
#include <QListView>
#include "../CommonDefine/UIWidgetColorDefine.h"
#include "../CommonDefine/UIWidgetGlobal.h"

/// <summary>
/// 自定义组合框控件类，提供丰富的样式设置
/// </summary>
class CustomUIGlobal_API CustomComboBox : public QComboBox
{
    Q_OBJECT

    // 使用QColor类型替代自定义颜色类型，使Qt Designer能够识别和编辑
    Q_PROPERTY(QColor fontColor READ fontColor WRITE SetFontColor)
    Q_PROPERTY(EM_FontSize fontSize READ fontSize WRITE SetFontSize)
    Q_PROPERTY(EM_FontStyle fontStyle READ fontStyle WRITE SetFontStyle)
    Q_PROPERTY(EM_BackgroundType backgroundType READ backgroundType WRITE SetBackgroundType)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE SetBackgroundColor)
    Q_PROPERTY(QColor itemFontColor READ itemFontColor WRITE SetItemFontColor)
    Q_PROPERTY(QColor itemBackgroundColor READ itemBackgroundColor WRITE SetItemBackgroundColor)
    Q_PROPERTY(int itemSpacing READ itemSpacing WRITE SetItemSpacing)
    Q_PROPERTY(int itemHeight READ itemHeight WRITE SetItemHeight)

public:
    /// <summary>
    /// 字体大小枚举，定义标准字体大小集
    /// </summary>
    enum EM_FontSize
    {
        FontSize_Small      = 9,  /// 小号字体
        FontSize_Normal     = 12, /// 正常字体
        FontSize_Medium     = 14, /// 中等字体
        FontSize_Large      = 16, /// 大号字体
        FontSize_ExtraLarge = 20  /// 特大字体
    };
    Q_ENUM(EM_FontSize)

    /// <summary>
    /// 字体样式枚举，定义文字的显示样式
    /// </summary>
    enum EM_FontStyle
    {
        FontStyle_Normal,    /// 正常样式
        FontStyle_Bold,      /// 粗体
        FontStyle_Italic,    /// 斜体
        FontStyle_Underline  /// 下划线
    };
    Q_ENUM(EM_FontStyle)

    /// <summary>
    /// 背景类型枚举，定义背景显示方式
    /// </summary>
    enum EM_BackgroundType
    {
        BackgroundType_Transparent, /// 透明背景
        BackgroundType_Solid,      /// 纯色背景
        BackgroundType_Gradient    /// 渐变背景
    };
    Q_ENUM(EM_BackgroundType)

public:
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父窗口指针</param>
    explicit CustomComboBox(QWidget* parent = nullptr);

    /// <summary>
    /// 析构函数
    /// </summary>
    ~CustomComboBox();

    // Getters
    QColor fontColor() const { return m_fontColor; }
    QColor backgroundColor() const { return m_backgroundColor; }
    QColor itemFontColor() const { return m_itemFontColor; }
    QColor itemBackgroundColor() const { return m_itemBackgroundColor; }
    EM_FontSize fontSize() const { return m_fontSize; }
    EM_FontStyle fontStyle() const { return m_fontStyle; }
    EM_BackgroundType backgroundType() const { return m_backgroundType; }
    int itemSpacing() const { return m_itemSpacing; }
    int itemHeight() const { return m_itemHeight; }

    // Setters
    void SetFontColor(const QColor& color);
    void SetBackgroundColor(const QColor& color);
    void SetItemFontColor(const QColor& color);
    void SetItemBackgroundColor(const QColor& color);
    void SetFontSize(const EM_FontSize& fontSize);
    void SetFontStyle(const EM_FontStyle& fontStyle);
    void SetBackgroundType(const EM_BackgroundType& type);
    void SetGradientBackground(const UIColorDefine::ST_GradientColor& gradientColor);
    void SetItemSpacing(int spacing);
    void SetItemHeight(int height);

    /// <summary>
    /// 设置边距
    /// </summary>
    /// <param name="left">左边距</param>
    /// <param name="top">上边距</param>
    /// <param name="right">右边距</param>
    /// <param name="bottom">下边距</param>
    void SetMargins(int left, int top, int right, int bottom);

    /// <summary>
    /// 设置边框宽度
    /// </summary>
    /// <param name="width">边框宽度</param>
    void SetBorderWidth(int width);

    /// <summary>
    /// 设置边框颜色
    /// </summary>
    /// <param name="color">边框颜色</param>
    void SetBorderColor(const QColor& color);

protected:
    void paintEvent(QPaintEvent* event) override;
private slots:
    /// <summary>
    /// 样式变化槽函数
    /// </summary>
    void OnStyleChanged();

private:
    /// <summary>
    /// 初始化组合框
    /// </summary>
    void InitializeComboBox();

    /// <summary>
    /// 更新样式
    /// </summary>
    void UpdateStyle();

private:
    QColor m_fontColor;            /// 字体颜色
    EM_FontSize m_fontSize;        /// 字体大小
    EM_FontStyle m_fontStyle;      /// 字体样式
    EM_BackgroundType m_backgroundType; /// 背景类型
    QColor m_backgroundColor;      /// 背景颜色
    QColor m_itemFontColor;        /// 项目字体颜色
    QColor m_itemBackgroundColor;  /// 项目背景颜色
    int m_itemSpacing;            /// 项目间距
    int m_itemHeight;             /// 项目高度
    UIColorDefine::ST_GradientColor m_gradientColor; /// 渐变颜色
    int m_borderWidth;         /// 边框宽度
    QColor m_borderColor;      /// 边框颜色
};
