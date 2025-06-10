#include "CustomWidgetCollection.h"
#include <QtPlugin>
#include <QtDesigner/QExtensionManager>
#include <QtUiPlugin/QDesignerCustomWidgetInterface>
#include "CustomComboBoxPlugin.h"
#include "CustomFramePlugin.h"
#include "CustomLabelPlugin.h"
#include "CustomToolButtonPlugin.h"
#include "FilePathIconListWidgetPlugin.h"

CustomWidgetCollection::CustomWidgetCollection(QObject* parent)
    : QObject(parent)
{
    m_widgets.append(new CustomComboBoxPlugin(this));
    m_widgets.append(new CustomLabelPlugin(this));
    m_widgets.append(new CustomToolButtonPlugin(this));
    m_widgets.append(new FilePathIconListWidgetPlugin(this));
    m_widgets.append(new CustomFramePlugin(this));
}

QList<QDesignerCustomWidgetInterface*> CustomWidgetCollection::customWidgets() const
{
    return m_widgets;
}
