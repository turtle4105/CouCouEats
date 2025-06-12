#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>


class TcpClient : public QObject {
    Q_OBJECT

public:
    explicit TcpClient(QObject *parent = nullptr);
    void connectToServer();
    void sendJson(const QJsonObject &json); // JSON 전송

signals:
    void jsonReceived(const QJsonObject &json); // JSON 수신 완료 후 signal

private slots:
    void onConnected();
    void onReadyRead();
    void onDisconnected();
    bool isJsonComplete(const QByteArray& data);
private:
    QTcpSocket *socket;
    QByteArray buffer;
};

#endif // TCPCLIENT_H
