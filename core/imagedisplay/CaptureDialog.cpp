#include "CaptureDialog.h"

#include <qlayout.h>
#include <QVBoxLayout>

namespace NICE {

CaptureDialog::CaptureDialog(QWidget* parent, const char* name, 
                             bool modal, Qt::WFlags fl)
    : QDialog( parent, fl ) {
  if (name == NULL) {
    setWindowTitle("CaptureDialog");
  }
  
  QVBoxLayout* layout = new QVBoxLayout( this ); 
  
  m_capture = new CaptureWidget(this);
  m_capture->showCancelButton();
  layout->addWidget(m_capture);
  connect(m_capture, SIGNAL(cancelled()), this, SLOT(reject()));
}  

CaptureDialog::~CaptureDialog() {
}

}
