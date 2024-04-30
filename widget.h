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
 
private:
    Ui::Widget*     ui;
    QString         m_url;
    QTimer*         m_refreshTimer;
    OfficeProber*   m_prober;
    OfficeClient*   m_client;
};

#endif // WIDGET_H
