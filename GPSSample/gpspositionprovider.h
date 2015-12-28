#ifndef GPSPOSITIONPROVIDER_H
#define GPSPOSITIONPROVIDER_H

#include <QObject>
#include <QGeoPositionInfoSource>

class QGeoPositionInfo;

class GPSPositionProvider : public QObject
{
    Q_OBJECT
public:
    explicit GPSPositionProvider(QObject *parent = 0);

public:
    void init(int interval = 0);
    void setTimerInterval(int interval);
    void setPositioningMethods(QGeoPositionInfoSource::PositioningMethods methods);

private:
    void connectSlots();

public slots:
    void onPositionUpdated(const QGeoPositionInfo &info);
    void onEror(QGeoPositionInfoSource::Error positioningError);
    void onUpdateTimeout();

signals:
    void notifyPositionUpdated(const QGeoPositionInfo &info);
    void notifyStatusUpdated(const QString &message);

private:
    QGeoPositionInfoSource *mPositionInfoSource;
};

#endif // GPSPOSITIONPROVIDER_H
