#include "SkinManager.h"
#include "SkinSystemUsage.h"
#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QGroupBox>
#include <QWidget>
#include <QDebug>

class StyleSystemTestWidget : public QWidget
{
    Q_OBJECT

public:
    StyleSystemTestWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
        setWindowTitle("皮肤系统测试");
        setMinimumSize(450, 350);
        setupUI();
        connectSignals();
        updateSkinList();
    }

private slots:
    void onSkinChanged(const QString &skinId)
    {
        m_currentSkinLabel->setText(QString("当前皮肤: %1").arg(skinId));
        qDebug() << "皮肤已切换到:" << skinId;
    }

    void onSkinComboChanged(const QString &skinId)
    {
        if (SkinManager::instance()->applySkin(skinId)) {
            qDebug() << "成功应用皮肤:" << skinId;
        } else {
            qDebug() << "应用皮肤失败:" << skinId;
        }
    }

    void onRefreshSkins()
    {
        updateSkinList();
    }

    void onTestButtonClicked()
    {
        int currentValue = m_progressBar->value();
        m_progressBar->setValue((currentValue + 10) % 101);
    }

    void onDefaultSkinClicked()
    {
        SkinSystemUsage::switchToLightTheme();
    }

    void onDarkSkinClicked()
    {
        SkinSystemUsage::switchToDarkTheme();
    }

private:
    void setupUI()
    {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        
        // 当前皮肤标签
        m_currentSkinLabel = new QLabel("当前皮肤: default");
        m_currentSkinLabel->setStyleSheet("font-weight: bold; font-size: 14px;");
        mainLayout->addWidget(m_currentSkinLabel);
        
        // 皮肤选择组
        QGroupBox *skinGroup = new QGroupBox("皮肤选择");
        QVBoxLayout *skinLayout = new QVBoxLayout(skinGroup);
        
        // 下拉选择
        QHBoxLayout *comboLayout = new QHBoxLayout();
        comboLayout->addWidget(new QLabel("选择皮肤:"));
        m_skinCombo = new QComboBox();
        comboLayout->addWidget(m_skinCombo);
        m_refreshButton = new QPushButton("刷新");
        comboLayout->addWidget(m_refreshButton);
        skinLayout->addLayout(comboLayout);
        
        // 快速切换按钮
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        m_defaultButton = new QPushButton("默认主题");
        m_darkButton = new QPushButton("深色主题");
        buttonLayout->addWidget(m_defaultButton);
        buttonLayout->addWidget(m_darkButton);
        skinLayout->addLayout(buttonLayout);
        
        mainLayout->addWidget(skinGroup);
        
        // 测试控件组
        QGroupBox *testGroup = new QGroupBox("测试控件");
        QVBoxLayout *testLayout = new QVBoxLayout(testGroup);
        
        m_testLineEdit = new QLineEdit("测试文本输入");
        testLayout->addWidget(m_testLineEdit);
        
        m_testButton = new QPushButton("测试按钮");
        testLayout->addWidget(m_testButton);
        
        m_progressBar = new QProgressBar();
        m_progressBar->setValue(50);
        testLayout->addWidget(m_progressBar);
        
        mainLayout->addWidget(testGroup);
        
        // 状态信息
        QGroupBox *infoGroup = new QGroupBox("状态信息");
        QVBoxLayout *infoLayout = new QVBoxLayout(infoGroup);
        
        m_skinCountLabel = new QLabel("可用皮肤: 0");
        infoLayout->addWidget(m_skinCountLabel);
        
        mainLayout->addWidget(infoGroup);
        
        // 添加弹性空间
        mainLayout->addStretch();
        
        setLayout(mainLayout);
    }

    void connectSignals()
    {
        connect(SkinManager::instance(), &SkinManager::skinChanged,
                this, &StyleSystemTestWidget::onSkinChanged);
        connect(m_skinCombo, QOverload<const QString &>::of(&QComboBox::currentTextChanged),
                this, &StyleSystemTestWidget::onSkinComboChanged);
        connect(m_refreshButton, &QPushButton::clicked,
                this, &StyleSystemTestWidget::onRefreshSkins);
        connect(m_testButton, &QPushButton::clicked,
                this, &StyleSystemTestWidget::onTestButtonClicked);
        connect(m_defaultButton, &QPushButton::clicked,
                this, &StyleSystemTestWidget::onDefaultSkinClicked);
        connect(m_darkButton, &QPushButton::clicked,
                this, &StyleSystemTestWidget::onDarkSkinClicked);
    }

    void updateSkinList()
    {
        m_skinCombo->clear();
        QStringList skins = SkinManager::instance()->availableSkins();
        m_skinCombo->addItems(skins);
        m_skinCombo->setCurrentText(SkinManager::instance()->currentSkinId());
        
        m_skinCountLabel->setText(QString("可用皮肤: %1").arg(skins.size()));
        
        qDebug() << "可用皮肤:" << skins;
    }

private:
    QLabel *m_currentSkinLabel;
    QLabel *m_skinCountLabel;
    QComboBox *m_skinCombo;
    QPushButton *m_refreshButton;
    QPushButton *m_testButton;
    QPushButton *m_defaultButton;
    QPushButton *m_darkButton;
    QLineEdit *m_testLineEdit;
    QProgressBar *m_progressBar;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    qDebug() << "启动皮肤系统测试程序...";
    
    // 初始化皮肤系统
    SkinSystemUsage::initializeSkinSystem(&app);
    
    // 创建测试窗口
    StyleSystemTestWidget window;
    window.show();
    
    int result = app.exec();
    
    // 清理
    SkinSystemUsage::cleanupSkinSystem();
    
    return result;
}

#include "StyleSystemTest.moc" 