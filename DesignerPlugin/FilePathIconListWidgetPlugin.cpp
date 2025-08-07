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
    </widget>
</ui>
)");
} 