#ifndef CAPTUREDIALOG_IMAGEDISPLAY_H
#define CAPTUREDIALOG_IMAGEDISPLAY_H

#include <qdialog.h>
#include <core/imagedisplay/CaptureWidget.h>
#include <memory>

namespace NICE {

class CaptureDialog : public QDialog {
Q_OBJECT
public:
  CaptureDialog(QWidget* parent = 0, const char* name = 0,
                bool modal = FALSE, Qt::WFlags fl = 0 );
  ~CaptureDialog();
  
  inline CaptureWidget* capture() {
    return m_capture;
  }
  
private:
  CaptureWidget* m_capture;
};

}

#endif // CAPTUREDIALOG_IMAGEDISPLAY_H
