#pragma once

#include "CustomWidgetPlugin.h"
#include "CoreWidget/CustomToolBar.h"

/// <summary>
/// CustomToolBar设计器插件类
/// </summary>
class CUSTOMWIDGETPLUGIN_EXPORT CustomToolBarPlugin : public CustomWidgetPlugin
{
    Q_OBJECT

public:
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父对象指针</param>
    explicit CustomToolBarPlugin(QObject* parent = nullptr);

    /// <summary>
    /// 创建控件实例
    /// </summary>
    QWidget* createWidget(QWidget* parent) override;

    /// <summary>
    /// 获取控件名称
    /// </summary>
    QString name() const override;

    /// <summary>
    /// 获取工具提示
    /// </summary>
    QString toolTip() const override;

    /// <summary>
    /// 获取What's This提示
    /// </summary>
    QString whatsThis() const override;

    /// <summary>
    /// 获取包含文件名
    /// </summary>
    QString includeFile() const override;

    /// <summary>
    /// 获取控件的XML描述
    /// </summary>
    QString domXml() const override;
}; 