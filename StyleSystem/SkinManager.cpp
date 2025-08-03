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
    qDeleteAll(m_skinInfos);
    m_skinInfos.clear();
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
    return m_skinResource->scanAvailableSkins();
}

QString SkinManager::parseStyleSheet(const QString& styleSheet, const QString& skinId) const
{
    QString result = styleSheet;

    // 获取皮肤信息
    SkinInfo* skinInfo = m_skinInfos.value(skinId);
    if (skinInfo)
    {
        // 替换颜色变量
        result = replaceColorVariables(result, skinInfo->colorVariables());
    }

    return result;
}

bool SkinManager::loadComponentStyle(QWidget* component, const QString& componentClassName, const QString& skinId)
{
    if (!component) {
        return false;
    }

    QString targetSkinId = skinId.isEmpty() ? m_currentSkinId : skinId;
    QString targetClassName = componentClassName;
    
    if (targetClassName.isEmpty()) {
        targetClassName = component->metaObject()->className();
    }
    
    // 获取组件样式内容
    QString styleContent = m_skinResource->getComponentStyleContent(targetSkinId, targetClassName);
    if (styleContent.isEmpty()) {
        qWarning() << "No style found for component:" << targetClassName << "in skin:" << targetSkinId;
        return false;
    }
    
    // 解析样式表（替换颜色变量等）
    QString parsedStyle = parseStyleSheet(styleContent, targetSkinId);
    
    // 应用样式到组件
    component->setStyleSheet(parsedStyle);
    
    return true;
}

bool SkinManager::addQrcResource(const QString& qrcPath, const QString& skinId)
{
    if (qrcPath.isEmpty()) {
        return false;
    }
    
    QFileInfo fileInfo(qrcPath);
    if (!fileInfo.exists())
    {
        return false;
    }

    QString targetSkinId = skinId.isEmpty() ? fileInfo.baseName() : skinId;

    // 注册QRC资源
    if (!m_skinResource->registerSkinResource(targetSkinId, qrcPath)) {
        return false;
    }
    
    // 如果是第一个添加的皮肤，设置为默认
    if (m_currentSkinId.isEmpty() || m_currentSkinId == DEFAULT_SKIN_ID) {
        setCurrentSkinId(targetSkinId);
    }
    
    return true;
}

QString SkinManager::getColorVariable(const QString& colorKey, const QString& skinId) const
{
    QString targetSkinId = skinId.isEmpty() ? m_currentSkinId : skinId;
    SkinInfo* skinInfo = m_skinInfos.value(targetSkinId);
    
    if (skinInfo) {
        return skinInfo->getColorVariable(colorKey);
    }
    
    return QString();
}

QString SkinManager::getStyleContent(const QString& fileName, const QString& skinId) const
{
    QString targetSkinId = skinId.isEmpty() ? m_currentSkinId : skinId;
    return m_skinResource->getStyleContentFromQrc(targetSkinId, fileName);
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
