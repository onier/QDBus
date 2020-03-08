#include "types.h"

#include <QMetaType>
#include <QtDBus>

static struct RegisterTypes {
    RegisterTypes()
    {
        qRegisterMetaType<Money>("Money");
        qDBusRegisterMetaType<Money>();

        qRegisterMetaType<Letter>("Letter");
        qDBusRegisterMetaType<Letter>();

        qRegisterMetaType<Stuff>("Stuff");
        qDBusRegisterMetaType<Stuff>();

        qRegisterMetaType<Parcel>("Parcel");
        qDBusRegisterMetaType<Parcel>();
    }
} RegisterTypes;

//------------------------
QDBusArgument& operator <<(QDBusArgument& argument, const Money& arg)
{
    argument.beginStructure();
    argument << arg.summ;
    argument << arg.type;
    argument.endStructure();

    return argument;
}

const QDBusArgument& operator >>(const QDBusArgument& argument, Money& arg)
{
    argument.beginStructure();
    argument >> arg.summ;
    argument >> arg.type;
    argument.endStructure();

    return argument;
}

 //------------------------
QDBusArgument& operator <<(QDBusArgument& argument, const Letter& arg)
{
    argument.beginStructure();
    argument << arg.summ;
    argument << arg.text;
    argument << arg.letterDate;
    argument.endStructure();

    return argument;
}

const QDBusArgument& operator >>(const QDBusArgument& argument, Letter& arg)
{
    argument.beginStructure();
    argument >> arg.summ;
    argument >> arg.text;
    argument >> arg.letterDate;
    argument.endStructure();

    return argument;
}

//------------------------
QDBusArgument& operator <<(QDBusArgument& argument, const Parcel& arg)
{
    argument.beginStructure();
    argument << arg.someFood;
    argument << arg.letter;
    argument.endStructure();

    return argument;
}

const QDBusArgument& operator >>(const QDBusArgument& argument, Parcel& arg)
{
    argument.beginStructure();
    argument >> arg.someFood;
    argument >> arg.letter;
    argument.endStructure();

    return argument;
}
//------------------------
