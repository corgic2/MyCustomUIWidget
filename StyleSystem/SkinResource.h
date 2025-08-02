#ifndef SKINRESOURCE_H
#define SKINRESOURCE_H

#include "StyleSystemGlobal.h"
#include <QObject>
#include <QString>
#include <QStringList>
#include <QFileSystemWatcher>
#include <QMap>

class STYLESYSTEM_EXPORT SkinResource : public QObject
{
    Q_OBJECT

public:
    explicit SkinResource(QObject *parent = nullptr);
    ~SkinResource();

    /// <summary>
    /// 资源发现
    /// </summary>
    /// <returns></returns>
    QStringList scanAvailableSkins() const;
    QStringList scanResourceDirectory(const QString &directory) const;
    bool registerSkinResource(const QString &skinId, const QString &resourcePath);
    void unregisterSkinResource(const QString &skinId);

    /// <summary>
    /// 资源访问
    /// </summary>
    /// <param name="skinId"></param>
    /// <param name="resourceName"></param>
    /// <returns></returns>
    QString getResourcePath(const QString &skinId, const QString &resourceName) const;
    QString getStyleContent(const QString &skinId) const;
    QByteArray getResourceData(const QString &skinId, const QString &resourceName) const;
    
    /// <summary>
    /// 组件特定样式访问
    /// </summary>
    /// <param name="skinId"></param>
    /// <param name="componentClassName"></param>
    /// <returns></returns>
    QString getComponentStyleContent(const QString &skinId, const QString &componentClassName) const;
    QStringList getAvailableComponents(const QString &skinId) const;
    
    /// <summary>
    /// 从QRC中查找任意QSS文件内容
    /// </summary>
    /// <param name="skinId"></param>
    /// <param name="fileName"></param>
    /// <returns></returns>
    QString getStyleContentFromQrc(const QString &skinId, const QString &fileName) const;
    
    /// <summary>
    /// 递归查找QRC中所有QSS文件
    /// </summary>
    /// <param name="skinId"></param>
    /// <returns></returns>
    QStringList findAllQssFiles(const QString &skinId) const;

    /// <summary>
    /// 资源验证
    /// </summary>
    /// <param name="skinId"></param>
    /// <param name="resourceName"></param>
    /// <returns></returns>
    bool isResourceValid(const QString &skinId, const QString &resourceName) const; //是否有效
    bool isSkinResourceComplete(const QString &skinId) const; // 是否存在
    /// <summary>
    /// 外部资源支持
    /// </summary>
    /// <param name="filePath"></param>
    /// <returns></returns>
    bool loadExternalResource(const QString &filePath);
    void setExternalResourceDirectory(const QString &directory);
    QString externalResourceDirectory() const;



signals:
    void resourceChanged(const QString &skinId, const QString &resourceName);
    void skinResourceAdded(const QString &skinId);
    void skinResourceRemoved(const QString &skinId);



private:
    void initializeBuiltinResources();
    void updateResourceIndex();
    QString normalizeResourcePath(const QString &path) const;

private:
    /// <summary>
    /// 皮肤id -> 资源路径
    /// /// </summary>
    QMap<QString, QString> m_resourcePaths;  // skinId -> resourcePath
    QFileSystemWatcher *m_watcher;
    QString m_externalResourceDirectory;
};

#endif // SKINRESOURCE_H