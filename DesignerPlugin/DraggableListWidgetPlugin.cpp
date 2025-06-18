#include "DraggableListWidgetPlugin.h"

DraggableListWidgetPlugin::DraggableListWidgetPlugin(QObject* parent)
    : CustomWidgetPlugin(parent)
{
}

QWidget* DraggableListWidgetPlugin::createWidget(QWidget* parent)
{
    return new DraggableListWidget(parent);
}

QString DraggableListWidgetPlugin::name() const
{
    return QStringLiteral("DraggableListWidget");
}

QString DraggableListWidgetPlugin::toolTip() const
{
    return QStringLiteral("可拖拽排序列表控件");
}

QString DraggableListWidgetPlugin::whatsThis() const
{
    return QStringLiteral("一个支持拖拽排序的列表控件，适用于任务优先级管理等场景");
}

QString DraggableListWidgetPlugin::includeFile() const
{
    return QStringLiteral("CoreWidget/DraggableListWidget.h");
}

QString DraggableListWidgetPlugin::domXml() const
{
    return QLatin1String(R"(
<ui language="c++">
    <widget class="DraggableListWidget" name="draggableListWidget">
        <property name="geometry">
            <rect>
                <x>0</x>
                <y>0</y>
                <width>200</width>
                <height>300</height>
            </rect>
        </property>
        <property name="dragEnabled">
            <bool>true</bool>
        </property>
        <property name="dropIndicatorVisible">
            <bool>true</bool>
        </property>
        <property name="dropIndicatorWidth">
            <number>2</number>
        </property>
        <property name="alternatingRowColors">
            <bool>true</bool>
        </property>
    </widget>
</ui>
)");
} 