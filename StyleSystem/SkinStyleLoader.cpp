#include "SkinStyleLoader.h"
#include "SkinManager.h"
#include <QWidget>
#include <QMetaObject>
#include <QDebug>

static const char* STYLE_LOADER_KEY = "__SkinStyleLoader_autoReload__";
static const char* STYLE_NAME_KEY = "__SkinStyleLoader_styleName__";

SkinStyleLoader::SkinStyleLoader(QObject* parent)
    : QObject(parent)
{
}

bool SkinStyleLoader::loadStyle(QWidget* widget, const QString& styleName)
{
    if (!widget) {
        return false;
    }

    QString actualStyleName = styleName.isEmpty() ? getWidgetStyleName(widget) : styleName;
    
    // 存储样式名用于后续重载
    widget->setProperty(STYLE_NAME_KEY, actualStyleName);
    
    return SkinManager::instance()->loadComponentStyle(widget, actualStyleName);
}

void SkinStyleLoader::enableAutoReload(QWidget* widget, const QString& styleName)
{
    if (!widget) {
        return;
    }

    // 如果已经启用了自动重载，先移除旧的连接
    disableAutoReload(widget);

    // 创建新的加载器实例
    SkinStyleLoader* loader = new SkinStyleLoader(widget);
    
    // 存储样式名
    if (!styleName.isEmpty()) {
        widget->setProperty(STYLE_NAME_KEY, styleName);
    }
    
    // 连接到皮肤变化信号
    QObject::connect(SkinManager::instance(), &SkinManager::skinChanged,
                     loader, &SkinStyleLoader::onSkinChanged);
    
    // 存储加载器实例
    widget->setProperty(STYLE_LOADER_KEY, QVariant::fromValue(loader));
}

void SkinStyleLoader::disableAutoReload(QWidget* widget)
{
    if (!widget) {
        return;
    }

    QVariant loaderVar = widget->property(STYLE_LOADER_KEY);
    if (loaderVar.isValid()) {
        SkinStyleLoader* loader = loaderVar.value<SkinStyleLoader*>();
        if (loader) {
            loader->deleteLater();
        }
        widget->setProperty(STYLE_LOADER_KEY, QVariant());
    }
}

void SkinStyleLoader::onSkinChanged(const QString& skinId)
{
    Q_UNUSED(skinId);
    
    // 获取关联的widget
    QWidget* widget = qobject_cast<QWidget*>(parent());
    if (!widget) {
        return;
    }

    // 获取存储的样式名
    QString styleName = widget->property(STYLE_NAME_KEY).toString();
    if (styleName.isEmpty()) {
        styleName = getWidgetStyleName(widget);
    }

    // 重新加载样式
    SkinManager::instance()->loadComponentStyle(widget, styleName);
}

QString SkinStyleLoader::getWidgetStyleName(QWidget* widget)
{
    if (!widget) {
        return QString();
    }

    QString className = widget->metaObject()->className();
    
    // 移除命名空间前缀
    int lastColon = className.lastIndexOf("::");
    if (lastColon != -1) {
        className = className.mid(lastColon + 2);
    }
    
    return className;
}

QString SkinStyleLoader::getWidgetStyleKey(QWidget* widget)
{
    if (!widget) {
        return QString();
    }

    return QString("widget_%1").arg(reinterpret_cast<quintptr>(widget));
}