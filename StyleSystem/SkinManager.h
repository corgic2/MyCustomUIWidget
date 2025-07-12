#ifndef SKINMANAGER_H
#define SKINMANAGER_H

#include "StyleSystemGlobal.h"
#include "SkinInfo.h"
#include "SkinResource.h"
#include <QObject>
#include <QApplication>
#include <QSettings>
#include <QMap>
#include <QMutex>

class STYLESYSTEM_EXPORT SkinManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentSkinId READ currentSkinId WRITE setCurrentSkinId NOTIFY currentSkinIdChanged)
    Q_PROPERTY(QStringList availableSkins READ availableSkins NOTIFY availableSkinsChanged)

public:
    static SkinManager* instance();
    static void destroyInstance();

    // 皮肤管理
    bool loadSkin(const QString &skinId);
    bool applySkin(const QString &skinId);
    bool applyGlobalStyle();
    
    QString currentSkinId() const;
    void setCurrentSkinId(const QString &skinId);
    
    QStringList availableSkins() const;
    SkinInfo* getSkinInfo(const QString &skinId) const;
    
    // 资源访问
    QString getResourcePath(const QString &skinId, const QString &resourceName) const;
    QString getResourcePath(const QString &resourceName) const; // 使用当前皮肤
    
    // 样式处理
    QString parseStyleSheet(const QString &styleSheet, const QString &skinId) const;
    QString getCurrentStyleSheet() const;
    
    // 配置管理
    void loadSettings();
    void saveSettings();
    
    // 错误处理
    SkinError getLastError() const;
    QString getErrorString(SkinError error) const;

public slots:
    void refreshAvailableSkins();
    void resetToDefaultSkin();

signals:
    void currentSkinIdChanged(const QString &skinId);
    void availableSkinsChanged(const QStringList &skins);
    void skinChanged(const QString &skinId);
    void skinLoadError(const QString &skinId, SkinError error);

private:
    explicit SkinManager(QObject *parent = nullptr);
    ~SkinManager();
    
    // 初始化
    void initializeBuiltinSkins();
    void loadSkinConfigs();
    
    // 皮肤加载
    bool loadSkinConfig(const QString &skinId);
    bool validateSkinStructure(const QString &skinId);
    
    // 样式解析
    QString replaceColorVariables(const QString &styleSheet, const QMap<QString, QString> &variables) const;
    QString processStyleDirectives(const QString &styleSheet) const;
    
    // 回退机制
    void fallbackToDefaultSkin();

private:
    static SkinManager *s_instance;
    static QMutex s_mutex;
    
    QString m_currentSkinId;
    QString m_currentStyleSheet;
    QMap<QString, SkinInfo*> m_skinInfos;
    SkinResource *m_skinResource;
    QSettings *m_settings;
    SkinError m_lastError;
    
    Q_DISABLE_COPY(SkinManager)
};

#endif // SKINMANAGER_H 