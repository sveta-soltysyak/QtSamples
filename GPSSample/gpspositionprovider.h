#ifndef GPSPOSITIONPROVIDER_H
#define GPSPOSITIONPROVIDER_H

#include <QObject>

class QGeoPositionInfoSource;
class QGeoPositionInfo;

class GPSPositionProvider : public QObject
{
    Q_OBJECT
public:
    explicit GPSPositionProvider(QObject *parent = 0);

public:
    void init(int interval = 0);
    void setTimerInterval(int interval);

public slots:
    void onPositionUpdated(const QGeoPositionInfo &info);

signals:
    void notifyPositionUpdated(const QGeoPositionInfo &info);
    void notifyStatusUpdated(const QString &message);

private:
    QGeoPositionInfoSource *mPositionInfoSource;
};

#endif // GPSPOSITIONPROVIDER_H
