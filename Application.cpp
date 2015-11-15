#include "Application.h"
#include <QDebug>
#include <QString>
#include <QThread>

/** A szerver hallgatózás az inicializáláskor megkezdődik.
 *
 */
Application::Application(int argc, char *argv[])
    : QApplication(argc, argv), engine(),
      tcpServer(4444), tcpClient(),
      dataParser(QString("code.txt"))
{
    connect(&tcpServer,&CommunicationTcpSocketServer::dataReady,
            &dataParser,&DataParser::dataInput);
    connect(&tcpClient,&CommunicationTcpSocketClient::dataReady,
            &dataParser,&DataParser::dataInput);

    connect(&tcpServer,&CommunicationTcpSocketServer::errorOccurred,
            this,&Application::errorHandling);
    connect(&tcpServer,&CommunicationTcpSocketClient::errorOccurred,
            this,&Application::errorHandling);
    connect(&dataParser,&DataParser::errorOccurred,
            this,&Application::errorHandling);

    tcpClient.connect(QString("localhost"),4444);
}

void Application::dataReceived(QDataStream& stream)
{
    qDebug() << "Adat feldolgozása..."<< endl;
    // Egyenlőre csak konzolra kiírás
    //TODO: mi legyen az adattal?

    QByteArray ba;
    stream >> ba;
    qDebug() << ba.size() << " bájt:" << endl << ba.toHex();
}

void Application::errorHandling(const QString& error)
{
    qWarning() << "Hiba!";
    qWarning() << error << endl;
}
