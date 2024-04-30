#ifndef WIDGET_H
#define WIDGET_H

#include <QTimer>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

#include "officeclient.h"
#include "officeprober.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    void setOfficeProberUI();
    void setConnectionUI();
    void setPresentationUI();
    void setConfigurationUI();
    void setSlideShowUI();

private slots:
    void refreshUI();
    void on_pushButton_killSOfficeBin_clicked();
    void on_pushButton_connect_clicked();
    void on_pushButton_disconnect_clicked();
    void on_pushButton_loadPresentation_clicked();
    void on_pushButton_closePresentation_clicked();
    void on_pushButton_start_clicked();
    void on_pushButton_end_clicked();
    void on_checkBox_setFullScreen_stateChanged(int arg1);
    void on_checkBox_setEndless_stateChanged(int arg1);
    void on_pushButton_gotoNextEffect_clicked();
    void on_pushButton_gotoPreviousEffect_clicked();
    void on_pushButton_gotoNextSlide_clicked();
    void on_pushButton_gotoPreviousSlide_clicked();
    void on_pushButton_gotoFirstSlide_clicked();
    void on_pushButton_gotoLastSlide_clicked();
    void on_pushButton_convertToPDF_clicked();

private:
    Ui::Widget*     ui;
    QString         m_url;
    QTimer*         m_refreshTimer;
    OfficeProber*   m_prober;
    OfficeClient*   m_client;
};

#endif // WIDGET_H
