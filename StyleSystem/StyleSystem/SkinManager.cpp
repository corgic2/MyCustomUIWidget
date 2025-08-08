#include "SkinManager.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMutexLocker>
#include <QStandardPaths>
#include <QWidget>
SkinManager* SkinManager::s_instance = nullptr;
QMutex SkinManager::s_mutex;

SkinManager::SkinManager(QObject* parent)
    : QObject(parent), m_currentSkinId(DEFAULT_SKIN_ID), m_skinResource(new SkinResource(this))
{
}

SkinManager::~SkinManager()
{
    qDeleteAll(m_SkinVersionInfos);
    m_SkinVersionInfos.clear();
}

SkinManager* SkinManager::instance()
{
    if (!s_instance)
    {
        QMutexLocker locker(&s_mutex);
        if (!s_instance)
        {
            s_instance = new SkinManager();
        }
    }
    return s_instance;
}

void SkinManager::destroyInstance()
{
    QMutexLocker locker(&s_mutex);
    if (s_instance)
    {
        delete s_instance;
        s_instance = nullptr;
    }
}

QString SkinManager::currentSkinId() const
{
    return m_currentSkinId;
}

void SkinManager::setCurrentSkinId(const QString& skinId)
{
    if (m_currentSkinId != skinId)
    {
        m_currentSkinId = skinId;
        emit currentSkinIdChanged(skinId);
        emit skinChanged(skinId);
    }
}

QStringList SkinManager::availableSkins() const
{
    return m_SkinVersionInfos.keys();
}

QString SkinManager::parseStyleSheet(const QString& styleSheet) const
{
    QString result = styleSheet;

    // 获取皮肤信息
    SkinVersionInfo* SkinVersionInfo = m_SkinVersionInfos.value(m_currentSkinId);
    if (SkinVersionInfo)
    {
        // 替换颜色变量
        result = replaceColorVariables(result, SkinVersionInfo->colorVariables());
    }

    return result;
}

QColor SkinManager::parseColorSheet(const QString& color) const
{
    QString result;

    // 获取皮肤信息
    SkinVersionInfo* SkinVersionInfo = m_SkinVersionInfos.value(m_currentSkinId);
    if (SkinVersionInfo)
    {
        // 替换颜色变量
        result = replaceColorVariables(color, SkinVersionInfo->colorVariables());
    }
    QStringList str = result.split(',');
    if (str.size() == 3)
    {
        return QColor(str[0].toInt(), str[1].toInt(), str[2].toInt());
    }
    else if (str.size() == 4)
    {
        return QColor(str[0].toInt(), str[1].toInt(), str[2].toInt(), str[3].toDouble());
    }
    return QColor();
}

bool SkinManager::loadComponentStyle(QWidget* component, const QString& componentClassName)
{
    if (!component) {
        return false;
    }

    QString targetSkinId = m_currentSkinId;
    QString targetClassName = componentClassName;
    
    if (targetClassName.isEmpty()) {
        targetClassName = component->metaObject()->className();
    }

    // 获取组件样式内容（统一从default资源获取）
    QString styleContent = m_skinResource->getComponentStyleContent(targetClassName);
    if (styleContent.isEmpty()) {
        qWarning() << "No style found for component:" << targetClassName << "in skin:" << targetSkinId;
        return false;
    }
    
    // 解析样式表（替换颜色变量等）
    QString parsedStyle = parseStyleSheet(styleContent);
    
    // 应用样式到组件
    component->setStyleSheet(parsedStyle);
    
    return true;
}

bool SkinManager::addQrcResource(const QString& qrcPath)
{
    if (qrcPath.isEmpty()) {
        return false;
    }
    // 注册QRC资源（全局资源，不绑定皮肤ID）
    return m_skinResource->registerResource(qrcPath);
}

bool SkinManager::addSkinVersionInfo(const QString& skinId, const QString& jsonPath)
{
    if (skinId.isEmpty() || jsonPath.isEmpty())
    {
        return false;
    }

    QFileInfo fileInfo(jsonPath);
    if (!fileInfo.exists())
    {
        return false;
    }

    QFile jsonFile(jsonPath);
    if (!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open skin config file:" << jsonPath;
        return false;
    }

    QByteArray jsonData = jsonFile.readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
    if (jsonDoc.isNull())
    {
        qWarning() << "Invalid JSON format:" << jsonPath;
        return false;
    }

    auto versionInfo = new SkinVersionInfo(skinId, this);
    if (!versionInfo->fromVariantMap(jsonDoc.object().toVariantMap()))
    {
        delete versionInfo;
        return false;
    }

    // 移除旧版本信息
    if (m_SkinVersionInfos.contains(skinId))
    {
        delete m_SkinVersionInfos.take(skinId);
    }

    // 添加新版本信息
    m_SkinVersionInfos.insert(skinId, versionInfo);
    
    // 如果是第一个添加的皮肤，设置为默认
    if (m_currentSkinId.isEmpty() || m_currentSkinId == DEFAULT_SKIN_ID)
    {
        setCurrentSkinId(skinId);
    }

    emit availableSkinsChanged(availableSkins());
    return true;
}

QString SkinManager::getColorVariable(const QString& colorKey, const QString& skinId) const
{
    QString targetSkinId = skinId.isEmpty() ? m_currentSkinId : skinId;
    SkinVersionInfo* SkinVersionInfo = m_SkinVersionInfos.value(targetSkinId);

    if (SkinVersionInfo)
    {
        return SkinVersionInfo->getColorVariable(colorKey);
    }
    
    return QString();
}

QString SkinManager::getStyleContent(const QString& fileName, const QString& skinId) const
{
    QString targetSkinId = skinId.isEmpty() ? m_currentSkinId : skinId;
    return m_skinResource->getStyleContentFromQrc(fileName);
}

QString SkinManager::replaceColorVariables(const QString& styleSheet, const QMap<QString, QString>& variables) const
{
    QString result = styleSheet;

    for (auto it = variables.begin(); it != variables.end(); ++it)
    {
        result.replace(it.key(), it.value());
    }

    return result;
}
