#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>


enum TimeScaleIndex
{
    TSI_MSEC,
    TSI_SEC,
    TSI_MIN,

    TSI_MAX
};

const QString gTimeScaleNames[TSI_MAX] = { "milliseconds", "seconds", "minutes" };
const int gTimeScaleValues[TSI_MAX] = { 1, 1000, 1000*60 };

const int gTimePeriodDefaultValue = 1;
const TimeScaleIndex gTimeScaleDefaultIndex = TSI_SEC;

const int gSpinBoxDefaultMinValue = 0;
const int gSpinBoxDefaultMaxValue = 10000;

const QString &gPositionStatusString = "Position updated:\nDate/time = %1\nCoordinate = %2";


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    initSpinBox();
    initComboBox();
    setDefaultValues();

    connectSlots();
    initProvider();
}

void MainWindow::initSpinBox()
{
    ui->spinBox->setMinimum(gSpinBoxDefaultMinValue);
    ui->spinBox->setMaximum(gSpinBoxDefaultMaxValue);
}

void MainWindow::initComboBox()
{
    for (int i = 0; i < TSI_MAX; ++i)
    {
        ui->comboBox->addItem(gTimeScaleNames[i], gTimeScaleValues[i]);
    }
}

void MainWindow::setDefaultValues()
{
    ui->spinBox->setValue(gTimePeriodDefaultValue);
    ui->comboBox->setCurrentIndex(gTimeScaleDefaultIndex);
}

void MainWindow::connectSlots()
{
    connect(&mProvider, SIGNAL(notifyPositionUpdated(QGeoPositionInfo)),
            this, SLOT(onProviderPositionUpdated(QGeoPositionInfo)));

    connect(&mProvider, SIGNAL(notifyStatusUpdated(QString)),
            this, SLOT(onProviderStatusUpdated(QString)));
}

void MainWindow::initProvider()
{
    int interval = getCurrentTimeInterval();
    mProvider.setPositioningMethods(QGeoPositionInfoSource::AllPositioningMethods);
    mProvider.init(interval);
}

int MainWindow::getCurrentTimeInterval() const
{
    int timeValue = ui->spinBox->value();
    int timeScale = ui->comboBox->currentData().toInt();
    int interval = timeValue * timeScale;

    return interval;
}

void MainWindow::onProviderPositionUpdated(const QGeoPositionInfo &info)
{
    const QDateTime &timestamp = info.timestamp();
    const QGeoCoordinate &coordinate = info.coordinate();

    ui->label->setText(
                QString(gPositionStatusString).arg(timestamp.toString()).arg(coordinate.toString())
                );
}

void MainWindow::onProviderStatusUpdated(const QString &message)
{
    ui->label_2->setText(message);
}

void MainWindow::on_pushButton_clicked()
{
    int interval = getCurrentTimeInterval();
    mProvider.setTimerInterval(interval);
}

void MainWindow::on_allRadioButton_toggled(bool checked)
{
    if (checked)
    {
        mProvider.setPositioningMethods(QGeoPositionInfoSource::AllPositioningMethods);
    }
}

void MainWindow::on_satelliteRadioButton_toggled(bool checked)
{
    if (checked)
    {
        mProvider.setPositioningMethods(QGeoPositionInfoSource::SatellitePositioningMethods);
    }
}

void MainWindow::on_nonSatelliteradioButton_toggled(bool checked)
{
    if (checked)
    {
        mProvider.setPositioningMethods(QGeoPositionInfoSource::NonSatellitePositioningMethods);
    }
}
