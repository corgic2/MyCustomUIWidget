#include "CustomLabelPlugin.h"

CustomLabelPlugin::CustomLabelPlugin(QObject* parent)
    : CustomWidgetPlugin(parent)
{
}

QWidget* CustomLabelPlugin::createWidget(QWidget* parent)
{
    return new CustomLabel(parent);
}

QString CustomLabelPlugin::name() const
{
    return QStringLiteral("CustomLabel");
}

QString CustomLabelPlugin::toolTip() const
{
    return QStringLiteral("A custom label widget with enhanced features");
}

QString CustomLabelPlugin::whatsThis() const
{
    return QStringLiteral("A custom label widget that supports styling, eliding, and tooltips");
}

QString CustomLabelPlugin::includeFile() const
{
    return QStringLiteral("CoreWidget/CustomLabel.h");
}

QString CustomLabelPlugin::domXml() const
{
    return QLatin1String(R"(
    <ui language="c++">
        <widget class="CustomLabel" name="customLabel">
            <property name="geometry">
                <rect>
                    <x>0</x>
                    <y>0</y>
                    <width>100</width>
                    <height>30</height>
                </rect>
            </property>
        </widget>
    </ui>
)");
} 