#include <QCoreApplication>
#include "parents.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Parents par;
    return a.exec();
}
