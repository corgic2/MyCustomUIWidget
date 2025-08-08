#include "CustomComboBoxPlugin.h"

CustomComboBoxPlugin::CustomComboBoxPlugin(QObject* parent)
    : CustomWidgetPlugin(parent)
{
}

QWidget* CustomComboBoxPlugin::createWidget(QWidget* parent)
{
    return new CustomComboBox(parent);
}

QString CustomComboBoxPlugin::name() const
{
    return QStringLiteral("CustomComboBox");
}

QString CustomComboBoxPlugin::toolTip() const
{
    return QStringLiteral("A custom combo box widget with enhanced features");
}

QString CustomComboBoxPlugin::whatsThis() const
{
    return QStringLiteral("A custom combo box widget that supports styling, searching, and custom item appearance");
}

QString CustomComboBoxPlugin::includeFile() const
{
    return QStringLiteral("CoreWidget/CustomComboBox.h");
}

QString CustomComboBoxPlugin::domXml() const
{
    return QLatin1String(R"(
    <ui language="c++">
        <widget class="CustomComboBox" name="customComboBox">
            <property name="geometry">
                <rect>
                    <x>0</x>
                    <y>0</y>
                    <width>200</width>
                    <height>30</height>
                </rect>
            </property>
        </widget>
    </ui>
)");
}
