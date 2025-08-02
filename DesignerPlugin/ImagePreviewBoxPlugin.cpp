#include "ImagePreviewBoxPlugin.h"
#include "../MyCustomUiWidget/CoreWidget/ImagePreviewBox.h"

ImagePreviewBoxPlugin::ImagePreviewBoxPlugin(QObject* parent)
    : CustomWidgetPlugin(parent)
{
}

QWidget* ImagePreviewBoxPlugin::createWidget(QWidget* parent)
{
    return new ImagePreviewBox(parent);
}

QString ImagePreviewBoxPlugin::domXml() const
{
    return QLatin1String(R"(
<ui language="c++">
    <widget class="ImagePreviewBox" name="imagePreviewBox">
        <property name="geometry">
            <rect>
                <x>0</x>
                <y>0</y>
                <width>200</width>
                <height>200</height>
            </rect>
        </property>
        <property name="scaleMode">
            <enum>ImagePreviewBox::ScaleToFit</enum>
        </property>
        <property name="enableDragDrop">
            <bool>true</bool>
        </property>
        <property name="showCropHint">
            <bool>false</bool>
        </property>
        <property name="cropSize">
            <size>
                <width>100</width>
                <height>100</height>
            </size>
        </property>
        <property name="borderWidth">
            <number>1</number>
        </property>
        <property name="placeholderText">
            <string>拖拽图片到此处或点击选择</string>
        </property>
    </widget>
</ui>
)");
}

QString ImagePreviewBoxPlugin::name() const
{
    return QLatin1String("ImagePreviewBox");
}

QString ImagePreviewBoxPlugin::includeFile() const
{
    return QLatin1String("CoreWidget/ImagePreviewBox.h");
}

QString ImagePreviewBoxPlugin::toolTip() const
{
    return QLatin1String("图片预览框控件");
}

QString ImagePreviewBoxPlugin::whatsThis() const
{
    return QLatin1String("图片预览框控件，支持拖拽加载、缩放、裁剪提示");
} 