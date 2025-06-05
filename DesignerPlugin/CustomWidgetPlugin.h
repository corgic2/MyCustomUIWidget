#pragma once

#include <QtUiPlugin/QDesignerCustomWidgetInterface>
#include <QtCore/qplugin.h>
#include "DesignerPluginExport.h"

/// <summary>
/// 自定义控件插件基类，实现Qt Designer插件接口
/// </summary>
class CUSTOMWIDGETPLUGIN_EXPORT CustomWidgetPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父对象指针</param>
    explicit CustomWidgetPlugin(QObject* parent = nullptr);

    /// <summary>
    /// 是否初始化
    /// </summary>
    bool isInitialized() const override;

    /// <summary>
    /// 初始化
    /// </summary>
    /// <param name="formEditor">表单编辑器接口指针</param>
    void initialize(QDesignerFormEditorInterface* formEditor) override;

    /// <summary>
    /// 是否支持容器扩展
    /// </summary>
    bool isContainer() const override;

    /// <summary>
    /// 获取图标
    /// </summary>
    QIcon icon() const override;

    /// <summary>
    /// 获取分组名称
    /// </summary>
    QString group() const override;

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
    /// 获取域名
    /// </summary>
    QString domXml() const override;

protected:
    bool m_initialized;  /// 初始化标志
}; 