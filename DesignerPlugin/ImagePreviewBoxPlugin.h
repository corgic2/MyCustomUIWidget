#pragma once

#include "CustomWidgetPlugin.h"

/// <summary>
/// 图片预览框设计器插件
/// </summary>
class CUSTOMWIDGETPLUGIN_EXPORT ImagePreviewBoxPlugin : public CustomWidgetPlugin
{
    Q_OBJECT

public:
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父对象指针</param>
    explicit ImagePreviewBoxPlugin(QObject* parent = nullptr);

    /// <summary>
    /// 创建控件
    /// </summary>
    /// <param name="parent">父窗口指针</param>
    /// <returns>创建的控件指针</returns>
    QWidget* createWidget(QWidget* parent) override;

    /// <summary>
    /// 域名
    /// </summary>
    /// <returns>域名</returns>
    QString domXml() const override;

    /// <summary>
    /// 名称
    /// </summary>
    /// <returns>控件名称</returns>
    QString name() const override;

    /// <summary>
    /// 包含文件
    /// </summary>
    /// <returns>包含文件名</returns>
    QString includeFile() const override;

    /// <summary>
    /// 工具提示
    /// </summary>
    /// <returns>工具提示文本</returns>
    QString toolTip() const override;

    /// <summary>
    /// what's this
    /// </summary>
    /// <returns>what's this文本</returns>
    QString whatsThis() const override;
}; 