#include "CustomProgressBarPlugin.h"

CustomProgressBarPlugin::CustomProgressBarPlugin(QObject* parent)
    : CustomWidgetPlugin(parent)
{
}

QWidget* CustomProgressBarPlugin::createWidget(QWidget* parent)
{
    return new CustomProgressBar(parent);
}

QString CustomProgressBarPlugin::name() const
{
    return QStringLiteral("CustomProgressBar");
}

QString CustomProgressBarPlugin::toolTip() const
{
    return QStringLiteral("A custom progress bar widget with rich styling and animation features");
}

QString CustomProgressBarPlugin::whatsThis() const
{
    return QStringLiteral("A custom progress bar widget that supports gradient colors, animations, stripes effects, and various styling options");
}

QString CustomProgressBarPlugin::includeFile() const
{
    return QStringLiteral("CoreWidget/CustomProgressBar.h");
}

QString CustomProgressBarPlugin::domXml() const
{
    return QLatin1String(R"(
    <ui language="c++">
        <widget class="CustomProgressBar" name="customProgressBar">
            <property name="geometry">
                <rect>
                    <x>0</x>
                    <y>0</y>
                    <width>200</width>
                    <height>25</height>
                </rect>
            </property>
        </widget>
    </ui>
)");
} 