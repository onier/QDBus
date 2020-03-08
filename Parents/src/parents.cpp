#include "parents.h"

#include <QDBusConnection>
#include <QDebug>
#include <iostream>

Parents::Parents(QObject *parent) :
        QObject(parent) {
    connectToDBusSignal();
}

Parents::~Parents() {
}

void Parents::reciveLetter(const Letter letterFromStudent) {
    qDebug() << "Letter recived from student: " << letterFromStudent;
    sendHelpToChild(letterFromStudent);
}

void Parents::connectToDBusSignal() {
    bool isConnected = QDBusConnection::sessionBus().connect(
            "",
            dbus::studentServicePath(),
            dbus::studentServiceName(),
            "needHelp", this,
            SLOT(reciveLetter(Letter)));
    if (!isConnected)
        qDebug() << "Can't connect to needHelp signal";
    else
        qDebug() << "connect to needHelp signal";
    isConnected = QDBusConnection::sessionBus().connect(
            "",
            dbus::studentServicePath(),
            dbus::studentServiceName(),
            "parcelRecived", this,
            SLOT(reciveParcel(QString)));
    if (!isConnected)
        qDebug() << "Can't connect to parcelRecived signal";
    else
        qDebug() << "connect to parcelRecived signal";
}

void Parents::sendHelpToChild(const Letter letterFromStudent) const {
    Parcel preparingParcel;
    preparingParcel.letter = writeLetter(letterFromStudent);
    preparingParcel.someFood = poskrestiPoSusekam();
    sendParcel(preparingParcel);
}

void Parents::sendParcel(const Parcel parentsParcel) const {
    const QString studentMetod = "reciveParcel";
    QDBusMessage sendParcel = QDBusMessage::createMethodCall(dbus::studentServiceName(), dbus::studentServicePath(), "",
                                                             studentMetod);

    QList<QVariant> arg;
    arg.append(qVariantFromValue(parentsParcel));

    sendParcel.setArguments(arg);
    qDebug() << "send Parcel to student " << sendParcel;
    if (!QDBusConnection::sessionBus().send(sendParcel)) {
        qDebug() << QString("D-bus %1 calling error: %2").arg(studentMetod).arg(
                QDBusConnection::sessionBus().lastError().message());
    }
}

Letter Parents::writeLetter(const Letter letterFromStudent) const {
    QString text = "We read about you problem so send some help";
    Letter parentLetter;
    parentLetter.text = text;
    parentLetter.summ = letterFromStudent.summ;
    parentLetter.letterDate = QDateTime::currentDateTime();
    return parentLetter;
}

Stuff Parents::poskrestiPoSusekam() const {
    Stuff food;
    food << "Russian donuts";
    food << "Meat dumplings";
    return food;
}

void Parents::reciveParcel(QString parcelDescription) {
    qDebug() << "reciveParcel from student " << parcelDescription;
}
