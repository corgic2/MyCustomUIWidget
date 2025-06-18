#include "FilePickerPlugin.h"
#include "../MuCustomUiWidget/CoreWidget/FilePicker.h"

FilePickerPlugin::FilePickerPlugin(QObject* parent)
    : CustomWidgetPlugin(parent)
{
}

QString FilePickerPlugin::domXml() const
{
    return QLatin1String(R"(
<ui language="c++">
    <widget class="FilePicker" name="filePicker">
        <property name="geometry">
            <rect>
                <x>0</x>
                <y>0</y>
                <width>250</width>
                <height>22</height>
            </rect>
        </property>
        <property name="toolTip">
            <string>文件选择器</string>
        </property>
        <property name="whatsThis">
            <string>文件选择器控件，用于选择文件路径</string>
        </property>
    </widget>
</ui>
)");
}


QString FilePickerPlugin::includeFile() const
{
    return QLatin1String("CoreWidget/FilePicker.h");
}

QString FilePickerPlugin::name() const
{
    return QLatin1String("FilePicker");
}

QString FilePickerPlugin::toolTip() const
{
    return QLatin1String("文件选择器控件");
}

QString FilePickerPlugin::whatsThis() const
{
    return QLatin1String("文件选择器控件，用于选择文件路径");
}

QWidget* FilePickerPlugin::createWidget(QWidget* parent)
{
    return new FilePicker(parent);
}

