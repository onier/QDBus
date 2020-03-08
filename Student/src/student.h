#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>
#include "types.h"

class Student : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.student.interface")

public:
    Student(QObject *parent = 0);
    ~Student();

signals:
    Q_SCRIPTABLE void needHelp(Letter reason);
    Q_SCRIPTABLE void parcelRecived(QString parcelDescription);

public slots:
    Q_SCRIPTABLE Q_NOREPLY void reciveParcel(Parcel parcelFromParents);
    void sendLetterToParents(QString letterText);

private:
    void registerService();
};

#endif // STUDENT_H
