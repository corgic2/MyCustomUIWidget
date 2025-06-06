#pragma once

#include <QComboBox>
#include <QLineEdit>
#include <QListView>
#include <QtCore/QObject>
#include "UIWidgetColorDefine.h"
#include "UIWidgetGlobal.h"
#include "ui_CustomComboBox.h"

/// <summary>
/// 自定义组合框控件类，提供丰富的样式设置和搜索功能
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
    Q_PROPERTY(bool searchEnabled MEMBER m_searchEnabled WRITE SetEnableSearch)
    Q_PROPERTY(QString searchPlaceholderText READ searchPlaceholderText WRITE SetSearchPlaceholderText)

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
    explicit CustomComboBox(QWidget* parent = nullptr);

    /// <summary>
    /// 析构函数
    /// </summary>
    ~CustomComboBox() override;

    /// <summary>
    /// 获取字体颜色
    /// </summary>
    QColor fontColor() const;

    /// <summary>
    /// 获取背景颜色
    /// </summary>
    QColor backgroundColor() const;

    /// <summary>
    /// 获取项目字体颜色
    /// </summary>
    QColor itemFontColor() const;

    /// <summary>
    /// 获取项目背景颜色
    /// </summary>
    QColor itemBackgroundColor() const;

    /// <summary>
    /// 设置字体颜色
    /// </summary>
    void SetFontColor(const QColor& color);

    /// <summary>
    /// 设置背景颜色
    /// </summary>
    void SetBackgroundColor(const QColor& color);

    /// <summary>
    /// 设置项目字体颜色
    /// </summary>
    void SetItemFontColor(const QColor& color);

    /// <summary>
    /// 设置项目背景颜色
    /// </summary>
    void SetItemBackgroundColor(const QColor& color);

    /// <summary>
    /// 设置渐变背景
    /// </summary>
    void SetGradientBackground(const UIColorDefine::ST_GradientColor& gradientColor);

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
    /// 设置背景类型
    /// </summary>
    /// <param name="type">背景类型枚举值</param>
    void SetBackgroundType(const EM_BackgroundType& type);

    /// <summary>
    /// 设置下拉框项目间距
    /// </summary>
    /// <param name="spacing">间距大小（像素）</param>
    void SetItemSpacing(int spacing);

    /// <summary>
    /// 设置下拉框项目高度
    /// </summary>
    /// <param name="height">高度（像素）</param>
    void SetItemHeight(int height);

    /// <summary>
    /// 启用搜索功能
    /// </summary>
    /// <param name="enable">是否启用</param>
    void SetEnableSearch(bool enable = true);

    /// <summary>
    /// 设置搜索框提示文本
    /// </summary>
    /// <param name="text">提示文本</param>
    void SetSearchPlaceholderText(const QString& text);

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
    /// 获取渐变起始颜色
    /// </summary>
    QColor gradientStartColor() const;

    /// <summary>
    /// 获取渐变结束颜色
    /// </summary>
    QColor gradientEndColor() const;

    /// <summary>
    /// 获取项目间距
    /// </summary>
    int itemSpacing() const;

    /// <summary>
    /// 获取项目高度
    /// </summary>
    int itemHeight() const;

    /// <summary>
    /// 获取是否启用搜索
    /// </summary>
    bool isSearchEnabled() const;

    /// <summary>
    /// 获取搜索框提示文本
    /// </summary>
    QString searchPlaceholderText() const;

protected:
    /// <summary>
    /// 显示弹出窗口事件
    /// </summary>
    void showPopup() override;

    /// <summary>
    /// 隐藏弹出窗口事件
    /// </summary>
    void hidePopup() override;

private slots:
    /// <summary>
    /// 搜索文本变化槽函数
    /// </summary>
    void OnSearchTextChanged(const QString& text);

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

    /// <summary>
    /// 创建搜索框
    /// </summary>
    void CreateSearchBox();

    /// <summary>
    /// 高亮搜索文本
    /// </summary>
    /// <param name="text">原始文本</param>
    /// <param name="searchText">搜索文本</param>
    /// <returns>高亮后的HTML文本</returns>
    QString HighlightSearchText(const QString& text, const QString& searchText);

private:
    Ui::CustomComboBoxClass* m_ui; /// UI对象指针
    QString m_styleSheet; /// 样式表字符串
    QColor m_fontColor; /// 字体颜色
    EM_FontSize m_fontSize; /// 字体大小
    EM_FontStyle m_fontStyle; /// 字体样式
    EM_BackgroundType m_backgroundType; /// 背景类型
    QColor m_backgroundColor; /// 背景颜色
    QColor m_gradientStartColor; /// 渐变起始颜色
    QColor m_gradientEndColor; /// 渐变结束颜色
    QColor m_itemFontColor; /// 项目字体颜色
    QColor m_itemBackgroundColor; /// 项目背景颜色
    int m_itemSpacing; /// 项目间距
    int m_itemHeight; /// 项目高度
    bool m_searchEnabled; /// 是否启用搜索
    QLineEdit* m_searchBox; /// 搜索框指针
    QStringList m_originalItems; /// 原始项目列表
    QString m_searchPlaceholderText; /// 搜索框提示文本
    UIColorDefine::ST_GradientColor m_gradientColor; //渐变颜色
};
