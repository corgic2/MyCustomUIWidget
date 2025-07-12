#include "SkinSystemUsage.h"
#include "SkinManager.h"
#include <QApplication>
#include <QWidget>
#include <QDebug>

SkinSystemUsage::SkinSystemUsage(QObject *parent)
    : QObject(parent)
{
    // 连接皮肤管理器的信号
    connect(SkinManager::instance(), &SkinManager::skinChanged,
            this, &SkinSystemUsage::onSkinChanged);
    connect(SkinManager::instance(), &SkinManager::skinLoadError,
            this, &SkinSystemUsage::onSkinError);
}

SkinSystemUsage::~SkinSystemUsage()
{
}

void SkinSystemUsage::initializeSkinSystem(QApplication *app)
{
    Q_UNUSED(app)
    
    // 初始化皮肤管理器
    SkinManager *manager = SkinManager::instance();
    
    // 加载默认皮肤
    if (!manager->applySkin("default")) {
        qWarning() << "Failed to load default skin";
    }
    
    qDebug() << "皮肤系统初始化完成";
    qDebug() << "可用皮肤:" << manager->availableSkins();
}

void SkinSystemUsage::applySkinToWidget(QWidget *widget, const QString &skinId)
{
    if (!widget) {
        qWarning() << "Widget is null";
        return;
    }
    
    SkinManager *manager = SkinManager::instance();
    
    // 获取皮肤样式表
    if (manager->applySkin(skinId)) {
        QString styleSheet = manager->getCurrentStyleSheet();
        widget->setStyleSheet(styleSheet);
        qDebug() << "成功为控件应用皮肤:" << skinId;
    } else {
        qWarning() << "Failed to apply skin to widget:" << skinId;
    }
}

void SkinSystemUsage::cleanupSkinSystem()
{
    SkinManager::destroyInstance();
    qDebug() << "皮肤系统清理完成";
}

void SkinSystemUsage::switchToLightTheme()
{
    SkinManager::instance()->applySkin("default");
}

void SkinSystemUsage::switchToDarkTheme()
{
    SkinManager::instance()->applySkin("dark");
}

void SkinSystemUsage::switchToCustomTheme(const QString &skinId)
{
    if (isSkinAvailable(skinId)) {
        SkinManager::instance()->applySkin(skinId);
    } else {
        qWarning() << "Skin not available:" << skinId;
    }
}

QString SkinSystemUsage::getCurrentSkinId()
{
    return SkinManager::instance()->currentSkinId();
}

QStringList SkinSystemUsage::getAvailableSkins()
{
    return SkinManager::instance()->availableSkins();
}

bool SkinSystemUsage::isSkinAvailable(const QString &skinId)
{
    return SkinManager::instance()->availableSkins().contains(skinId);
}

QString SkinSystemUsage::getIconPath(const QString &iconName)
{
    return SkinManager::instance()->getResourcePath(iconName);
}

QString SkinSystemUsage::getStylePath(const QString &styleFile)
{
    return SkinManager::instance()->getResourcePath(styleFile);
}

void SkinSystemUsage::onSkinChanged(const QString &skinId)
{
    qDebug() << "皮肤已切换:" << skinId;
    emit skinSwitched(skinId);
}

void SkinSystemUsage::onSkinError(const QString &skinId, SkinError error)
{
    QString errorMsg = SkinManager::instance()->getErrorString(error);
    qWarning() << "皮肤加载错误:" << skinId << errorMsg;
    emit skinLoadFailed(skinId, errorMsg);
} 