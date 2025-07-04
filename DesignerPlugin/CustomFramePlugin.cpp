﻿#include "CustomFramePlugin.h"

CustomFramePlugin::CustomFramePlugin(QObject* parent)
    : CustomWidgetPlugin(parent)
{
}

QWidget* CustomFramePlugin::createWidget(QWidget* parent)
{
    return new CustomFrame(parent);
}

QString CustomFramePlugin::name() const
{
    return QStringLiteral("CustomFrame");
}

QString CustomFramePlugin::toolTip() const
{
    return QStringLiteral("A custom frame widget with enhanced features");
}

QString CustomFramePlugin::whatsThis() const
{
    return QStringLiteral("A custom frame widget that supports styling, borders, and padding");
}

QString CustomFramePlugin::includeFile() const
{
    return QStringLiteral("CoreWidget/CustomFrame.h");
}

QString CustomFramePlugin::domXml() const
{
    return QLatin1String(R"(
    <ui language="c++">
    <widget class="CustomFrame" name="customFrame">
    <property name="geometry">
    <rect>
    <x>0</x>
    <y>0</y>
    <width>200</width>
    <height>150</height>
    </rect>
    </property>
    <property name="backgroundType">
    <enum>CustomFrame::BackgroundType_Transparent</enum>
    </property>
    <property name="leftBorder">
    <bool>false</bool>
    </property>
    <property name="topBorder">
    <bool>false</bool>
    </property>
    <property name="rightBorder">
    <bool>false</bool>
    </property>
    <property name="bottomBorder">
    <bool>false</bool>
    </property>
    <property name="borderWidth">
    <number>1</number>
    </property>
    <property name="padding">
    <number>0</number>
    </property>
    <property name="hasShadow">
    <bool>false</bool>
    </property>
    </widget>
    </ui>
    )");
}
