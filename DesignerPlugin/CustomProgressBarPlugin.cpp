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
        <property name="minimum">
            <number>0</number>
        </property>
        <property name="maximum">
            <number>100</number>
        </property>
        <property name="value">
            <number>50</number>
        </property>
        <property name="progressBarStyle">
            <enum>CustomProgressBar::ProgressBarStyle_Default</enum>
        </property>
        <property name="enableGradient">
            <bool>false</bool>
        </property>
        <property name="enableAnimation">
            <bool>true</bool>
        </property>
        <property name="animationDuration">
            <number>500</number>
        </property>
        <property name="textPosition">
            <enum>CustomProgressBar::TextPosition_Center</enum>
        </property>
        <property name="enableShadow">
            <bool>false</bool>
        </property>
        <property name="enableBorder">
            <bool>false</bool>
        </property>
        <property name="borderWidth">
            <number>1</number>
        </property>
        <property name="borderRadius">
            <number>0</number>
        </property>
        <property name="enableStripes">
            <bool>false</bool>
        </property>
        <property name="stripeDirection">
            <enum>CustomProgressBar::StripeDirection_LeftToRight</enum>
        </property>
    </widget>
</ui>
)");
} 