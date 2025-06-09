#include "FilePathIconListWidgetPlugin.h"

FilePathIconListWidgetPlugin::FilePathIconListWidgetPlugin(QObject* parent)
    : CustomWidgetPlugin(parent)
{
}

QWidget* FilePathIconListWidgetPlugin::createWidget(QWidget* parent)
{
    return new FilePathIconListWidget(parent);
}

QString FilePathIconListWidgetPlugin::name() const
{
    return QStringLiteral("FilePathIconListWidget");
}

QString FilePathIconListWidgetPlugin::toolTip() const
{
    return QStringLiteral("A custom file list widget with icons and tooltips");
}

QString FilePathIconListWidgetPlugin::whatsThis() const
{
    return QStringLiteral("A custom widget for displaying file paths with icons, tooltips, and context menu support");
}

QString FilePathIconListWidgetPlugin::includeFile() const
{
    return QStringLiteral("DomainWidget/FilePathIconListWidget.h");
}

QString FilePathIconListWidgetPlugin::domXml() const
{
    return QLatin1String(R"(
<ui language="c++">
    <widget class="FilePathIconListWidget" name="filePathIconListWidget">
        <property name="geometry">
            <rect>
                <x>0</x>
                <y>0</y>
                <width>300</width>
                <height>600</height>
            </rect>
        </property>
        <property name="backgroundColor">
            <color>
                <red>255</red>
                <green>255</green>
                <blue>255</blue>
            </color>
        </property>
        <property name="itemHoverColor">
            <color>
                <red>230</red>
                <green>230</green>
                <blue>230</blue>
            </color>
        </property>
        <property name="itemSelectedColor">
            <color>
                <red>200</red>
                <green>200</green>
                <blue>255</blue>
            </color>
        </property>
        <property name="itemTextColor">
            <color>
                <red>0</red>
                <green>0</green>
                <blue>0</blue>
            </color>
        </property>
        <property name="itemHeight">
            <number>32</number>
        </property>
        <property name="enableHoverEffect">
            <bool>true</bool>
        </property>
        <property name="enableSelectedEffect">
            <bool>true</bool>
        </property>
        <property name="showContextMenu">
            <bool>true</bool>
        </property>
    </widget>
</ui>
)");
} 