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

private:
    int getCurrentTimeInterval() const;

signals:
    void updateProviderTimerInterval(int interval);

private slots:
   void onProviderPositionUpdated(const QGeoPositionInfo &info);
   void onProviderStatusUpdated(const QString &message);

   void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    GPSPositionProvider mProvider;
};

#endif // MAINWINDOW_H
