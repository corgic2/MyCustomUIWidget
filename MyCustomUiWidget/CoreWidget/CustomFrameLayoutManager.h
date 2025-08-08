#pragma once

#include <QObject>
#include <QLayout>
#include <QWidget>

/// <summary>
/// CustomFrame布局管理器，提供与QFrame相同的布局功能
/// </summary>
class CustomFrameLayoutManager : public QObject
{
    Q_OBJECT

public:
    /// <summary>
    /// 布局类型枚举
    /// </summary>
    enum EM_LayoutType
    {
        EM_Vertical = 0,    ///< 垂直布局
        EM_Horizontal = 1,  ///< 水平布局
        EM_Grid = 2,        ///< 栅格布局
        EM_Form = 3,        ///< 表单布局
        EM_Stacked = 4,     ///< 堆叠布局
        EM_None = 5         ///< 无布局
    };
    Q_ENUM(EM_LayoutType)

    /// <summary>
    /// 构造函数
    /// </summary>
    explicit CustomFrameLayoutManager(QWidget* parent);

    /// <summary>
    /// 设置布局类型
    /// </summary>
    void SetLayoutType(EM_LayoutType type);

    /// <summary>
    /// 获取当前布局类型
    /// </summary>
    EM_LayoutType GetLayoutType() const;

    /// <summary>
    /// 获取布局类型字符串
    /// </summary>
    static QString LayoutTypeToString(EM_LayoutType type);

    /// <summary>
    /// 从字符串获取布局类型
    /// </summary>
    static EM_LayoutType StringToLayoutType(const QString& str);

    /// <summary>
    /// 获取当前布局
    /// </summary>
    QLayout* GetCurrentLayout() const;

private:
    /// <summary>
    /// 保存现有子控件
    /// </summary>
    QList<QWidget*> SaveChildren();

    /// <summary>
    /// 重新添加子控件到布局
    /// </summary>
    void RestoreChildren(const QList<QWidget*>& children, QLayout* layout);

    QWidget* m_parentWidget;    ///< 父控件
    EM_LayoutType m_currentType; ///< 当前布局类型
};