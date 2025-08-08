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
}

SkinResource::~SkinResource()
{
}

bool SkinResource::registerResource(const QString& resourcePath)
{
    if (resourcePath.isEmpty())
    {
        return false;
    }

    if (m_resourcePaths.contains(resourcePath))
    {
        return false;
    }

    m_resourcePaths.append(resourcePath);

    // 对于QRC资源，不需要检查文件系统是否存在
    // 直接注册即可，Qt会自动处理QRC虚拟路径
    emit skinResourceAdded(resourcePath);
    return true;
}

void SkinResource::unregisterResource(const QString& resourcePath)
{
    int removed = m_resourcePaths.removeAll(resourcePath);
    if (removed > 0)
    {
        emit skinResourceRemoved(resourcePath);
    }
}

QString SkinResource::getResourcePath(const QString& resourceName) const
{
    if (m_resourcePaths.isEmpty())
    {
        return QString();
    }

    // 如果resourceName已经是完整路径，直接返回
    if (resourceName.startsWith(":/"))
    {
        return resourceName;
    }

    // 尝试所有已注册的资源路径
    for (const QString& basePath : m_resourcePaths)
    {
        QString fullPath = basePath + "/" + resourceName;
        if (QFile::exists(":" + fullPath))
        {
            return fullPath;
        }
    }

    // 如果没找到，返回第一个路径
    QString basePath = m_resourcePaths.first();
    if (resourceName.isEmpty())
    {
        return basePath;
    }
    return basePath + "/" + resourceName;
}

QString SkinResource::getStyleContent() const
{
    if (m_resourcePaths.isEmpty())
    {
        return QString();
    }

    QStringList qssFiles = findAllQssFiles();
    QString styleContent;

    for (const QString& qssFile : qssFiles)
    {
        QString content = getStyleContentFromQrc(qssFile);
        if (!content.isEmpty())
        {
            styleContent += content + "\n";
        }
    }
    return styleContent;
}

QByteArray SkinResource::getResourceData(const QString& resourceName) const
{
    if (m_resourcePaths.isEmpty())
    {
        return QByteArray();
    }

    QString fullPath = getResourcePath(resourceName);
    QFile file(":" + fullPath);

    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning() << "Failed to open resource file:" << fullPath;
        return QByteArray();
    }
    return file.readAll();
}

QString SkinResource::getComponentStyleContent(const QString& componentClassName) const
{
    if (m_resourcePaths.isEmpty())
    {
        return QString();
    }
    // 遍历所有已注册的资源路径
    for (const QString& resourcePath : m_resourcePaths)
    {
        QString qssFileName = componentClassName + ".qss";
        QString qrcPath = resourcePath + "/" + qssFileName;
        QFile file(qrcPath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return file.readAll();
        }
    }

    return QString();
}

QString SkinResource::getStyleContentFromQrc(const QString& fileName) const
{
    if (m_resourcePaths.isEmpty())
    {
        return QString();
    }

    QString resourcePath = m_resourcePaths.first();
    QString actualFileName = fileName;
    if (!actualFileName.endsWith(".qss", Qt::CaseInsensitive))
    {
        actualFileName += ".qss";
    }

    QString qrcPath = ":" + resourcePath + "/" + actualFileName;
    QFile file(qrcPath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return file.readAll();
    }

    // 尝试直接查找文件名
    qrcPath = ":" + resourcePath + "/" + fileName;
    file.setFileName(qrcPath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return file.readAll();
    }
    
    return QString();
}

QStringList SkinResource::findAllQssFiles() const
{
    QStringList qssFiles;
    if (m_resourcePaths.isEmpty())
    {
        return qssFiles;
    }

    QString resourcePath = m_resourcePaths.first();
    QString qrcBasePath = ":" + resourcePath;

    // 直接遍历资源路径下的所有QSS文件
    QDirIterator it(qrcBasePath, QStringList() << "*.qss", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        QString filePath = it.next();
        QString relativePath = filePath;
        relativePath.remove(qrcBasePath);
        if (relativePath.startsWith("/"))
        {
            relativePath = relativePath.mid(1);
        }
        qssFiles.append(relativePath);
    }
    
    return qssFiles;
}

void SkinResource::initializeBuiltinResources()
{
}
