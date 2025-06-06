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
    {
        return;
    }

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
