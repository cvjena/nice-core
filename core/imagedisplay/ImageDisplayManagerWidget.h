#ifndef IMAGEDISPLAYMANAGERWIDGET_H
#define IMAGEDISPLAYMANAGERWIDGET_H

#include <qvariant.h>
#include <qwidget.h>
//Added by qt3to4:
#include <Q3GridLayout>
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>

class Q3VBoxLayout;
class Q3HBoxLayout;
class Q3GridLayout;
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
    Q3VBoxLayout* ImageDisplayManagerWidgetLayout;

protected slots:
    virtual void languageChange();

};

#endif // IMAGEDISPLAYMANAGERWIDGET_H
