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
        <property name="text">
            <string>Custom Label</string>
        </property>
        <property name="fontSize">
            <enum>CustomLabel::FontSize_Normal</enum>
        </property>
        <property name="fontStyle">
            <enum>CustomLabel::FontStyle_Normal</enum>
        </property>
        <property name="backgroundType">
            <enum>CustomLabel::BackgroundType_Transparent</enum>
        </property>
        <property name="hasShadow">
            <bool>false</bool>
        </property>
        <property name="hasBorder">
            <bool>false</bool>
        </property>
        <property name="borderWidth">
            <number>1</number>
        </property>
        <property name="enableElide">
            <bool>false</bool>
        </property>
        <property name="imageScaleMode">
            <enum>CustomLabel::ScaleToFit</enum>
        </property>
    </widget>
</ui>
)");
} 