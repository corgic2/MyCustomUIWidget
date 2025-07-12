// 这是一个使用示例文件，演示如何使用SkinManager
#include "SkinManager.h"
#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QWidget>

class SkinTestWidget : public QWidget
{
    Q_OBJECT

public:
    SkinTestWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
        setupUI();
        connectSignals();
        updateSkinList();
    }

private slots:
    void onSkinChanged(const QString &skinId)
    {
        m_currentSkinLabel->setText(QString("Current Skin: %1").arg(skinId));
    }

    void onSkinComboChanged(const QString &skinId)
    {
        SkinManager::instance()->applySkin(skinId);
    }

    void onRefreshSkins()
    {
        updateSkinList();
    }

private:
    void setupUI()
    {
        QVBoxLayout *layout = new QVBoxLayout(this);
        
        m_currentSkinLabel = new QLabel("Current Skin: default");
        layout->addWidget(m_currentSkinLabel);
        
        m_skinCombo = new QComboBox();
        layout->addWidget(m_skinCombo);
        
        m_refreshButton = new QPushButton("Refresh Skins");
        layout->addWidget(m_refreshButton);
        
        m_testButton = new QPushButton("Test Button");
        layout->addWidget(m_testButton);
        
        setLayout(layout);
    }

    void connectSignals()
    {
        connect(SkinManager::instance(), &SkinManager::skinChanged,
                this, &SkinTestWidget::onSkinChanged);
        connect(m_skinCombo, QOverload<const QString &>::of(&QComboBox::currentTextChanged),
                this, &SkinTestWidget::onSkinComboChanged);
        connect(m_refreshButton, &QPushButton::clicked,
                this, &SkinTestWidget::onRefreshSkins);
    }

    void updateSkinList()
    {
        m_skinCombo->clear();
        m_skinCombo->addItems(SkinManager::instance()->availableSkins());
        m_skinCombo->setCurrentText(SkinManager::instance()->currentSkinId());
    }

private:
    QLabel *m_currentSkinLabel;
    QComboBox *m_skinCombo;
    QPushButton *m_refreshButton;
    QPushButton *m_testButton;
};

#include "SkinManagerExample.moc" 