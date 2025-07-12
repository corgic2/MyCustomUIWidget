#include "SkinManager.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMutexLocker>
#include <QStandardPaths>

SkinManager* SkinManager::s_instance = nullptr;
QMutex SkinManager::s_mutex;

SkinManager::SkinManager(QObject* parent)
    : QObject(parent), m_currentSkinId(DEFAULT_SKIN_ID), m_skinResource(new SkinResource(this)), m_settings(nullptr), m_lastError(SkinError::NoError)
{
    // 初始化设置
    QString configPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QDir().mkpath(configPath);
    m_settings = new QSettings(QDir(configPath).filePath("skin_settings.ini"), QSettings::IniFormat, this);

    // 连接信号 - 修复信号槽连接问题
    connect(m_skinResource, &SkinResource::skinResourceAdded, this, &SkinManager::refreshAvailableSkins);
    connect(m_skinResource, &SkinResource::skinResourceRemoved, this, &SkinManager::refreshAvailableSkins);

    // 初始化内置皮肤
    initializeBuiltinSkins();

    // 加载设置
    loadSettings();

    // 启动资源监听
    m_skinResource->startWatching();
}

SkinManager::~SkinManager()
{
    saveSettings();

    // 清理皮肤信息
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

bool SkinManager::loadSkin(const QString& skinId)
{
    if (skinId.isEmpty())
    {
        m_lastError = SkinError::InvalidSkinStructure;
        return false;
    }

    // 检查皮肤是否存在
    if (!m_skinInfos.contains(skinId))
    {
        if (!loadSkinConfig(skinId))
        {
            m_lastError = SkinError::SkinNotFound;
            emit skinLoadError(skinId, m_lastError);
            return false;
        }
    }

    // 验证皮肤结构
    if (!validateSkinStructure(skinId))
    {
        m_lastError = SkinError::InvalidSkinStructure;
        emit skinLoadError(skinId, m_lastError);
        return false;
    }

    // 加载样式表
    QString styleContent = m_skinResource->getStyleContent(skinId);
    if (styleContent.isEmpty())
    {
        m_lastError = SkinError::StyleParseError;
        emit skinLoadError(skinId, m_lastError);
        return false;
    }

    // 解析样式表
    m_currentStyleSheet = parseStyleSheet(styleContent, skinId);
    m_lastError = SkinError::NoError;

    return true;
}

bool SkinManager::applySkin(const QString& skinId)
{
    if (!loadSkin(skinId))
    {
        fallbackToDefaultSkin();
        return false;
    }

    // 应用样式
    if (!applyGlobalStyle())
    {
        fallbackToDefaultSkin();
        return false;
    }

    // 更新当前皮肤
    setCurrentSkinId(skinId);

    return true;
}

bool SkinManager::applyGlobalStyle()
{
    if (!qApp)
    {
        return false;
    }

    qApp->setStyleSheet(m_currentStyleSheet);
    return true;
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

SkinInfo* SkinManager::getSkinInfo(const QString& skinId) const
{
    return m_skinInfos.value(skinId, nullptr);
}

QString SkinManager::getResourcePath(const QString& skinId, const QString& resourceName) const
{
    return m_skinResource->getResourcePath(skinId, resourceName);
}

QString SkinManager::getResourcePath(const QString& resourceName) const
{
    return getResourcePath(m_currentSkinId, resourceName);
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

    // 处理样式指令
    result = processStyleDirectives(result);

    return result;
}

QString SkinManager::getCurrentStyleSheet() const
{
    return m_currentStyleSheet;
}

void SkinManager::loadSettings()
{
    if (!m_settings)
    {
        return;
    }

    m_settings->beginGroup("SkinManager");
    QString savedSkinId = m_settings->value("currentSkinId", DEFAULT_SKIN_ID).toString();
    m_settings->endGroup();

    // 尝试加载保存的皮肤
    if (availableSkins().contains(savedSkinId))
    {
        applySkin(savedSkinId);
    }
    else
    {
        applySkin(DEFAULT_SKIN_ID);
    }
}

void SkinManager::saveSettings()
{
    if (!m_settings)
    {
        return;
    }

    m_settings->beginGroup("SkinManager");
    m_settings->setValue("currentSkinId", m_currentSkinId);
    m_settings->endGroup();
    m_settings->sync();
}

SkinError SkinManager::getLastError() const
{
    return m_lastError;
}

QString SkinManager::getErrorString(SkinError error) const
{
    switch (error)
    {
        case SkinError::NoError:
            return tr("No error");
        case SkinError::SkinNotFound:
            return tr("Skin not found");
        case SkinError::ResourceNotFound:
            return tr("Resource not found");
        case SkinError::ConfigParseError:
            return tr("Config parse error");
        case SkinError::StyleParseError:
            return tr("Style parse error");
        case SkinError::InvalidSkinStructure:
            return tr("Invalid skin structure");
        default:
            return tr("Unknown error");
    }
}

void SkinManager::refreshAvailableSkins()
{
    loadSkinConfigs();
    emit availableSkinsChanged(availableSkins());
}

void SkinManager::resetToDefaultSkin()
{
    applySkin(DEFAULT_SKIN_ID);
}

void SkinManager::initializeBuiltinSkins()
{
    // 创建默认皮肤信息
    auto defaultSkin = new SkinInfo("default", this);
    defaultSkin->setName("Default");
    defaultSkin->setAuthor("System");
    defaultSkin->setVersion("1.0.0");
    defaultSkin->setDescription("Default system skin");

    // 设置默认颜色变量
    QMap<QString, QString> defaultColors;
    defaultColors["@primaryColor"] = "#3498db";
    defaultColors["@secondaryColor"] = "#2ecc71";
    defaultColors["@backgroundColor"] = "#ffffff";
    defaultColors["@textColor"] = "#333333";
    defaultColors["@borderColor"] = "#cccccc";
    defaultColors["@hoverColor"] = "#ecf0f1";
    defaultColors["@selectedColor"] = "#bdc3c7";
    defaultColors["@disabledColor"] = "#7f8c8d";
    defaultSkin->setColorVariables(defaultColors);

    m_skinInfos["default"] = defaultSkin;

    // 创建深色皮肤信息
    auto darkSkin = new SkinInfo("dark", this);
    darkSkin->setName("Dark");
    darkSkin->setAuthor("System");
    darkSkin->setVersion("1.0.0");
    darkSkin->setDescription("Dark theme skin");

    // 设置深色颜色变量
    QMap<QString, QString> darkColors;
    darkColors["@primaryColor"] = "#2980b9";
    darkColors["@secondaryColor"] = "#27ae60";
    darkColors["@backgroundColor"] = "#2c3e50";
    darkColors["@textColor"] = "#ecf0f1";
    darkColors["@borderColor"] = "#34495e";
    darkColors["@hoverColor"] = "#34495e";
    darkColors["@selectedColor"] = "#3498db";
    darkColors["@disabledColor"] = "#7f8c8d";
    darkSkin->setColorVariables(darkColors);

    m_skinInfos["dark"] = darkSkin;
}

void SkinManager::loadSkinConfigs()
{
    QStringList skins = m_skinResource->scanAvailableSkins();

    for (const QString& skinId : skins)
    {
        if (!m_skinInfos.contains(skinId))
        {
            loadSkinConfig(skinId);
        }
    }
}

bool SkinManager::loadSkinConfig(const QString& skinId)
{
    QString configPath = m_skinResource->getResourcePath(skinId, DEFAULT_CONFIG_FILE);
    QFile configFile(configPath);

    if (!configFile.open(QIODevice::ReadOnly))
    {
        qWarning() << "Failed to open skin config:" << configPath;
        return false;
    }

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(configFile.readAll(), &parseError);

    if (parseError.error != QJsonParseError::NoError)
    {
        qWarning() << "Failed to parse skin config:" << parseError.errorString();
        m_lastError = SkinError::ConfigParseError;
        return false;
    }

    QJsonObject config = doc.object();

    // 创建皮肤信息
    auto skinInfo = new SkinInfo(skinId, this);
    skinInfo->setName(config["name"].toString());
    skinInfo->setAuthor(config["author"].toString());
    skinInfo->setVersion(config["version"].toString());
    skinInfo->setDescription(config["description"].toString());

    // 加载颜色变量
    QJsonObject colors = config["colors"].toObject();
    QMap<QString, QString> colorVariables;
    for (auto it = colors.begin(); it != colors.end(); ++it)
    {
        colorVariables[it.key()] = it.value().toString();
    }
    skinInfo->setColorVariables(colorVariables);

    m_skinInfos[skinId] = skinInfo;
    return true;
}

bool SkinManager::validateSkinStructure(const QString& skinId)
{
    SkinInfo* skinInfo = m_skinInfos.value(skinId);
    if (!skinInfo)
    {
        return false;
    }

    return skinInfo->isValid();
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

QString SkinManager::processStyleDirectives(const QString& styleSheet) const
{
    // 这里可以处理自定义样式指令
    // 例如：@import, @include 等
    return styleSheet;
}

void SkinManager::fallbackToDefaultSkin()
{
    qWarning() << "Falling back to default skin";

    if (m_currentSkinId != DEFAULT_SKIN_ID)
    {
        applySkin(DEFAULT_SKIN_ID);
    }
}
