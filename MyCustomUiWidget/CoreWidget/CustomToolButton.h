#pragma once

#include <QtWidgets/QToolButton>
#include "../CommonDefine/UIWidgetColorDefine.h"
#include "../CommonDefine/UIWidgetGlobal.h"
#include "../UtilsWidget/CustomToolTips.h"
/// <summary>
/// 自定义工具按钮类，提供丰富的样式设置和提示功能
/// </summary>
class CustomUIGlobal_API CustomToolButton : public QToolButton
{
    Q_OBJECT

    // 使用QColor类型替代自定义颜色类型，使Qt Designer能够识别和编辑
    Q_PROPERTY(QString toolTipsText READ toolTipsText WRITE SetToolTipsText)
    Q_PROPERTY(QString toolTipsExText READ toolTipsExText WRITE SetToolTipsExText)
    Q_PROPERTY(CustomToolTips::EM_TipsType tipsType READ tipsType WRITE SetTipsType)
    Q_PROPERTY(QColor fontColor READ fontColor WRITE SetFontColor)
    Q_PROPERTY(int fontSize READ fontSize WRITE SetFontSize)
    Q_PROPERTY(EM_FontStyle fontStyle READ fontStyle WRITE SetFontStyle)
    Q_PROPERTY(EM_BackgroundType backgroundType READ backgroundType WRITE SetBackgroundType)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE SetBackgroundColor)
    Q_PROPERTY(int padding READ padding WRITE SetPadding)

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
    /// 背景类型枚举，定义背景显示方式
    /// </summary>
    enum EM_BackgroundType
    {
        BackgroundType_Transparent, /// 透明背景
        BackgroundType_Solid, /// 纯色背景
        BackgroundType_Gradient /// 渐变背景
    };

    Q_ENUM(EM_BackgroundType)

public:
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父窗口指针</param>
    explicit CustomToolButton(QWidget* parent = nullptr);

    /// <summary>
    /// 析构函数
    /// </summary>
    ~CustomToolButton();

    /// <summary>
    /// 设置提示文本
    /// </summary>
    /// <param name="text">提示文本内容</param>
    void SetToolTipsText(const QString& text);

    /// <summary>
    /// 获取提示文本
    /// </summary>
    QString toolTipsText() const;

    /// <summary>
    /// 设置扩展提示文本
    /// </summary>
    /// <param name="text">扩展提示文本内容</param>
    void SetToolTipsExText(const QString& text);

    /// <summary>
    /// 获取扩展提示文本
    /// </summary>
    QString toolTipsExText() const;

    /// <summary>
    /// 设置提示类型
    /// </summary>
    /// <param name="type">提示类型枚举值</param>
    void SetTipsType(CustomToolTips::EM_TipsType type);

    /// <summary>
    /// 设置字体颜色
    /// </summary>
    /// <param name="color"></param>
    void SetFontColor(const QColor& color);

    /// <summary>
    /// 获取提示类型
    /// </summary>
    CustomToolTips::EM_TipsType tipsType() const;

    /// <summary>
    /// 获取字体颜色
    /// </summary>
    QColor fontColor() const;

    /// <summary>
    /// 设置字体大小
    /// </summary>
    /// <param name="size">字体大小</param>
    void SetFontSize(int size);

    /// <summary>
    /// 获取字体大小
    /// </summary>
    int fontSize() const;

    /// <summary>
    /// 设置字体样式
    /// </summary>
    /// <param name="style">字体样式枚举值</param>
    void SetFontStyle(const EM_FontStyle& style);

    /// <summary>
    /// 设置背景颜色
    /// </summary>
    /// <param name="color"></param>
    void SetBackgroundColor(const QColor& color);

    /// <summary>
    /// 获取字体样式
    /// </summary>
    EM_FontStyle fontStyle() const;

    /// <summary>
    /// 获取背景颜色
    /// </summary>
    QColor backgroundColor() const;

    /// <summary>
    /// 设置背景类型
    /// </summary>
    /// <param name="type">背景类型枚举值</param>
    void SetBackgroundType(const EM_BackgroundType& type);

    /// <summary>
    /// 获取背景类型
    /// </summary>
    EM_BackgroundType backgroundType() const;

    /// <summary>
    /// 设置渐变背景
    /// </summary>
    /// <param name="startColor">渐变起始颜色</param>
    /// <param name="endColor">渐变结束颜色</param>
    void SetGradientBackground(const QColor& startColor, const QColor& endColor);

    /// <summary>
    /// 设置内边距
    /// </summary>
    /// <param name="padding">内边距大小（像素）</param>
    void SetPadding(int padding);

    /// <summary>
    /// 获取内边距
    /// </summary>
    int padding() const;

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
    /// <summary>
    /// 进入事件
    /// </summary>
    void enterEvent(QEvent* event) override;

    /// <summary>
    /// 离开事件
    /// </summary>
    void leaveEvent(QEvent* event) override;

    void paintEvent(QPaintEvent* event) override;
private slots:
    /// <summary>
    /// 样式变化槽函数
    /// </summary>
    void OnStyleChanged();

private:
    /// <summary>
    /// 初始化按钮
    /// </summary>
    void InitializeButton();

    /// <summary>
    /// 更新样式
    /// </summary>
    void UpdateStyle();

private:
    QString m_styleSheet; /// 样式表字符串
    QString m_toolTipsText; /// 提示文本
    QString m_toolTipsExText; /// 扩展提示文本
    CustomToolTips::EM_TipsType m_tipsType; /// 提示类型
    QColor m_fontColor; /// 字体颜色
    int m_fontSize; /// 字体大小
    EM_FontStyle m_fontStyle; /// 字体样式
    EM_BackgroundType m_backgroundType; /// 背景类型
    QColor m_backgroundColor; /// 背景颜色
    QColor m_gradientStartColor; /// 渐变起始颜色
    QColor m_gradientEndColor; /// 渐变结束颜色
    int m_padding; /// 内边距
    CustomToolTips* m_tips = nullptr; // tips
    int m_borderWidth;         /// 边框宽度
    QColor m_borderColor;      /// 边框颜色
};


Q_DECLARE_METATYPE(CustomToolButton::EM_BackgroundType)

Q_DECLARE_METATYPE(CustomToolButton::EM_FontSize)

Q_DECLARE_METATYPE(CustomToolButton::EM_FontStyle)
