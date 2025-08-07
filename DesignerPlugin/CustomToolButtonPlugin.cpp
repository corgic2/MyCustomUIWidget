#include "CustomToolButtonPlugin.h"

CustomToolButtonPlugin::CustomToolButtonPlugin(QObject* parent)
    : CustomWidgetPlugin(parent)
{
}

QWidget* CustomToolButtonPlugin::createWidget(QWidget* parent)
{
    return new CustomToolButton(parent);
}

QString CustomToolButtonPlugin::name() const
{
    return QStringLiteral("CustomToolButton");
}

QString CustomToolButtonPlugin::toolTip() const
{
    return QStringLiteral("A custom tool button widget with enhanced features");
}

QString CustomToolButtonPlugin::whatsThis() const
{
    return QStringLiteral("A custom tool button widget that supports styling and tooltips");
}

QString CustomToolButtonPlugin::includeFile() const
{
    return QStringLiteral("CoreWidget/CustomToolButton.h");
}

QString CustomToolButtonPlugin::domXml() const
{
    return QLatin1String(R"(
<ui language="c++">
    <widget class="CustomToolButton" name="customToolButton">
        <property name="geometry">
            <rect>
                <x>0</x>
                <y>0</y>
                <width>32</width>
                <height>32</height>
            </rect>
        </property>

    </widget>
</ui>
)");
} 