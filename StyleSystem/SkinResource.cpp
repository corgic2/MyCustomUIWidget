#include "SkinResource.h"
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QResource>

SkinResource::SkinResource(QObject* parent)
    : QObject(parent)
{
    initializeBuiltinResources();
    m_skinPreFix.insert("default", { "/Default","/CoreWidget","/DomainWidget" });
}

SkinResource::~SkinResource()
{
}

QStringList SkinResource::scanAvailableSkins() const
{
    QStringList skins;

    // 只返回内置资源
    for (auto it = m_resourcePaths.begin(); it != m_resourcePaths.end(); ++it)
    {
        skins.append(it.key());
    }

    return skins;
}

bool SkinResource::registerSkinResource(const QString& skinId, const QString& resourcePath)
{
    if (skinId.isEmpty() || resourcePath.isEmpty())
    {
        return false;
    }

    m_resourcePaths[skinId] = resourcePath;
    emit skinResourceAdded(skinId);
    return true;
}

void SkinResource::unregisterSkinResource(const QString& skinId)
{
    if (m_resourcePaths.remove(skinId) > 0)
    {
        emit skinResourceRemoved(skinId);
    }
}

QString SkinResource::getResourcePath(const QString& skinId, const QString& resourceName) const
{
    if (!m_resourcePaths.contains(skinId))
    {
        return QString();
    }

    return QString(":%1/%2").arg(skinId, resourceName);
}

QString SkinResource::getStyleContent(const QString& skinId) const
{
    QString stylePath = getResourcePath(skinId, DEFAULT_STYLE_FILE);
    QFile file(stylePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open style file:" << stylePath;
        return QString();
    }

    return file.readAll();
}

QByteArray SkinResource::getResourceData(const QString& skinId, const QString& resourceName) const
{
    QString resourcePath = getResourcePath(skinId, resourceName);
    QFile file(resourcePath);

    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning() << "Failed to open resource file:" << resourcePath;
        return QByteArray();
    }

    return file.readAll();
}

QString SkinResource::getComponentStyleContent(const QString& skinId, const QString& componentClassName) const
{
    // 支持灵活的QSS文件查找，不再限制固定路径
    QStringList qssFiles = findAllQssFiles(skinId);

    // 优先查找完全匹配的文件名
    for (const QString& filePath : qssFiles)
    {
        QFileInfo fileInfo(filePath);
        if (fileInfo.baseName().compare(componentClassName, Qt::CaseInsensitive) == 0)
        {
            QFile file(filePath);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                return file.readAll();
            }
        }
    }

    return QString();
}

QString SkinResource::getStyleContentFromQrc(const QString& skinId, const QString& fileName) const
{
    if (!m_resourcePaths.contains(skinId))
    {
        return QString();
    }

    QString resourceBase = QString(":/%1").arg(skinId);

    // 直接查找指定文件名的QSS文件
    QString targetFile = fileName;
    if (!targetFile.endsWith(".qss", Qt::CaseInsensitive))
    {
        targetFile += ".qss";
    }

    QStringList allFiles = findAllQssFiles(skinId);
    for (const QString& filePath : allFiles)
    {
        QFileInfo fileInfo(filePath);
        if (fileInfo.fileName().compare(targetFile, Qt::CaseInsensitive) == 0)
        {
            QFile file(filePath);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                return file.readAll();
            }
        }
    }

    return QString();
}

QStringList SkinResource::findAllQssFiles(const QString& skinId) const
{
    QStringList qssFiles;
    
    // 支持MyCustomUiWidget的qrc资源结构
    for (const QString& prefix : m_skinPreFix.value(skinId))
    {
        // 使用QDirIterator遍历qrc中的QSS文件
        QDirIterator it(":" + prefix, QStringList() << "*.qss", QDir::Files, QDirIterator::Subdirectories);

        while (it.hasNext())
        {
            qssFiles.append(it.next());
        }
    }
    return qssFiles;
}

void SkinResource::initializeBuiltinResources()
{
    // 注册MyCustomUiWidget的内置资源
    registerSkinResource("default", "MyCustomUiWidget");
}
