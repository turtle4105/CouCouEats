#include "tcpclient.h"
#include <QDebug>

TcpClient::TcpClient(QObject *parent)
    : QObject(parent), socket(new QTcpSocket(this)) { //this를 parent로 넘겨서 TcpClient가 삭제되면 socket도 같이 삭제됨
    //서버에 연결되면 onConnected() 자동 실행
    connect(socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    //데이터 오면 onReadyRead()자동 실행
    connect(socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
    //연결 끊기면 onDisConnected() 자동 실행
    connect(socket, &QTcpSocket::disconnected, this, &TcpClient::onDisconnected);
}

//서버에 연결
void TcpClient::connectToServer() {
    socket->connectToHost("10.10.20.109", 20006);
    if (socket->waitForConnected(3000)) {
        qDebug() << "서버에 연결되었습니다.";
    } else {
        qDebug() << "연결 실패:" << socket->errorString();
    }
}

//JSON 전송
void TcpClient::sendJson(const QJsonObject &json) {
    //먼저 소켓이 연결되어 있는지 확인 state()
    if (socket->state() == QAbstractSocket::ConnectedState) {
        QJsonDocument doc(json);
        //JSON -> 문자열 형태로 변환
        QByteArray data = doc.toJson(QJsonDocument::Compact);
        //소켓을 통해 전송
        data.append('\n');
        socket->write(data);
        socket->flush();

    }

}

// 서버 연결 확인용
void TcpClient::onConnected() {
    qDebug() << "Connected to server.";
}

void TcpClient::onReadyRead() {
    buffer.append(socket->readAll());
    qDebug() << "현재 버퍼 (문자열):" << QString::fromUtf8(buffer);  // 문자열로 보기 쉽게 출력

    if (!isJsonComplete(buffer)) {
        // 아직 JSON 완성 안 됨, 다음 데이터 기다려
        return;
    }

    // JSON이 완성되었을 때만 파싱 시도
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(buffer, &error);

    if (error.error == QJsonParseError::NoError) {
        if (doc.isObject()) {
            emit jsonReceived(doc.object());
        }
        buffer.clear(); // 다 처리했으니 버퍼 초기화
    } else {
        qDebug() << "JSON 파싱 오류:" << error.errorString();
        qDebug() << "문제 있는 버퍼 (문자열):" << QString::fromUtf8(buffer);  // 보기 쉬운 문자열 출력
        buffer.clear(); // 복구 불가, 버퍼 비움
    }
}


// 함수 정의
bool TcpClient::isJsonComplete(const QByteArray& data) {
    int curly_open = 0;
    int curly_close = 0;
    int square_open = 0;
    int square_close = 0;

    for (char c : data) {
        if (c == '{') curly_open++;
        if (c == '}') curly_close++;
        if (c == '[') square_open++;
        if (c == ']') square_close++;
    }

    return (curly_open == curly_close) && (square_open == square_close);
}

void TcpClient::onDisconnected() {
    qDebug() << "Disconnected from server.";
}

