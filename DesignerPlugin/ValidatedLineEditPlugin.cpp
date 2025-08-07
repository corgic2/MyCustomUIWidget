#include "ValidatedLineEditPlugin.h"

ValidatedLineEditPlugin::ValidatedLineEditPlugin(QObject* parent)
    : CustomWidgetPlugin(parent)
{
}

QWidget* ValidatedLineEditPlugin::createWidget(QWidget* parent)
{
    return new ValidatedLineEdit(parent);
}

QString ValidatedLineEditPlugin::name() const
{
    return QStringLiteral("ValidatedLineEdit");
}

QString ValidatedLineEditPlugin::toolTip() const
{
    return QStringLiteral("A line edit with input validation");
}

QString ValidatedLineEditPlugin::whatsThis() const
{
    return QStringLiteral("A line edit widget that validates input using regular expressions");
}

QString ValidatedLineEditPlugin::includeFile() const
{
    return QStringLiteral("CoreWidget/ValidatedLineEdit.h");
}

QString ValidatedLineEditPlugin::domXml() const
{
    return QLatin1String(R"(
<ui language="c++">
    <widget class="ValidatedLineEdit" name="validatedLineEdit">
        <property name="geometry">
            <rect>
                <x>0</x>
                <y>0</y>
                <width>150</width>
                <height>30</height>
            </rect>
        </property>
    </widget>
</ui>
)");
} 