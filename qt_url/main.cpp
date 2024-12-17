#include <QCoreApplication>
//QNetwork headers to manage network requests and responses
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QDebug>
//QEventLoop to wait for asynchronous data from the network
#include <QEventLoop>


// print html contents
void printHTML(QString html){
    qDebug() << "Done";
    qDebug() << html;
}

int main(int argc, char *argv[])
{
    // Initialize QCoreApplication for event-driven support
    QCoreApplication a(argc, argv);
    QString html;
    qDebug() << "Start";
    // Manager to handle network requests
    QNetworkAccessManager manager;
    QNetworkRequest req(QUrl("https://www.vt.edu/"));

    // Send a GET request and receive a reply
    QNetworkReply *reply = manager.get(req);
    // Use an event loop to wait for the reply to finish
    QEventLoop loop;
    // Connect the finished signal of the reply
    // to Quit the event loop when finished signal is emitted
    QObject::connect(reply, &QNetworkReply::finished,
                     &loop, &QEventLoop::quit);
    // Start the event loop to wait for the response
    loop.exec();
    // Check for errors and read the HTML content if no errors occurred
    if (reply->error() == QNetworkReply::NoError) {
        html = reply->readAll();
        printHTML(html);
    } else {
        qDebug() << "Error: " << reply->errorString();
    }
    // Clean up reply object after use
    reply->deleteLater();
    // Execute the application event loop
    return a.exec();
}
