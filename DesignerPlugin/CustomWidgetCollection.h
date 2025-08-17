#pragma once

#include <QtUiPlugin/QDesignerCustomWidgetCollectionInterface>
#include <QObject>
#include <QList>

// 前置声明新插件类
class MusicProgressBarPlugin;

/// <summary>
/// 自定义控件集合类，用于管理所有自定义控件插件
/// </summary>
class CustomWidgetCollection : public QObject, public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetCollectionInterface" FILE "customwidgetplugin.json")
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)

public:
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="parent">父对象指针</param>
    explicit CustomWidgetCollection(QObject* parent = nullptr);

    /// <summary>
    /// 获取所有自定义控件
    /// </summary>
    QList<QDesignerCustomWidgetInterface*> customWidgets() const override;

private:
    QList<QDesignerCustomWidgetInterface*> m_widgets; /// 控件列表
    MusicProgressBarPlugin* m_musicProgressBarPlugin; /// 音乐进度条插件
};