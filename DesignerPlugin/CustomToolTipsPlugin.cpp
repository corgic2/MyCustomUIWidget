#include "CustomToolTipsPlugin.h"

CustomToolTipsPlugin::CustomToolTipsPlugin(QObject* parent)
    : CustomWidgetPlugin(parent)
{
}

QWidget* CustomToolTipsPlugin::createWidget(QWidget* parent)
{
    return new CustomToolTips(parent);
}

QString CustomToolTipsPlugin::name() const
{
    return QStringLiteral("CustomToolTips");
}

QString CustomToolTipsPlugin::toolTip() const
{
    return QStringLiteral("A custom tooltip widget with enhanced features");
}

QString CustomToolTipsPlugin::whatsThis() const
{
    return QStringLiteral("A custom tooltip widget that supports styling, animation, and positioning");
}

QString CustomToolTipsPlugin::includeFile() const
{
    return QStringLiteral("UtilsWidget/CustomToolTips.h");
} 