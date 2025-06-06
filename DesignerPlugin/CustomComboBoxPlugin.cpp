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
        <property name="fontSize">
            <enum>CustomComboBox::FontSize_Normal</enum>
        </property>
        <property name="fontStyle">
            <enum>CustomComboBox::FontStyle_Normal</enum>
        </property>
        <property name="backgroundType">
            <enum>CustomComboBox::BackgroundType_Transparent</enum>
        </property>
        <property name="itemSpacing">
            <number>2</number>
        </property>
        <property name="itemHeight">
            <number>24</number>
        </property>
        <property name="searchEnabled">
            <bool>false</bool>
        </property>
        <property name="searchPlaceholderText">
            <string>搜索...</string>
        </property>
    </widget>
</ui>
)");
}
