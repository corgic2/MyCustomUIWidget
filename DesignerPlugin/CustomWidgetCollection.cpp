#include "CustomWidgetCollection.h"
#include <QtPlugin>
#include <QtDesigner/QExtensionManager>
#include <QtUiPlugin/QDesignerCustomWidgetInterface>
#include "CustomComboBoxPlugin.h"
#include "CustomFramePlugin.h"
#include "CustomLabelPlugin.h"
#include "CustomProgressBarPlugin.h"
#include "CustomToolBarPlugin.h"
#include "CustomToolButtonPlugin.h"
#include "FilePathIconListWidgetPlugin.h"
#include "ValidatedLineEditPlugin.h"
#include "FilePickerPlugin.h"
#include "MusicProgressBarPlugin.h"

CustomWidgetCollection::CustomWidgetCollection(QObject* parent)
    : QObject(parent)
    , m_musicProgressBarPlugin(new MusicProgressBarPlugin(this))
{
    m_widgets.append(new CustomComboBoxPlugin(this));
    m_widgets.append(new CustomFramePlugin(this));
    m_widgets.append(new CustomLabelPlugin(this));
    m_widgets.append(new CustomProgressBarPlugin(this));
    m_widgets.append(new CustomToolBarPlugin(this));
    m_widgets.append(new CustomToolButtonPlugin(this));
    m_widgets.append(new FilePathIconListWidgetPlugin(this));
    m_widgets.append(new ValidatedLineEditPlugin(this));
    m_widgets.append(new FilePickerPlugin(this));
    m_widgets.append(m_musicProgressBarPlugin);
}

QList<QDesignerCustomWidgetInterface*> CustomWidgetCollection::customWidgets() const
{
    return m_widgets;
}
