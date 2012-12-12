#include "ImageDisplayManagerWidget.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <q3whatsthis.h>
//Added by qt3to4:
#include <Q3VBoxLayout>

/*
 *  Constructs a ImageDisplayManagerWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
ImageDisplayManagerWidget::ImageDisplayManagerWidget( QWidget* parent, const char* name, Qt::WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
  setName( "ImageDisplayManagerWidget" );
    ImageDisplayManagerWidgetLayout = new Q3VBoxLayout( this, 11, 6, "ImageDisplayManagerWidgetLayout");

    buttonShowAll = new QPushButton( this, "buttonShowAll" );
    ImageDisplayManagerWidgetLayout->addWidget( buttonShowAll );

    buttonHideAll = new QPushButton( this, "buttonHideAll" );
    ImageDisplayManagerWidgetLayout->addWidget( buttonHideAll );

    buttonDeleteAll = new QPushButton( this, "buttonDeleteAll" );
    ImageDisplayManagerWidgetLayout->addWidget( buttonDeleteAll );
    languageChange();
    resize( QSize(205, 133).expandedTo(minimumSizeHint()) );
//     clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonShowAll, SIGNAL( clicked() ), this, SLOT( buttonShowAll_clicked() ) );
    connect( buttonHideAll, SIGNAL( clicked() ), this, SLOT( buttonHideAll_clicked() ) );
    connect( buttonDeleteAll, SIGNAL( clicked() ), this, SLOT( buttonDeleteAll_clicked() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
ImageDisplayManagerWidget::~ImageDisplayManagerWidget()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ImageDisplayManagerWidget::languageChange()
{
    setCaption( tr( "Image displays" ) );
    buttonShowAll->setText( tr( "Show all images" ) );
    buttonHideAll->setText( tr( "Hide all images" ) );
    buttonDeleteAll->setText( tr( "Release (!) all images" ) );
}

#include <core/imagedisplay/ImageDisplayManager.h>

void ImageDisplayManagerWidget::buttonShowAll_clicked()
{
  NICE::ImageDisplayManager::instance().showAll();
}


void ImageDisplayManagerWidget::buttonHideAll_clicked()
{
  NICE::ImageDisplayManager::instance().hideAll();
}


void ImageDisplayManagerWidget::buttonDeleteAll_clicked()
{
  NICE::ImageDisplayManager::instance().deleteAll();
}
