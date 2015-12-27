#include "gpspositionprovider.h"
#include <QGeoPositionInfoSource>


const QString gInitSucceeded1 = "Default Geo Position Info Source created. Timer with interval %1 started.";
const QString gInitFailed = "Failed to create default Geo Position Info Source.";
const QString gTimerIntervalChanged1 = "Timer inverval changed to %1";


GPSPositionProvider::GPSPositionProvider(QObject *parent):
    QObject(parent),
    mPositionInfoSource(NULL)
{
}

void GPSPositionProvider::init(int interval)
{
    mPositionInfoSource = QGeoPositionInfoSource::createDefaultSource(this);

    if (mPositionInfoSource)
    {
        connect(mPositionInfoSource, SIGNAL(positionUpdated(QGeoPositionInfo)),
                this, SLOT(onPositionUpdated(QGeoPositionInfo)));
        mPositionInfoSource->setUpdateInterval(interval);
        mPositionInfoSource->startUpdates();

        emit notifyStatusUpdated(QString(gInitSucceeded1).arg(interval));
    }
    else
    {
        emit notifyStatusUpdated(gInitFailed);
    }
}

void GPSPositionProvider::setTimerInterval(int interval)
{
    if (mPositionInfoSource)
    {
        mPositionInfoSource->setUpdateInterval(interval);

        emit notifyStatusUpdated(QString(gTimerIntervalChanged1).arg(interval));
    }
}

void GPSPositionProvider::onPositionUpdated(const QGeoPositionInfo &info)
{
    emit notifyPositionUpdated(info);
}
