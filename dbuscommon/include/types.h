#ifndef TYPES_H
#define TYPES_H
#include <QString>
#include <QDateTime>
#include <QMap>
#include <QMetaType>
#include <QtDBus>

namespace dbus
{
    static QString studentServiceName()
    {
        return "org.student.interface";
    }
    static QString studentServicePath()
    {
        return "/org/student/interface";
    }
}

struct Money
{
    int summ;
    QString type;

    Money()
        : summ(0)
        , type()
    {}

    friend QDBusArgument &operator<<(QDBusArgument &argument, const Money &arg);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, Money &arg);
};
Q_DECLARE_METATYPE(Money)

struct Letter
{
    Money summ;
    QString text;
    QDateTime letterDate;

    Letter()
        : summ()
        , text()
        , letterDate()
    {}

    friend QDBusArgument &operator<<(QDBusArgument &argument, const Letter &arg);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, Letter &arg);
};
Q_DECLARE_METATYPE(Letter)

typedef QList<QVariant> Stuff;

Q_DECLARE_METATYPE(Stuff)

struct Parcel
{
    Stuff someFood;
    Letter letter;

    Parcel()
        : someFood()
        , letter()
    {}

    friend QDBusArgument &operator<<(QDBusArgument &argument, const Parcel &arg);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, Parcel &arg);
};

Q_DECLARE_METATYPE(Parcel)

#endif // TYPES_H
