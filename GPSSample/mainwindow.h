#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gpspositionprovider.h"

class QGeoPositionInfo;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void init();

private:
    void initSpinBox();
    void initComboBox();
    void setDefaultValues();
    void connectSlots();
    void initProvider();

private:
    int getCurrentTimeInterval() const;

private slots:
   void onProviderPositionUpdated(const QGeoPositionInfo &info);
   void onProviderStatusUpdated(const QString &message);

   void on_pushButton_clicked();
   void on_allRadioButton_toggled(bool checked);
   void on_satelliteRadioButton_toggled(bool checked);
   void on_nonSatelliteradioButton_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    GPSPositionProvider mProvider;
};

#endif // MAINWINDOW_H
