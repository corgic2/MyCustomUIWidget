#include "CustomToolBarPlugin.h"
#include "../MyCustomUiWidget/CommonDefine/UIWidgetColorDefine.h"

CustomToolBarPlugin::CustomToolBarPlugin(QObject* parent)
    : CustomWidgetPlugin(parent)
{
}

QWidget* CustomToolBarPlugin::createWidget(QWidget* parent)
{
    return new CustomToolBar(parent);
}

QString CustomToolBarPlugin::name() const
{
    return QStringLiteral("CustomToolBar");
}

QString CustomToolBarPlugin::toolTip() const
{
    return QStringLiteral("A modern styled toolbar with enhanced features");
}

QString CustomToolBarPlugin::whatsThis() const
{
    return QStringLiteral("A custom toolbar widget that supports styling, shadows, and modern UI features");
}

QString CustomToolBarPlugin::includeFile() const
{
    return QStringLiteral("CoreWidget/CustomToolBar.h");
}

QString CustomToolBarPlugin::domXml() const
{
    // 使用预定义的颜色值
    return QLatin1String(R"(<ui language="c++">
                                <widget class="CustomToolBar" name="customToolBar">
                                    <property name="geometry">
                                        <rect>
                                            <x>0</x>
                                            <y>0</y>
                                            <width>300</width>
                                            <height>40</height>
                                        </rect>
                                    </property>
                                </widget>
                            </ui>
                            )");
}
