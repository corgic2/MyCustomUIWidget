#include "MusicProgressBarPlugin.h"

MusicProgressBarPlugin::MusicProgressBarPlugin(QObject* parent)
    : CustomWidgetPlugin(parent)
{
}

QWidget* MusicProgressBarPlugin::createWidget(QWidget* parent)
{
    return new MusicProgressBar(parent);
}

QString MusicProgressBarPlugin::name() const
{
    return QStringLiteral("MusicProgressBar");
}

QString MusicProgressBarPlugin::toolTip() const
{
    return QStringLiteral("A custom music progress bar widget with enhanced features");
}

QString MusicProgressBarPlugin::whatsThis() const
{
    return QStringLiteral("A custom music progress bar widget that supports styling, eliding, and tooltips");
}

QString MusicProgressBarPlugin::includeFile() const
{
    return QStringLiteral("CoreWidget/MusicProgressBar.h");
}

QString MusicProgressBarPlugin::domXml() const
{
    return QLatin1String(R"(
    <ui language="c++">
        <widget class="MusicProgressBar" name="musicProgressBar">
            <property name="geometry">
                <rect>
                    <x>0</x>
                    <y>0</y>
                    <width>300</width>
                    <height>30</height>
                </rect>
            </property>
            <property name="progress">
                <number>0</number>
            </property>
            <property name="bufferProgress">
                <number>0</number>
            </property>
            <property name="duration">
                <number>0</number>
            </property>
            <property name="clickJumpEnabled">
                <bool>true</bool>
            </property>
            <property name="showMilliseconds">
                <bool>false</bool>
            </property>
        </widget>
    </ui>
    )");
}

bool MusicProgressBarPlugin::isContainer() const
{
    return false;
}