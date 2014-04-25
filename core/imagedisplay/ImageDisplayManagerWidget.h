#ifndef IMAGEDISPLAYMANAGERWIDGET_H
#define IMAGEDISPLAYMANAGERWIDGET_H

#include <qvariant.h>
#include <qwidget.h>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

class QSpacerItem;
class QPushButton;

class ImageDisplayManagerWidget : public QWidget
{
    Q_OBJECT

public:
    ImageDisplayManagerWidget( QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );
    ~ImageDisplayManagerWidget();

    QPushButton* buttonShowAll;
    QPushButton* buttonHideAll;
    QPushButton* buttonDeleteAll;

public slots:
    virtual void buttonShowAll_clicked();
    virtual void buttonHideAll_clicked();
    virtual void buttonDeleteAll_clicked();

protected:
    QVBoxLayout* ImageDisplayManagerWidgetLayout;

protected slots:
    virtual void languageChange();

};

#endif // IMAGEDISPLAYMANAGERWIDGET_H
