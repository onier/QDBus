#ifndef TYPES_H
#define TYPES_H

#include <QString>
#include <QDateTime>
#include <QMap>
#include <QMetaType>
#include <QtDBus>

namespace dbus {
    static QString studentServiceName() {
        return "org.student.interface";
    }

    static QString studentServicePath() {
        return "/org/student/interface";
    }
}

struct Money {
    int summ;
    QString type;

    Money()
            : summ(0), type() {}

    operator QString() const {
        return "summ=" + QString(std::to_string(summ).data()) + "   type=" + type;
    }

    friend QDBusArgument &operator<<(QDBusArgument &argument, const Money &arg);

    friend const QDBusArgument &operator>>(const QDBusArgument &argument, Money &arg);
};

Q_DECLARE_METATYPE(Money)

struct Letter {
    Money summ;
    QString text;
    QDateTime letterDate;

    Letter()
            : summ(), text(), letterDate() {}

    operator QString() const {
        return "money:" + summ + "  text:" + text + "   letterDate:" + letterDate.toString();
    }

    friend QDBusArgument &operator<<(QDBusArgument &argument, const Letter &arg);

    friend const QDBusArgument &operator>>(const QDBusArgument &argument, Letter &arg);
};

Q_DECLARE_METATYPE(Letter)

typedef QList<QVariant> Stuff;

Q_DECLARE_METATYPE(Stuff)

struct Parcel {
    Stuff someFood;
    Letter letter;

    Parcel()
            : someFood(), letter() {}

    operator QString() const {

        return "Stuff:" + QString(std::to_string(someFood.size()).data()) + "  letter:" + letter;
    }

    friend QDBusArgument &operator<<(QDBusArgument &argument, const Parcel &arg);

    friend const QDBusArgument &operator>>(const QDBusArgument &argument, Parcel &arg);
};

Q_DECLARE_METATYPE(Parcel)

#endif // TYPES_H
