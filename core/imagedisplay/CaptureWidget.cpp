#include "CaptureWidget.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qcombobox.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>

namespace NICE {

CaptureWidget::CaptureWidget(QWidget* parent, const char* name, Qt::WFlags fl)
        : QWidget(parent, fl) {
    CaptureWidgetLayout = new QVBoxLayout( this );

    layout15 = new QHBoxLayout( );

    textLabel1 = new QLabel( this );
    layout15->addWidget( textLabel1 );

    editFormat = new QComboBox( this );
    editFormat->addItem("ppm");
    editFormat->addItem("pgm");
    editFormat->addItem("png");
    editFormat->addItem("jpg");
    editFormat->setToolTip("Format specified by filename extension (without dot)");
    layout15->addWidget( editFormat );

    checkBuffered = new QCheckBox( this );
    checkBuffered->setToolTip( "Buffer images in memory and write after capturing (stop)");
    layout15->addWidget( checkBuffered );

    buttonStart = new QPushButton( this );
    layout15->addWidget( buttonStart );

    buttonStop = new QPushButton( this );
    buttonStop->setEnabled( FALSE );
    layout15->addWidget( buttonStop );

    buttonCancel = new QPushButton( this );
    buttonCancel->setAutoDefault( TRUE );
    buttonCancel->hide();
    layout15->addWidget( buttonCancel );
    
    CaptureWidgetLayout->addLayout( layout15 );

    layout11 = new QHBoxLayout();

    textLabel2 = new QLabel( this );
    layout11->addWidget( textLabel2 );

    editDirectory = new QLineEdit( this );
    layout11->addWidget( editDirectory );

    buttonBrowse = new QPushButton( this );
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
    setWindowTitle( tr( "Capture Image Sequence" ) );
    buttonStart->setText( tr( "Start" ) );
    buttonStop->setText( tr( "Stop" ) );
    buttonCancel->setText( tr( "&Cancel" ) );
    buttonCancel->setShortcut( QKeySequence( QString::null ) );
    checkBuffered->setText( tr( "Buffer" ) );
    textLabel1->setText( tr( "Format" ) );
    textLabel2->setText( tr( "Directory" ) );
    buttonBrowse->setText( tr( "..." ) );
}

void CaptureWidget::buttonBrowseClicked()
{
/*
  QFileDialog dialog( this );
  dialog.setWindowTitle("Choose an output directory");
  dialog.setMode(QFileDialog::AnyFile); 
  if (dialog.exec() == QDialog::Accepted) {
    editDirectory->setText(dialog.selectedFile());
  }
*/
  QString directory = QFileDialog::getExistingDirectory(this);
  if(!directory.isNull()) {
    editDirectory->setText(directory);
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
  buttonStop->setEnabled(!value);
}

std::string CaptureWidget::directoryName()
{
  return std::string(editDirectory->text().toLocal8Bit());
}

bool CaptureWidget::isBuffered() {
  return checkBuffered->isChecked();
}


std::string CaptureWidget::extensionName()
{
  return "." + std::string(editFormat->currentText().toLocal8Bit());
}

bool CaptureWidget::isCapturing() {
  return buttonStop->isEnabled();
}

void CaptureWidget::setDirectoryName(const std::string& dir) {
  editDirectory->setText(dir.c_str());
}

void CaptureWidget::setExtensionName(const std::string& ext) {
  std::string extension_end = ext.substr(1);
  int extension_index = editFormat->findText(extension_end.c_str());
  if(extension_index > 0) {
    editFormat->addItem(extension_end.c_str());
  } 

  editFormat->setCurrentIndex(extension_index);
}

void CaptureWidget::setBuffered(bool buffer) {
  checkBuffered->setChecked(buffer);
}

}
