#include <QFileDialog>
#include <QStandardPaths>

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


void Widget::on_pushButton_killSOfficeBin_clicked()
{
    ui->plainTextEdit_log->appendPlainText("Try to kill soffice.bin");
    m_prober->killSOfficeBin();
}

void Widget::on_pushButton_connect_clicked()
{
    m_client = new OfficeClient;

    if (m_client->connect())
    {
        ui->plainTextEdit_log->appendPlainText("Connected to the soffice.bin");
    }
    else
    {
        delete m_client;
        m_client = nullptr;
    }
}

void Widget::on_pushButton_disconnect_clicked()
{
    ui->plainTextEdit_log->appendPlainText("Release ref and close the connection");

    delete m_client;
    m_client = nullptr;
}

void Widget::on_pushButton_loadPresentation_clicked()
{
    if (m_client == nullptr)
        return;

    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setWindowTitle(tr("Open Files"));
    fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).value(0, QDir::homePath()));
    if (fileDialog.exec() == QDialog::Accepted)
    {
        auto selectedUrls = fileDialog.selectedUrls();
        ui->plainTextEdit_log->appendPlainText("Selected URL " + selectedUrls.front().toString());
        if (m_client->loadPresentation(selectedUrls.front().toString().toStdString().c_str()))
        {
            ui->plainTextEdit_log->appendPlainText("Document " + selectedUrls.front().toString() + " has been loaded");
        }
        else
        {
            ui->plainTextEdit_log->appendPlainText("Failed to load " + selectedUrls.front().toString());
        }

        m_url = selectedUrls.front().toString();

        bool isFullScreen;
        if (m_client->getFullScreen(isFullScreen))
        {
            if (isFullScreen)
            {
                ui->plainTextEdit_log->appendPlainText("Slideshow will start in full screen mode");
                ui->checkBox_setFullScreen->setChecked(true);
            }
            else
            {
                ui->plainTextEdit_log->appendPlainText("Slideshow will start in window mode");
                ui->checkBox_setFullScreen->setChecked(false);
            }
            ui->checkBox_setFullScreen->setEnabled(true);
        }

        bool isEndless;
        if (m_client->getEndless(isEndless))
        {
            if (isEndless)
            {
                ui->plainTextEdit_log->appendPlainText("Slideshow will play endless");
                ui->checkBox_setEndless->setChecked(true);
            }
            else
            {
                ui->plainTextEdit_log->appendPlainText("Slideshow will not play endless");
                ui->checkBox_setEndless->setChecked(false);
            }
            ui->checkBox_setEndless->setEnabled(true);
        }
    }
}

void Widget::on_pushButton_closePresentation_clicked()
{
    if (m_client == nullptr)
        return;

    m_client->closePresentation();
}

void Widget::on_pushButton_start_clicked()
{
    if (m_client == nullptr)
        return;

    if (m_client->start())
    {
        ui->plainTextEdit_log->appendPlainText("Start slide show.");
    }
    else
    {
        ui->plainTextEdit_log->appendPlainText("Failed to start slide show.");
    }
}

void Widget::on_pushButton_end_clicked()
{
    if (m_client == nullptr)
        return;

    if (m_client->end())
    {
        ui->plainTextEdit_log->appendPlainText("End slide show.");
        ui->checkBox_setFullScreen->setEnabled(true);
    }
    else
    {
        ui->plainTextEdit_log->appendPlainText("Failed to end slide show.");
    }
}

void Widget::on_pushButton_gotoNextEffect_clicked()
{
    if (m_client == nullptr)
        return;

    if (m_client->gotoNextEffect())
    {
        ui->plainTextEdit_log->appendPlainText("gotoNextEffect.");
    }
    else
    {
        ui->plainTextEdit_log->appendPlainText("gotoNextEffect failed.");
    }
}

void Widget::on_pushButton_gotoPreviousEffect_clicked()
{
    if (m_client == nullptr)
        return;

    if (m_client->gotoPreviousEffect())
    {
        ui->plainTextEdit_log->appendPlainText("gotoPreviousEffect.");
    }
    else
    {
        ui->plainTextEdit_log->appendPlainText("gotoPreviousEffect failed.");
    }
}

void Widget::on_pushButton_gotoNextSlide_clicked()
{
    if (m_client == nullptr)
        return;

    if (m_client->gotoNextSlide())
    {
        ui->plainTextEdit_log->appendPlainText("gotoNextSlide.");
    }
    else
    {
        ui->plainTextEdit_log->appendPlainText("gotoNextSlide failed.");
    }
}

void Widget::on_pushButton_gotoPreviousSlide_clicked()
{
    if (m_client == nullptr)
        return;

    if (m_client->gotoPreviousSlide())
    {
        ui->plainTextEdit_log->appendPlainText("gotoPreviousSlide.");
    }
    else
    {
        ui->plainTextEdit_log->appendPlainText("gotoPreviousSlide failed.");
    }
}

void Widget::on_pushButton_gotoFirstSlide_clicked()
{
    if (m_client == nullptr)
        return;

    if (m_client->gotoFirstSlide())
    {
        ui->plainTextEdit_log->appendPlainText("gotoFirstSlide.");
    }
    else
    {
        ui->plainTextEdit_log->appendPlainText("gotoFirstSlide failed.");
    }
}

void Widget::on_pushButton_gotoLastSlide_clicked()
{
    if (m_client == nullptr)
        return;

    if (m_client->gotoLastSlide())
    {
        ui->plainTextEdit_log->appendPlainText("gotoLastSlide.");
    }
    else
    {
        ui->plainTextEdit_log->appendPlainText("gotoLastSlide failed.");
    }
}

void Widget::on_checkBox_setFullScreen_stateChanged(int arg1)
{
    if (m_client == nullptr)
        return;

    if (arg1)
    {
        ui->plainTextEdit_log->appendPlainText("Selected full screen mode");
        if (m_client->setFullScreen(true))
        {
            ui->plainTextEdit_log->appendPlainText("Slideshow will start in full screen mode");
        }
        else
        {
            ui->plainTextEdit_log->appendPlainText("Failed to use full screen mode");
        }
    }
    else
    {
        ui->plainTextEdit_log->appendPlainText("Selected window mode");
        if (m_client->setFullScreen(false))
        {
            ui->plainTextEdit_log->appendPlainText("Slideshow will start in window mode");
        }
        else
        {
            ui->plainTextEdit_log->appendPlainText("Failed to use window mode");
        }
    }
}

void Widget::on_checkBox_setEndless_stateChanged(int arg1)
{
    if (m_client == nullptr)
        return;

    if (arg1)
    {
        ui->plainTextEdit_log->appendPlainText("Selected endless mode");
        if (m_client->setEndless(true))
        {
            ui->plainTextEdit_log->appendPlainText("Slideshow will play endless");
        }
        else
        {
            ui->plainTextEdit_log->appendPlainText("Failed to use endless mode");
        }
    }
    else
    {
        ui->plainTextEdit_log->appendPlainText("Selected non-endless mode");
        if (m_client->setEndless(false))
        {
            ui->plainTextEdit_log->appendPlainText("Slideshow will start in non-endless mode");
        }
        else
        {
            ui->plainTextEdit_log->appendPlainText("Failed to use non-endless mode");
        }
    }
}

void Widget::on_pushButton_convertToPDF_clicked()
{
    if (m_client == nullptr || !m_client->isAlive() || !m_client->isPresentationAvailable())
        return;

    QUrl fileURL = QFileDialog::getSaveFileUrl(this, tr("Export PDF As"));
    m_client->convertToPDF(fileURL.toString().toStdString().c_str());

    ui->plainTextEdit_log->appendPlainText("Export PDF file as " + fileURL.toString());
}