#include "CustomFramePlugin.h"

CustomFramePlugin::CustomFramePlugin(QObject* parent)
    : CustomWidgetPlugin(parent)
{
}

bool CustomFramePlugin::isContainer() const
{
    return true;
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
            <property name="frameShape">
                <enum>QFrame::StyledPanel</enum>
            </property>
            <property name="frameShadow">
                <enum>QFrame::Raised</enum>
            </property>
            <property name="lineWidth">
                <number>1</number>
            </property>
            <property name="midLineWidth">
                <number>0</number>
            </property>
            <property name="EM_FrameFormat">
                <enum>CustomFrame::EM_Normal</enum>
            </property>
            <property name="frameFormat">
                <string>EM_Normal</string>
            </property>
            <property name="layoutType">
                <string>Vertical</string>
            </property>
            <layout class="QVBoxLayout" name="verticalLayout">
                <property name="spacing">
                    <number>2</number>
                </property>
                <property name="leftMargin">
                    <number>4</number>
                </property>
                <property name="topMargin">
                    <number>4</number>
                </property>
                <property name="rightMargin">
                    <number>4</number>
                </property>
                <property name="bottomMargin">
                    <number>4</number>
                </property>
            </layout>
        </widget>
    </ui>
    )");
}
