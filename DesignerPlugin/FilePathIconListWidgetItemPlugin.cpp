#include "FilePathIconListWidgetItemPlugin.h"

FilePathIconListWidgetItemPlugin::FilePathIconListWidgetItemPlugin(QObject* parent)
    : CustomWidgetPlugin(parent)
{
}

QWidget* FilePathIconListWidgetItemPlugin::createWidget(QWidget* parent)
{
    return new FilePathIconListWidgetItem(parent);
}

QString FilePathIconListWidgetItemPlugin::name() const
{
    return QStringLiteral("FilePathIconListWidgetItem");
}

QString FilePathIconListWidgetItemPlugin::toolTip() const
{
    return QStringLiteral("A custom list widget item with icon and file path display");
}

QString FilePathIconListWidgetItemPlugin::whatsThis() const
{
    return QStringLiteral("A custom list widget item that displays file paths with icons and supports hover effects");
}

QString FilePathIconListWidgetItemPlugin::includeFile() const
{
    return QStringLiteral("DomainWidget/FilePathIconListWidgetItem.h");
} 