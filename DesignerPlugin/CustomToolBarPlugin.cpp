#include "CustomToolBarPlugin.h"
#include "../MuCustomUiWidget/CommonDefine/UIWidgetColorDefine.h"

CustomToolBarPlugin::CustomToolBarPlugin(QObject* parent)
    : CustomWidgetPlugin(parent)
{
}

QWidget* CustomToolBarPlugin::createWidget(QWidget* parent)
{
    return new CustomToolBar(parent);
}

QString CustomToolBarPlugin::name() const
{
    return QStringLiteral("CustomToolBar");
}

QString CustomToolBarPlugin::toolTip() const
{
    return QStringLiteral("A modern styled toolbar with enhanced features");
}

QString CustomToolBarPlugin::whatsThis() const
{
    return QStringLiteral("A custom toolbar widget that supports styling, shadows, and modern UI features");
}

QString CustomToolBarPlugin::includeFile() const
{
    return QStringLiteral("CoreWidget/CustomToolBar.h");
}

QString CustomToolBarPlugin::domXml() const
{
    // 使用预定义的颜色值
    const QColor bgColor = UIColorDefine::background_color::White;
    const QColor borderColor = UIColorDefine::border_color::Default;
    const QColor hoverColor = UIColorDefine::background_color::HoverBackground;
    const QColor pressedColor = UIColorDefine::background_color::PressedBackground;
    const QColor shadowColor = UIColorDefine::shadow_color::Light;

    return QLatin1String(R"(
<ui language="c++">
    <widget class="CustomToolBar" name="customToolBar">
        <property name="geometry">
            <rect>
                <x>0</x>
                <y>0</y>
                <width>300</width>
                <height>40</height>
            </rect>
        </property>
        <property name="iconSize">
            <number>24</number>
        </property>
        <property name="spacing">
            <number>8</number>
        </property>
        <property name="backgroundColor">
            <color>
                <red>)") + QString::number(bgColor.red()) + R"(</red>
                <green>)" + QString::number(bgColor.green()) + R"(</green>
                <blue>)" + QString::number(bgColor.blue()) + R"(</blue>
            </color>
        </property>
        <property name="borderColor">
            <color>
                <red>)" + QString::number(borderColor.red()) + R"(</red>
                <green>)" + QString::number(borderColor.green()) + R"(</green>
                <blue>)" + QString::number(borderColor.blue()) + R"(</blue>
            </color>
        </property>
        <property name="hoverColor">
            <color>
                <red>)" + QString::number(hoverColor.red()) + R"(</red>
                <green>)" + QString::number(hoverColor.green()) + R"(</green>
                <blue>)" + QString::number(hoverColor.blue()) + R"(</blue>
            </color>
        </property>
        <property name="pressedColor">
            <color>
                <red>)" + QString::number(pressedColor.red()) + R"(</red>
                <green>)" + QString::number(pressedColor.green()) + R"(</green>
                <blue>)" + QString::number(pressedColor.blue()) + R"(</blue>
            </color>
        </property>
        <property name="hasShadow">
            <bool>true</bool>
        </property>
        <property name="shadowSize">
            <number>4</number>
        </property>
        <property name="shadowColor">
            <color alpha=")" + QString::number(shadowColor.alpha()) + R"(">
                <red>)" + QString::number(shadowColor.red()) + R"(</red>
                <green>)" + QString::number(shadowColor.green()) + R"(</green>
                <blue>)" + QString::number(shadowColor.blue()) + R"(</blue>
            </color>
        </property>
    </widget>
</ui>
)";
} 