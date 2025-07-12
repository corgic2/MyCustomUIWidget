#ifndef SKINSYSTEMUSAGE_H
#define SKINSYSTEMUSAGE_H

#include "StyleSystemGlobal.h"
#include <QObject>

class QWidget;
class QApplication;

/**
 * @brief 皮肤系统使用示例和工具类
 */
class STYLESYSTEM_EXPORT SkinSystemUsage : public QObject
{
    Q_OBJECT

public:
    explicit SkinSystemUsage(QObject *parent = nullptr);
    ~SkinSystemUsage();

    // 静态便捷方法
    static void initializeSkinSystem(QApplication *app);
    static void applySkinToWidget(QWidget *widget, const QString &skinId);
    static void cleanupSkinSystem();

    // 皮肤切换示例
    static void switchToLightTheme();
    static void switchToDarkTheme();
    static void switchToCustomTheme(const QString &skinId);

    // 皮肤状态查询
    static QString getCurrentSkinId();
    static QStringList getAvailableSkins();
    static bool isSkinAvailable(const QString &skinId);

    // 资源路径获取
    static QString getIconPath(const QString &iconName);
    static QString getStylePath(const QString &styleFile = "main.qss");

public slots:
    void onSkinChanged(const QString &skinId);
    void onSkinError(const QString &skinId, SkinError error);

signals:
    void skinSwitched(const QString &skinId);
    void skinLoadFailed(const QString &skinId, const QString &error);
};

#endif // SKINSYSTEMUSAGE_H 