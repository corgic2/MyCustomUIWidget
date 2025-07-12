#include "SkinResource.h"
#include <QDir>
#include <QFile>
#include <QResource>
#include <QDirIterator>
#include <QDebug>
#include <QFileInfo>

SkinResource::SkinResource(QObject *parent)
    : QObject(parent)
    , m_watcher(new QFileSystemWatcher(this))
    , m_isWatching(false)
{
    connect(m_watcher, &QFileSystemWatcher::fileChanged,
            this, &SkinResource::onFileChanged);
    connect(m_watcher, &QFileSystemWatcher::directoryChanged,
            this, &SkinResource::onDirectoryChanged);
    
    initializeBuiltinResources();
}

SkinResource::~SkinResource()
{
    stopWatching();
}

QStringList SkinResource::scanAvailableSkins() const
{
    QStringList skins;
    
    // 扫描内置资源
    for (auto it = m_resourcePaths.begin(); it != m_resourcePaths.end(); ++it) {
        skins.append(it.key());
    }
    
    // 扫描外部资源目录
    if (!m_externalResourceDirectory.isEmpty()) {
        QStringList externalSkins = scanResourceDirectory(m_externalResourceDirectory);
        skins.append(externalSkins);
    }
    
    skins.removeDuplicates();
    return skins;
}

QStringList SkinResource::scanResourceDirectory(const QString &directory) const
{
    QStringList skins;
    QDir dir(directory);
    
    if (!dir.exists()) {
        return skins;
    }
    
    QDirIterator it(directory, QStringList() << "*.qrc", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString filePath = it.next();
        QFileInfo fileInfo(filePath);
        QString skinId = fileInfo.baseName();
        
        // 移除 _skin 后缀
        if (skinId.endsWith("_skin")) {
            skinId = skinId.left(skinId.length() - 5);
        }
        
        if (!skins.contains(skinId)) {
            skins.append(skinId);
        }
    }
    
    return skins;
}

bool SkinResource::registerSkinResource(const QString &skinId, const QString &resourcePath)
{
    if (skinId.isEmpty() || resourcePath.isEmpty()) {
        return false;
    }
    
    m_resourcePaths[skinId] = resourcePath;
    emit skinResourceAdded(skinId);
    return true;
}

void SkinResource::unregisterSkinResource(const QString &skinId)
{
    if (m_resourcePaths.remove(skinId) > 0) {
        emit skinResourceRemoved(skinId);
    }
}

QString SkinResource::getResourcePath(const QString &skinId, const QString &resourceName) const
{
    if (!m_resourcePaths.contains(skinId)) {
        return QString();
    }
    
    return QString(":%1/%2").arg(skinId, resourceName);
}

QString SkinResource::getStyleContent(const QString &skinId) const
{
    QString stylePath = getResourcePath(skinId, DEFAULT_STYLE_FILE);
    QFile file(stylePath);
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open style file:" << stylePath;
        return QString();
    }
    
    return file.readAll();
}

QByteArray SkinResource::getResourceData(const QString &skinId, const QString &resourceName) const
{
    QString resourcePath = getResourcePath(skinId, resourceName);
    QFile file(resourcePath);
    
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open resource file:" << resourcePath;
        return QByteArray();
    }
    
    return file.readAll();
}

bool SkinResource::isResourceValid(const QString &skinId, const QString &resourceName) const
{
    QString resourcePath = getResourcePath(skinId, resourceName);
    return QFile::exists(resourcePath);
}

bool SkinResource::isSkinResourceComplete(const QString &skinId) const
{
    if (!m_resourcePaths.contains(skinId)) {
        return false;
    }
    
    // 检查基本文件是否存在
    QStringList requiredFiles = {DEFAULT_STYLE_FILE, DEFAULT_CONFIG_FILE};
    for (const QString &file : requiredFiles) {
        if (!isResourceValid(skinId, file)) {
            return false;
        }
    }
    
    return true;
}

bool SkinResource::loadExternalResource(const QString &filePath)
{
    if (!QFile::exists(filePath)) {
        return false;
    }
    
    QFileInfo fileInfo(filePath);
    QString skinId = fileInfo.baseName();
    
    // 移除 _skin 后缀
    if (skinId.endsWith("_skin")) {
        skinId = skinId.left(skinId.length() - 5);
    }
    
    // 注册资源
    if (QResource::registerResource(filePath)) {
        registerSkinResource(skinId, filePath);
        return true;
    }
    
    return false;
}

void SkinResource::setExternalResourceDirectory(const QString &directory)
{
    if (m_externalResourceDirectory != directory) {
        m_externalResourceDirectory = directory;
        updateResourceIndex();
    }
}

QString SkinResource::externalResourceDirectory() const
{
    return m_externalResourceDirectory;
}

void SkinResource::startWatching()
{
    if (m_isWatching) {
        return;
    }
    
    // 监听外部资源目录
    if (!m_externalResourceDirectory.isEmpty() && QDir(m_externalResourceDirectory).exists()) {
        m_watcher->addPath(m_externalResourceDirectory);
    }
    
    m_isWatching = true;
}

void SkinResource::stopWatching()
{
    if (!m_isWatching) {
        return;
    }
    
    m_watcher->removePaths(m_watcher->directories());
    m_watcher->removePaths(m_watcher->files());
    m_isWatching = false;
}

bool SkinResource::isWatching() const
{
    return m_isWatching;
}

void SkinResource::onFileChanged(const QString &path)
{
    Q_UNUSED(path)
    updateResourceIndex();
}

void SkinResource::onDirectoryChanged(const QString &path)
{
    Q_UNUSED(path)
    updateResourceIndex();
}

void SkinResource::initializeBuiltinResources()
{
    // 注册内置皮肤资源
    registerSkinResource("default", ":/default");
    registerSkinResource("dark", ":/dark");
}

void SkinResource::updateResourceIndex()
{
    // 重新扫描外部资源
    if (!m_externalResourceDirectory.isEmpty()) {
        QStringList externalSkins = scanResourceDirectory(m_externalResourceDirectory);
        for (const QString &skinId : externalSkins) {
            if (!m_resourcePaths.contains(skinId)) {
                QString resourcePath = QDir(m_externalResourceDirectory).filePath(skinId + "_skin.qrc");
                if (loadExternalResource(resourcePath)) {
                    emit skinResourceAdded(skinId);
                }
            }
        }
    }
}

QString SkinResource::normalizeResourcePath(const QString &path) const
{
    return QDir::cleanPath(path);
} 