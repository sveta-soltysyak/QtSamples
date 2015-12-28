#include "gpspositionprovider.h"



const QString &gInitSucceeded1 = "Default Geo Position Info Source created. Timer with interval %1 started.";
const QString &gInitFailed = "Failed to create default Geo Position Info Source.";
const QString &gTimerIntervalChanged1 = "Timer inverval changed to %1";

const QString &gErrorOccured1 = "Error returned by Geo Position Info Source: %1";
const QString &gAccessError = "The connection setup to the remote positioning backend failed because the application lacked the required privileges.";
const QString &gClosedError = "The remote positioning backend closed the connection.";
const QString &gNoError = "No error has occurred.";
const QString &gUnknownError = "An unidentified error occurred.";

const QString &gTimeoutOccured = "Current position could not be retrieved.";


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
        connectSlots();

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

void GPSPositionProvider::setPositioningMethods(QGeoPositionInfoSource::PositioningMethods methods)
{
    if (mPositionInfoSource)
    {
        mPositionInfoSource->setPreferredPositioningMethods(methods);
    }
}

void GPSPositionProvider::connectSlots()
{
    connect(mPositionInfoSource, SIGNAL(positionUpdated(QGeoPositionInfo)),
            this, SLOT(onPositionUpdated(QGeoPositionInfo)));
    connect(mPositionInfoSource, static_cast<void(QGeoPositionInfoSource::*)(QGeoPositionInfoSource::Error)>(&QGeoPositionInfoSource::error),
        [=](QGeoPositionInfoSource::Error positioningError){ onEror(positioningError); });
    connect(mPositionInfoSource, SIGNAL(updateTimeout()) , this, SLOT(onUpdateTimeout()));
}

void GPSPositionProvider::onPositionUpdated(const QGeoPositionInfo &info)
{
    emit notifyPositionUpdated(info);
}

void GPSPositionProvider::onEror(QGeoPositionInfoSource::Error positioningError)
{
    QString message;

    switch (positioningError)
    {
    case QGeoPositionInfoSource::AccessError:
        message = gAccessError;
        break;
    case QGeoPositionInfoSource::ClosedError:
        message = gAccessError;
        break;
    case QGeoPositionInfoSource::NoError:
        message = gNoError;
        break;
    case QGeoPositionInfoSource::UnknownSourceError:
    default:
        message = gUnknownError;
        break;
    }

    emit notifyStatusUpdated(gErrorOccured1.arg(message));
}


void GPSPositionProvider::onUpdateTimeout()
{
    emit notifyStatusUpdated(gTimeoutOccured);
}
