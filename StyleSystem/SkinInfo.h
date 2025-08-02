#ifndef SKININFO_H
#define SKININFO_H

#include "StyleSystemGlobal.h"
#include <QObject>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QVariant>

/// <summary>
/// 颜色json存储信息，id，name，author，version，description，colorMap，ResourcesFiles等
/// </summary>
class STYLESYSTEM_EXPORT SkinInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString author READ author WRITE setAuthor NOTIFY authorChanged)
    Q_PROPERTY(QString version READ version WRITE setVersion NOTIFY versionChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)

public:
    explicit SkinInfo(QObject *parent = nullptr);
    explicit SkinInfo(const QString &skinId, QObject *parent = nullptr);
    ~SkinInfo();

    // 基本信息
    QString id() const;
    void setId(const QString &id);

    QString name() const;
    void setName(const QString &name);

    QString author() const;
    void setAuthor(const QString &author);

    QString version() const;
    void setVersion(const QString &version);

    QString description() const;
    void setDescription(const QString &description);

    // 资源路径
    QString resourcePath() const;
    void setResourcePath(const QString &path);

    QString configPath() const;
    void setConfigPath(const QString &path);

    QString stylePath() const;
    void setStylePath(const QString &path);

    // 颜色变量
    QMap<QString, QString> colorVariables() const;
    void setColorVariables(const QMap<QString, QString> &variables);
    void addColorVariable(const QString &name, const QString &value);
    QString getColorVariable(const QString &name) const;

    // 资源文件
    QStringList requiredFiles() const;
    void setRequiredFiles(const QStringList &files);
    void addRequiredFile(const QString &file);

    // 验证
    bool isValid() const;

    // 序列化
    QVariantMap toVariantMap() const;
    bool fromVariantMap(const QVariantMap &map);

signals:
    void idChanged(const QString &id);
    void nameChanged(const QString &name);
    void authorChanged(const QString &author);
    void versionChanged(const QString &version);
    void descriptionChanged(const QString &description);

private:
    QString m_id;
    QString m_name;
    QString m_author;
    QString m_version;
    QString m_description;
    QMap<QString, QString> m_colorVariables;
    QStringList m_requiredFiles;
};

#endif // SKININFO_H