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
    /// 注册全局资源
    /// </summary>
    /// <param name="resourcePath">资源路径</param>
    /// <returns></returns>
    bool registerResource(const QString& resourcePath);
    void unregisterResource(const QString& resourcePath);

    /// <summary>
    /// 资源访问（从全局资源获取）
    /// </summary>
    /// <param name="resourceName">资源名称</param>
    /// <returns></returns>
    QString getResourcePath(const QString& resourceName) const;
    QString getStyleContent() const;
    QByteArray getResourceData(const QString& resourceName) const;
    
    /// <summary>
    /// 组件特定样式访问（从全局资源获取）
    /// </summary>
    /// <param name="componentClassName">组件类名</param>
    /// <returns></returns>
    QString getComponentStyleContent(const QString& componentClassName) const;
    
    /// <summary>
    /// 从QRC中查找任意QSS文件内容
    /// </summary>
    /// <param name="fileName">文件名</param>
    /// <returns></returns>
    QString getStyleContentFromQrc(const QString& fileName) const;
    /// <summary>
    /// 寻找所有QSS文件
    /// </summary>
    /// <returns></returns>
    QStringList findAllQssFiles() const;
signals:
    void resourceChanged(const QString& resourceName);
    void skinResourceAdded(const QString& resourcePath);
    void skinResourceRemoved(const QString& resourcePath);
private:
    void initializeBuiltinResources();
private:
    /// <summary>
    /// 资源路径列表
    /// </summary>
    QStringList m_resourcePaths;
    QStringList m_resourcePrefixes;
};

#endif // SKINRESOURCE_H