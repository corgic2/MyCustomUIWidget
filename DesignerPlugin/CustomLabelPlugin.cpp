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