#include "CustomWidgetPlugin.h"
#include <QtPlugin>

CustomWidgetPlugin::CustomWidgetPlugin(QObject* parent)
    : QObject(parent)
    , m_initialized(false)
{
}

bool CustomWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

void CustomWidgetPlugin::initialize(QDesignerFormEditorInterface* /*formEditor*/)
{
    if (m_initialized)
        return;

    m_initialized = true;
}

bool CustomWidgetPlugin::isContainer() const
{
    return false;
}

QIcon CustomWidgetPlugin::icon() const
{
    return QIcon();
}

QString CustomWidgetPlugin::group() const
{
    return QStringLiteral("Custom Widgets");
}

QString CustomWidgetPlugin::toolTip() const
{
    return QString();
}

QString CustomWidgetPlugin::whatsThis() const
{
    return QString();
}

QString CustomWidgetPlugin::includeFile() const
{
    return QString();
}

QString CustomWidgetPlugin::domXml() const
{
    return QLatin1String(R"(
<ui language="c++">
    <widget class="%1" name="%2">
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