#include "CustomWidgetCollection.h"
#include "CustomLabelPlugin.h"
#include "CustomToolTipsPlugin.h"
#include "FilePathIconListWidgetItemPlugin.h"

CustomWidgetCollection::CustomWidgetCollection(QObject* parent)
    : QObject(parent)
{
    m_widgets.append(new CustomLabelPlugin(this));
    m_widgets.append(new CustomToolTipsPlugin(this));
    m_widgets.append(new FilePathIconListWidgetItemPlugin(this));
}

QList<QDesignerCustomWidgetInterface*> CustomWidgetCollection::customWidgets() const
{
    return m_widgets;
} 