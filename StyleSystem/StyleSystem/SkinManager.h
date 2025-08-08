#ifndef SKINMANAGER_H
#define SKINMANAGER_H

#include <QApplication>
#include <QMap>
#include <QMutex>
#include <QObject>
#include <QSettings>
#include "SkinVersionInfo.h"
#include "SkinResource.h"
#include "StyleSystemGlobal.h"

/// <summary>
/// 皮肤主题管理类
/// </summary>
class STYLESYSTEM_EXPORT SkinManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentSkinId READ currentSkinId WRITE setCurrentSkinId NOTIFY currentSkinIdChanged)
    Q_PROPERTY(QStringList availableSkins READ availableSkins NOTIFY availableSkinsChanged)
public:
    static SkinManager* instance();
    static void destroyInstance();

    /// <summary>
    /// 获取当前皮肤ID
    /// </summary>
    QString currentSkinId() const;
    void setCurrentSkinId(const QString& skinId);
    
    /// <summary>
    /// 获取可用皮肤列表
    /// </summary>
    QStringList availableSkins() const;

    /// <summary>
    /// 加载组件样式并自动应用
    /// </summary>
    /// <param name="component">目标组件</param>
    /// <param name="componentClassName">组件类名，为空时自动获取</param>
    /// <param name="skinId">皮肤ID，为空时使用当前皮肤</param>
    /// <returns></returns>
    bool loadComponentStyle(QWidget* component, const QString& componentClassName = QString());
    
    /// <summary>
    /// 添加QRC文件路径到皮肤系统（全局资源，所有皮肤共用）
    /// </summary>
    /// <param name="qrcPath">QRC文件路径</param>
    /// <returns></returns>
    bool addQrcResource(const QString& qrcPath);
    
    /// <summary>
    /// 添加皮肤版本信息（JSON配置文件）
    /// </summary>
    /// <param name="skinId">皮肤ID</param>
    /// <param name="jsonPath">JSON配置文件路径</param>
    /// <returns></returns>
    bool addSkinVersionInfo(const QString& skinId, const QString& jsonPath);

    /// <summary>
    /// 获取颜色变量值
    /// </summary>
    /// <param name="colorKey">颜色键名</param>
    /// <param name="skinId">皮肤ID</param>
    /// <returns></returns>
    QString getColorVariable(const QString& colorKey, const QString& skinId = QString()) const;
    /// <summary>
    /// 从QRC中获取任意QSS文件内容
    /// </summary>
    /// <param name="fileName">QSS文件名（可不带.qss后缀）</param>
    /// <param name="skinId">皮肤ID，为空时使用当前皮肤</param>
    /// <returns>QSS内容字符串</returns>
    QString getStyleContent(const QString& fileName, const QString& skinId = QString()) const;
    /// <summary>
    /// 替换颜色变量
    /// </summary>
    /// <param name="styleSheet"></param>
    /// <returns></returns>
    QString parseStyleSheet(const QString& styleSheet) const;
    /// <summary>
    /// 替换颜色变量
    /// </summary>
    /// <param name="color">如 @dark_color</param>
    /// <returns></returns>
    QColor parseColorSheet(const QString& color) const;
signals:
    void currentSkinIdChanged(const QString& skinId);
    void availableSkinsChanged(const QStringList& skins);
    void skinChanged(const QString& skinId);
private:
    explicit SkinManager(QObject* parent = nullptr);
    ~SkinManager() override;

    QString replaceColorVariables(const QString& styleSheet, const QMap<QString, QString>& variables) const;
private:
    static SkinManager* s_instance;
    static QMutex s_mutex;
    QString m_currentSkinId;
    SkinResource* m_skinResource = nullptr;
    QMap<QString, SkinVersionInfo*> m_SkinVersionInfos;
    Q_DISABLE_COPY(SkinManager)
};

#endif // SKINMANAGER_H
