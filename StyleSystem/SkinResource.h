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

    // 资源发现
    QStringList scanAvailableSkins() const;
    QStringList scanResourceDirectory(const QString &directory) const;
    bool registerSkinResource(const QString &skinId, const QString &resourcePath);
    void unregisterSkinResource(const QString &skinId);

    // 资源访问
    QString getResourcePath(const QString &skinId, const QString &resourceName) const;
    QString getStyleContent(const QString &skinId) const;
    QByteArray getResourceData(const QString &skinId, const QString &resourceName) const;

    // 资源验证
    bool isResourceValid(const QString &skinId, const QString &resourceName) const;
    bool isSkinResourceComplete(const QString &skinId) const;

    // 外部资源支持
    bool loadExternalResource(const QString &filePath);
    void setExternalResourceDirectory(const QString &directory);
    QString externalResourceDirectory() const;

    // 资源监听
    void startWatching();
    void stopWatching();
    bool isWatching() const;

signals:
    void resourceChanged(const QString &skinId, const QString &resourceName);
    void skinResourceAdded(const QString &skinId);
    void skinResourceRemoved(const QString &skinId);

private slots:
    void onFileChanged(const QString &path);
    void onDirectoryChanged(const QString &path);

private:
    void initializeBuiltinResources();
    void updateResourceIndex();
    QString normalizeResourcePath(const QString &path) const;

private:
    QMap<QString, QString> m_resourcePaths;  // skinId -> resourcePath
    QFileSystemWatcher *m_watcher;
    QString m_externalResourceDirectory;
    bool m_isWatching;
};

#endif // SKINRESOURCE_H 