#include "CaptureWidget.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <q3buttongroup.h>
#include <qradiobutton.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <q3whatsthis.h>
#include <qcombobox.h>
//Added by qt3to4:
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>

namespace NICE {

CaptureWidget::CaptureWidget(QWidget* parent, const char* name, Qt::WFlags fl)
        : QWidget(parent, name, fl) {
    if (name == NULL) {
      setName("CaptureWidget");
    }
    //setSizeGripEnabled( TRUE );
    CaptureWidgetLayout = new Q3VBoxLayout( this, 11, 6, "CaptureWidgetLayout");

    layout15 = new Q3HBoxLayout( 0, 0, 6, "layout15");

    textLabel1 = new QLabel( this, "textLabel1" );
    layout15->addWidget( textLabel1 );

    editFormat = new QComboBox( true, this, "editFormat" );
    editFormat->insertItem("ppm");
    editFormat->insertItem("pgm");
    editFormat->insertItem("png");
    editFormat->insertItem("jpg");
    QToolTip::add(editFormat,
                  "Format specified by filename extension (without dot)");
    layout15->addWidget( editFormat );

    checkBuffered = new QCheckBox( this, "checkBuffered" );
    QToolTip::add(checkBuffered,
                  "Buffer images in memory and write after capturing (stop)");
    layout15->addWidget( checkBuffered );

    buttonStart = new QPushButton( this, "buttonStart" );
    layout15->addWidget( buttonStart );

    buttonStop = new QPushButton( this, "buttonStop" );
    buttonStop->setEnabled( FALSE );
    layout15->addWidget( buttonStop );

    buttonCancel = new QPushButton( this, "buttonCancel" );
    buttonCancel->setAutoDefault( TRUE );
    buttonCancel->hide();
    layout15->addWidget( buttonCancel );
    //spacer5 = new QSpacerItem( 20, 44, QSizePolicy::Minimum, QSizePolicy::Expanding );
    //layout15->addItem( spacer5 );



//     layout15 = new QHBoxLayout( 0, 0, 6, "layout15");
//
//     boxFormat = new QButtonGroup( this, "boxFormat" );
//     //boxFormat->setInsideMargin(0);
//     //boxFormat->setInsideSpacing(2);
//
//     radioPPM = new QRadioButton( boxFormat, "radioPPM" );
//     radioPPM->setGeometry( QRect( 11, 26, 267, 25 ) );
//     radioPPM->setChecked( TRUE );
//
//     radioJPG = new QRadioButton( boxFormat, "radioJPG" );
//     radioJPG->setGeometry( QRect( 11, 119, 267, 25 ) );
//
//     radioPGM = new QRadioButton( boxFormat, "radioPGM" );
//     radioPGM->setGeometry( QRect( 11, 57, 267, 25 ) );
//
//     radioPNG = new QRadioButton( boxFormat, "radioPNG" );
//     radioPNG->setGeometry( QRect( 11, 88, 267, 25 ) );
//     layout15->addWidget( boxFormat );
//
//     layout14 = new QVBoxLayout( 0, 0, 6, "layout14");
//
//     buttonStart = new QPushButton( this, "buttonStart" );
//     layout14->addWidget( buttonStart );
//
//     buttonStop = new QPushButton( this, "buttonStop" );
//     buttonStop->setEnabled( FALSE );
//     layout14->addWidget( buttonStop );
//
//     buttonCancel = new QPushButton( this, "buttonCancel" );
//     buttonCancel->setAutoDefault( TRUE );
//     buttonCancel->hide();
//     layout14->addWidget( buttonCancel );
//     spacer5 = new QSpacerItem( 20, 44, QSizePolicy::Minimum, QSizePolicy::Expanding );
//     layout14->addItem( spacer5 );
//
//     checkBuffered = new QCheckBox( this, "checkBuffered" );
//     layout14->addWidget( checkBuffered );
//     layout15->addLayout( layout14 );

    CaptureWidgetLayout->addLayout( layout15 );

    layout11 = new Q3HBoxLayout( 0, 0, 6, "layout11");

    textLabel2 = new QLabel( this, "textLabel2" );
    layout11->addWidget( textLabel2 );

    editDirectory = new QLineEdit( this, "editDirectory" );
    layout11->addWidget( editDirectory );

    buttonBrowse = new QPushButton( this, "buttonBrowse" );
    layout11->addWidget( buttonBrowse );
    CaptureWidgetLayout->addLayout( layout11 );

    buttonBrowse->setFlat(true);
    QSize size = buttonBrowse->size();
    size.setHeight(editDirectory->size().height() - 5);
    size.setWidth(20);//buttonBrowse->size().width() - 20);
    buttonBrowse->setMaximumSize(size);
    buttonBrowse->setMinimumSize(size);
    buttonBrowse->resize(size);

    languageChange();
    resize( QSize(542, 253).expandedTo(minimumSizeHint()) );
//     clearWState( WState_Polished ); // Qt4

    // signals and slots connections
//     connect(buttonCancel, SIGNAL(clicked()),
//             this, SLOT(buttonCancelClicked()));
    connect(buttonCancel, SIGNAL(clicked()),
            this, SIGNAL(cancelled()));
    connect(buttonBrowse, SIGNAL(clicked()),
            this, SLOT(buttonBrowseClicked()));
    connect(buttonStart, SIGNAL(clicked()),
            this, SLOT(buttonStartClicked()));
    connect(buttonStop, SIGNAL(clicked()),
            this, SLOT(buttonStopClicked()));
}

void CaptureWidget::showCancelButton() {
  buttonCancel->show();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CaptureWidget::~CaptureWidget()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CaptureWidget::languageChange()
{
    setCaption( tr( "Capture Image Sequence" ) );
//     boxFormat->setTitle( tr( "Image file format" ) );
//     radioPPM->setText( tr( "PPM" ) );
//     radioJPG->setText( tr( "JPEG" ) );
//     radioPGM->setText( tr( "PGM (gray)" ) );
//     radioPNG->setText( tr( "PNG" ) );
    buttonStart->setText( tr( "Start" ) );
    buttonStop->setText( tr( "Stop" ) );
    buttonCancel->setText( tr( "&Cancel" ) );
    buttonCancel->setAccel( QKeySequence( QString::null ) );
    checkBuffered->setText( tr( "Buffer" ) );
    textLabel1->setText( tr( "Format" ) );
    textLabel2->setText( tr( "Directory" ) );
    buttonBrowse->setText( tr( "..." ) );
}

#include <q3filedialog.h>

void CaptureWidget::buttonBrowseClicked()
{
  Q3FileDialog dialog("",
                     "",
                     this,
                     "Save to directory dialog");
  dialog.setCaption("Choose an output directory");
  dialog.setMode(Q3FileDialog::AnyFile); // QFileDialog::DirectoryOnly
  if (dialog.exec() == QDialog::Accepted) {
    editDirectory->setText(dialog.selectedFile());
  }
}

void CaptureWidget::buttonStartClicked()
{
  if (!isCapturing()) {
    if (directoryName().size() == 0) {
      return;
    }
    enableGUI(false);
    emit(started());
  }
}

void CaptureWidget::buttonStopClicked()
{
  if (isCapturing()) {
    enableGUI(true);
    emit(stopped());
  }
}

void CaptureWidget::enableGUI(bool enable)
{
  const bool value = enable;
  buttonStart->setEnabled(value);
  buttonCancel->setEnabled(value);
  editDirectory->setEnabled(value);
  buttonBrowse->setEnabled(value);
  checkBuffered->setEnabled(value);
//   boxFormat->setEnabled(value);
  buttonStop->setEnabled(!value);
}

std::string CaptureWidget::directoryName()
{
  return std::string(editDirectory->text().local8Bit());
}

bool CaptureWidget::isBuffered() {
  return checkBuffered->isChecked();
}


std::string CaptureWidget::extensionName()
{
//   if (radioPPM->isChecked()) {
//     return ".ppm";
//   } else if (radioPGM->isChecked()) {
//     return ".pgm";
//   } else if (radioPNG->isChecked()) {
//     return ".png";
//   } else if (radioJPG->isChecked()) {
//     return ".jpg";
//   } else {
//     return ".ppm";
//   }
  return "." + std::string(editFormat->currentText().local8Bit());
}

bool CaptureWidget::isCapturing() {
  return buttonStop->isEnabled();
}

void CaptureWidget::setDirectoryName(const std::string& dir) {
  editDirectory->setText(dir.c_str());
}

void CaptureWidget::setExtensionName(const std::string& ext) {
  editFormat->setCurrentText(ext.c_str());
}

void CaptureWidget::setBuffered(bool buffer) {
  checkBuffered->setChecked(buffer);
}

}
