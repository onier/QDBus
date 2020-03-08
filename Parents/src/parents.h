#ifndef PARENTS_H
#define PARENTS_H

#include <QObject>
#include "types.h"

class Parents : public QObject
{
    Q_OBJECT
public:
    Parents(QObject *parent = 0);
    ~Parents();


private slots:
    void reciveLetter(const Letter letterFromStudent);

private:
    void connectToDBusSignal();
    void sendHelpToChild(const Letter letterFromStudent) const;
    void sendParcel(const Parcel parentsParcel) const;
    Letter writeLetter(const Letter letterFromStudent) const;
    Stuff poskrestiPoSusekam() const;
};

#endif // PARENTS_H
