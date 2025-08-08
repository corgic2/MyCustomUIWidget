#ifndef SKINSTYLELOADER_H
#define SKINSTYLELOADER_H

#include "StyleSystemGlobal.h"
#include <QObject>
#include <QWidget>

class STYLESYSTEM_EXPORT SkinStyleLoader : public QObject
{
    Q_OBJECT

public:
    explicit SkinStyleLoader(QObject* parent = nullptr);
    ~SkinStyleLoader() = default;

    /// <summary>
    /// 为组件自动加载样式
    /// </summary>
    /// <param name="widget">目标组件</param>
    /// <param name="styleName">样式文件名，为空时使用组件类名</param>
    /// <returns>是否加载成功</returns>
    static bool loadStyle(QWidget* widget, const QString& styleName = QString());

    /// <summary>
    /// 启用自动重载功能（皮肤切换时自动更新）
    /// </summary>
    /// <param name="widget">目标组件</param>
    /// <param name="styleName">样式文件名，为空时使用组件类名</param>
    static void enableAutoReload(QWidget* widget, const QString& styleName = QString());

    /// <summary>
    /// 禁用自动重载功能
    /// </summary>
    /// <param name="widget">目标组件</param>
    static void disableAutoReload(QWidget* widget);

private slots:
    void onSkinChanged(const QString& skinId);

private:
    static QString getWidgetStyleName(QWidget* widget);
    static QString getWidgetStyleKey(QWidget* widget);

private:
    Q_DISABLE_COPY(SkinStyleLoader)
};

/// <summary>
/// 自动样式加载器宏，用于简化组件内部使用
/// </summary>
#define AUTO_LOAD_SKIN_STYLE() \
    do { \
        SkinStyleLoader::loadStyle(this); \
        SkinStyleLoader::enableAutoReload(this); \
    } while(0)

/// <summary>
/// 自动样式加载器宏（指定样式名）
/// </summary>
#define AUTO_LOAD_SKIN_STYLE_NAME(styleName) \
    do { \
        SkinStyleLoader::loadStyle(this, styleName); \
        SkinStyleLoader::enableAutoReload(this, styleName); \
    } while(0)

#endif // SKINSTYLELOADER_H