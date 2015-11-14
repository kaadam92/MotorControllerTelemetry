#include "Application.h"
#include <QDebug>

/** A szerver hallgatózás az inicializáláskor megkezdődik.
 *
 */
Application::Application(int argc, char *argv[])
    : QApplication(argc, argv), tcpServer(3333), engine()
{
    connect(&tcpServer,&CommunicationTcpSocketServer::dataReady,
                     this,&Application::dataReceived);

}

void Application::dataReceived(QDataStream& stream)
{

    qDebug() << "Adat feldolgozása..."<< endl;
    // Egyenlőre csak konzolra kiírás
    //TODO: mi legyen az adattal?
    qDebug() << stream << endl;
}
