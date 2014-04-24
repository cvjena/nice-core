#ifndef CAPTUREWIDGET_IMAGEDISPLAY_H
#define CAPTUREWIDGET_IMAGEDISPLAY_H

#include <qvariant.h>
#include <qdialog.h>
#include <QFileDialog>
#include <QLabel>
#include <memory>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
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
  QVBoxLayout* CaptureWidgetLayout;
  QHBoxLayout* layout15;
//   QVBoxLayout* layout14;
  QSpacerItem* spacer5;
  QHBoxLayout* layout11;

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
