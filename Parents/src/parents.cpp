#include "parents.h"

#include <QDBusConnection>
#include <QDebug>

Parents::Parents(QObject *parent) :
    QObject(parent)
{
    connectToDBusSignal();
}

Parents::~Parents()
{
}

void Parents::reciveLetter(const Letter letterFromStudent)
{
    qDebug()<<"Letter recived: ";
    qDebug()<<"Letter text: "<<letterFromStudent.text;
    qDebug()<<"Letter date: "<<letterFromStudent.letterDate;
    qDebug()<<"Letter date: "<<letterFromStudent.summ.summ;
    qDebug()<<"Letter date: "<<letterFromStudent.summ.type;
    sendHelpToChild(letterFromStudent);
}

void Parents::connectToDBusSignal()
{
    bool isConnected = QDBusConnection::sessionBus().connect(
            "",
            dbus::studentServicePath(),
            dbus::studentServiceName(),
            "needHelp", this,
            SLOT(reciveLetter(Letter)));
    if(!isConnected)
        qDebug()<<"Can't connect to needHelp signal";
    else
        qDebug()<<"connect to needHelp signal";

}

void Parents::sendHelpToChild(const Letter letterFromStudent)  const
{
    Parcel preparingParcel;
    preparingParcel.letter = writeLetter(letterFromStudent);
    preparingParcel.someFood = poskrestiPoSusekam();
    sendParcel(preparingParcel);
}

void Parents::sendParcel(const Parcel parentsParcel) const
{
    const QString studentMetod = "reciveParcel";
    QDBusMessage sendParcel = QDBusMessage::createMethodCall(dbus::studentServiceName(), dbus::studentServicePath(), "", studentMetod);

    QList<QVariant> arg;
    arg.append(qVariantFromValue(parentsParcel));

    sendParcel.setArguments(arg);

    if ( !QDBusConnection::sessionBus().send( sendParcel) )
    {
        qDebug()<<QString("D-bus %1 calling error: %2").arg(studentMetod).arg(QDBusConnection::sessionBus().lastError().message());
    }
}

Letter Parents::writeLetter(const Letter letterFromStudent) const
{
    QString text = "We read about you problem so send some help";
    Letter parentLetter;
    parentLetter.text = text;
    Money summ;
    summ.summ = letterFromStudent.text.count(",")*100;
    summ.summ += letterFromStudent.text.count(".")*50;
    summ.summ += letterFromStudent.text.count(" ")*5;
    summ.type = "USD";
    parentLetter.summ = summ;
    parentLetter.letterDate = QDateTime::currentDateTime();
    return parentLetter;
}

Stuff Parents::poskrestiPoSusekam() const
{
    Stuff food;
    food<<"Russian donuts";
    food<<"Meat dumplings";
    return food;
}
