#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , m_url()
    , m_client(nullptr)
{
    ui->setupUi(this);

    m_prober = new OfficeProber;
    m_prober->killSOfficeBin();

    m_refreshTimer = new QTimer(this);
    connect(m_refreshTimer, &QTimer::timeout, this, &Widget::refreshUI);
    m_refreshTimer->start(100);
}

Widget::~Widget()
{
    delete ui;

    if (m_prober)
        m_prober->killSOfficeBin();
    delete m_prober;

    delete m_client;
}

void Widget::setOfficeProberUI()
{
    if (m_prober != nullptr)
    {
        int64_t ullSOfficeBinPid = m_prober->getSOfficeBinPid();
        if (ullSOfficeBinPid != 0)
            ui->lineEdit_sOfficeBinPid->setText(QString::number(ullSOfficeBinPid));
        else
            ui->lineEdit_sOfficeBinPid->setText("Not Available");

        int64_t ullSOfficeExePid = m_prober->getSOfficeExePid();
        if (ullSOfficeExePid != 0)
            ui->lineEdit_sOfficeExePid->setText(QString::number(ullSOfficeExePid));
        else
            ui->lineEdit_sOfficeExePid->setText("Not Available");
    }
}

void Widget::setConnectionUI()
{
    if (m_client != nullptr && m_client->isAlive())
    {
        ui->lineEdit_connectionState->setText("Alive");
    }
    else
    {
        ui->lineEdit_connectionState->setText("Not Alive");
    }
}

void Widget::setPresentationUI()
{
    if (m_client != nullptr && m_client->isAlive() && m_client->isPresentationAvailable())
    {
        ui->lineEdit_isPresentationAvailable->setText("Available");
        ui->lineEdit_currentDocumentURL->setText(m_url);
    }
    else
    {
        ui->lineEdit_isPresentationAvailable->setText("Not Available");
        m_url = "Null";
        ui->lineEdit_currentDocumentURL->setText(m_url);
    }
}

void Widget::setConfigurationUI()
{
    if (m_client == nullptr ||
        !m_client->isAlive() ||
        !m_client->isPresentationAvailable())
    {
        ui->checkBox_setFullScreen->setEnabled(false);
        ui->checkBox_setEndless->setEnabled(false);
    }
    else
    {
        if (m_client->isRunning())
        {
            ui->checkBox_setFullScreen->setEnabled(false);
            ui->checkBox_setEndless->setEnabled(false);
        }
        else
        {
            ui->checkBox_setFullScreen->setEnabled(true);
            ui->checkBox_setEndless->setEnabled(true);
        }
    }
}

void Widget::setSlideShowUI()
{
    if (m_client != nullptr &&
        m_client->isAlive() &&
        m_client->isPresentationAvailable() &&
        m_client->isRunning())
    {
        ui->lineEdit_isSlideShowRunning->setText("Running");
        int count = m_client->getSlideCount();
        if (count >= 0)
            ui->lineEdit_slideCount->setText(QString::number(count));
    }
    else
    {
        ui->lineEdit_isSlideShowRunning->setText("Not running");
        ui->lineEdit_slideCount->setText("Not Available");
    }
}

void Widget::refreshUI()
{
    setOfficeProberUI();
    setConnectionUI();
    setPresentationUI();
    setConfigurationUI();
    setSlideShowUI();
}
