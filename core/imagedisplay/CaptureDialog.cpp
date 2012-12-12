#include "CaptureDialog.h"

#include <qlayout.h>
//Added by qt3to4:
#include <Q3VBoxLayout>

namespace NICE {

CaptureDialog::CaptureDialog(QWidget* parent, const char* name, 
                             bool modal, Qt::WFlags fl)
    : QDialog( parent, name, modal, fl ) {
  if (name == NULL) {
    setName("CaptureDialog");
  }
  
  Q3VBoxLayout* layout = new Q3VBoxLayout( this, 11, 6, "layout"); 
  
  m_capture = new CaptureWidget(this);
  m_capture->showCancelButton();
  layout->addWidget(m_capture);
  connect(m_capture, SIGNAL(cancelled()), this, SLOT(reject()));
}  

CaptureDialog::~CaptureDialog() {
}

}
