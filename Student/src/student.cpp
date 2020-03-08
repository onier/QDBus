#include "student.h"
#include <QDBusConnection>
#include <QDebug>
#include <QDBusError>

Student::Student(QObject *parent) :
        QObject(parent) {
    registerService();
}

Student::~Student() {
}

void Student::reciveParcel(Parcel parcelFromParents) {
    qDebug()<<"reciveParcel from parent "<<parcelFromParents;
    QString letterText = parcelFromParents.letter.text;
    letterText.append(
            QString("\n Money: %1 %2").arg(parcelFromParents.letter.summ.summ).arg(parcelFromParents.letter.summ.type));
    Stuff sendedStuff = parcelFromParents.someFood;
    QString stuffText;
            foreach(QVariant food, sendedStuff) {
            stuffText.append(QString("Stuff: %1\n").arg(food.toString()));
        }

    QString parcelDescription;
    parcelDescription.append(letterText);
    parcelDescription.append("\n");
    parcelDescription.append(stuffText);
    qDebug()<<"emit parcelRecived "<< parcelDescription;
    emit parcelRecived(parcelDescription);
}

void Student::sendLetterToParents(QString letterText) {
    Letter letterToParents;
    Money money;
    money.summ = 123;
    money.type = "$";
    letterToParents.summ = money;
    letterToParents.text = letterText;
    letterToParents.letterDate = QDateTime::currentDateTime();
    emit needHelp(letterToParents);
}

void Student::registerService() {
    QDBusConnection connection = QDBusConnection::connectToBus(QDBusConnection::SessionBus, dbus::studentServiceName());

    if (!connection.isConnected())
        qDebug() << (QString("DBus connect false"));
    else
        qDebug() << (QString("DBus connect is successfully"));

    if (!connection.registerObject(dbus::studentServicePath(), this, QDBusConnection::ExportScriptableContents)) {
        qDebug() << (QString("DBus register object false. Error: %1").arg(connection.lastError().message()));
    } else
        qDebug() << (QString("DBus register object successfully"));

    if (!connection.registerService(dbus::studentServiceName())) {
        qDebug() << (QString("DBus register service false. Error: %1").arg(connection.lastError().message()));
    } else
        qDebug() << (QString("DBus register service successfully"));
}

