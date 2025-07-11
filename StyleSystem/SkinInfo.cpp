﻿#include "SkinInfo.h"
#include <QDir>
#include <QFileInfo>

SkinInfo::SkinInfo(QObject* parent)
    : QObject(parent)
{
    // 设置默认必需文件
    m_requiredFiles << DEFAULT_STYLE_FILE << DEFAULT_CONFIG_FILE;
}

SkinInfo::SkinInfo(const QString& skinId, QObject* parent)
    : QObject(parent), m_id(skinId)
{
    // 设置默认必需文件
    m_requiredFiles << DEFAULT_STYLE_FILE << DEFAULT_CONFIG_FILE;
}

SkinInfo::~SkinInfo()
{
}

QString SkinInfo::id() const
{
    return m_id;
}

void SkinInfo::setId(const QString& id)
{
    if (m_id != id)
    {
        m_id = id;
        emit idChanged(id);
    }
}

QString SkinInfo::name() const
{
    return m_name;
}

void SkinInfo::setName(const QString& name)
{
    if (m_name != name)
    {
        m_name = name;
        emit nameChanged(name);
    }
}

QString SkinInfo::author() const
{
    return m_author;
}

void SkinInfo::setAuthor(const QString& author)
{
    if (m_author != author)
    {
        m_author = author;
        emit authorChanged(author);
    }
}

QString SkinInfo::version() const
{
    return m_version;
}

void SkinInfo::setVersion(const QString& version)
{
    if (m_version != version)
    {
        m_version = version;
        emit versionChanged(version);
    }
}

QString SkinInfo::description() const
{
    return m_description;
}

void SkinInfo::setDescription(const QString& description)
{
    if (m_description != description)
    {
        m_description = description;
        emit descriptionChanged(description);
    }
}

QString SkinInfo::resourcePath() const
{
    return m_resourcePath;
}

void SkinInfo::setResourcePath(const QString& path)
{
    m_resourcePath = path;
}

QString SkinInfo::configPath() const
{
    return m_configPath;
}

void SkinInfo::setConfigPath(const QString& path)
{
    m_configPath = path;
}

QString SkinInfo::stylePath() const
{
    return m_stylePath;
}

void SkinInfo::setStylePath(const QString& path)
{
    m_stylePath = path;
}

QMap<QString, QString> SkinInfo::colorVariables() const
{
    return m_colorVariables;
}

void SkinInfo::setColorVariables(const QMap<QString, QString>& variables)
{
    m_colorVariables = variables;
}

void SkinInfo::addColorVariable(const QString& name, const QString& value)
{
    m_colorVariables[name] = value;
}

QString SkinInfo::getColorVariable(const QString& name) const
{
    return m_colorVariables.value(name);
}

QStringList SkinInfo::requiredFiles() const
{
    return m_requiredFiles;
}

void SkinInfo::setRequiredFiles(const QStringList& files)
{
    m_requiredFiles = files;
}

void SkinInfo::addRequiredFile(const QString& file)
{
    if (!m_requiredFiles.contains(file))
    {
        m_requiredFiles.append(file);
    }
}

bool SkinInfo::isValid() const
{
    return validate() == SkinError::NoError;
}

SkinError SkinInfo::validate() const
{
    // 检查基本信息
    if (m_id.isEmpty())
    {
        return SkinError::InvalidSkinStructure;
    }

    // 检查资源路径
    if (m_resourcePath.isEmpty())
    {
        return SkinError::ResourceNotFound;
    }

    // 检查必需文件
    for (const QString& file : m_requiredFiles)
    {
        QString filePath = QString(":%1/%2").arg(m_id, file);
        QFileInfo fileInfo(filePath);
        if (!fileInfo.exists())
        {
            return SkinError::ResourceNotFound;
        }
    }

    return SkinError::NoError;
}

QVariantMap SkinInfo::toVariantMap() const
{
    QVariantMap map;
    map["id"] = m_id;
    map["name"] = m_name;
    map["author"] = m_author;
    map["version"] = m_version;
    map["description"] = m_description;
    
    // 修复：将QMap转换为QVariantMap
    QVariantMap colorVariantMap;
    for (auto it = m_colorVariables.begin(); it != m_colorVariables.end(); ++it)
    {
        colorVariantMap[it.key()] = it.value();
    }
    map["colorVariables"] = colorVariantMap;
    
    map["requiredFiles"] = m_requiredFiles;
    return map;
}

bool SkinInfo::fromVariantMap(const QVariantMap& map)
{
    setId(map.value("id").toString());
    setName(map.value("name").toString());
    setAuthor(map.value("author").toString());
    setVersion(map.value("version").toString());
    setDescription(map.value("description").toString());

    // 修复：从QVariantMap转换为QMap<QString, QString>
    QVariantMap colorMap = map.value("colorVariables").toMap();
    QMap<QString, QString> colorVariables;
    for (auto it = colorMap.begin(); it != colorMap.end(); ++it)
    {
        colorVariables[it.key()] = it.value().toString();
    }
    m_colorVariables = colorVariables;

    m_requiredFiles = map.value("requiredFiles").toStringList();

    return true;
}
