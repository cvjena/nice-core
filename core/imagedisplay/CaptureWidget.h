#ifndef CAPTUREWIDGET_IMAGEDISPLAY_H
#define CAPTUREWIDGET_IMAGEDISPLAY_H

#include <qvariant.h>
#include <qdialog.h>
#include <q3filedialog.h>
//Added by qt3to4:
#include <Q3VBoxLayout>
#include <Q3GridLayout>
#include <Q3HBoxLayout>
#include <QLabel>
#include <memory>

class Q3VBoxLayout;
class Q3HBoxLayout;
class Q3GridLayout;
class QSpacerItem;
class Q3ButtonGroup;
class QRadioButton;
class QPushButton;
class QCheckBox;
class QLabel;
class QLineEdit;
class QComboBox;

namespace NICE {

class CaptureWidget : public QWidget {
Q_OBJECT
public:
  CaptureWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );
  ~CaptureWidget();

  std::string directoryName();
  std::string extensionName();
  bool isBuffered();
  bool isCapturing();

  void showCancelButton();

  void setDirectoryName(const std::string& dir);
  void setExtensionName(const std::string& ext);
  void setBuffered(bool buffer);

signals:
  void started();
  void stopped();
  void cancelled();

public slots:
  virtual void buttonBrowseClicked();
  virtual void buttonStartClicked();
  virtual void buttonStopClicked();

protected:
  Q3VBoxLayout* CaptureWidgetLayout;
  Q3HBoxLayout* layout15;
//   QVBoxLayout* layout14;
  QSpacerItem* spacer5;
  Q3HBoxLayout* layout11;

//   QButtonGroup* boxFormat;
//   QRadioButton* radioPPM;
//   QRadioButton* radioJPG;
//   QRadioButton* radioPGM;
//   QRadioButton* radioPNG;
  QPushButton* buttonStart;
  QPushButton* buttonStop;
  QPushButton* buttonCancel;
  QCheckBox* checkBuffered;
  QLabel* textLabel1;
  QLabel* textLabel2;
  QLineEdit* editDirectory;
  QComboBox* editFormat;
  QPushButton* buttonBrowse;

protected slots:
  virtual void languageChange();

private:
  void enableGUI(bool enable);
};

}

#endif // CAPTUREWIDGET_IMAGEDISPLAY_H
