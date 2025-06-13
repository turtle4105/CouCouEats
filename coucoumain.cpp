#include "coucoumain.h"
#include "ui_coucoumain.h"

CouCouMain::CouCouMain(QWidget *parent): QMainWindow(parent), ui(new Ui::CouCouMain)
{
    ui->setupUi(this);
    client = new TcpClient(this);  // MainWindow 소멸 시 같이 삭제됨
    client->connectToServer();     // 연결은 딱 한 번만 하면 됨

    connect(ui->BtnMyEats, &QPushButton::clicked, this, /*[=](){
        QJsonObject req;
        req["signal"] = "check";
        client->sendJson(req);
    }*/&CouCouMain::showChoiceLoginDialg);

    // 서버로부터 받은 JSON 응답을 여기 처리
    connect(client, &TcpClient::jsonReceived, this, [=](QJsonObject json){
        qDebug() << "here";

        QString signal = json["signal"].toString();
        // Signal 분기 처리 시작
        if (signal == "r") {
            qDebug() << "here3";
        }
    });


}

void CouCouMain::showChoiceLoginDialg() {

    QWidget *overlay = new QWidget(this);
    overlay->setAttribute(Qt::WA_DeleteOnClose);
    overlay->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    overlay->setAttribute(Qt::WA_TranslucentBackground);
    overlay->resize(this->size());
    overlay->show();

    // 다이얼로그 생성
    QDialog *dialog = new QDialog(overlay);  // parent는 overlay!
    dialog->setWindowFlags(Qt::FramelessWindowHint);
    dialog->setStyleSheet("QDialog { border: 1px solid #999999; background-color: white; }"); //border-radius: 12px;
    dialog->setFixedSize(450, 350);

    // 수직 레이아웃 구성
    QVBoxLayout *layout = new QVBoxLayout(dialog);

    QLabel *wowLabel = new QLabel("WOW 와우회원은 매 주문 무료배달", dialog);
    wowLabel->setAlignment(Qt::AlignCenter);
    wowLabel->setStyleSheet(R"(
        Q  background-color: #0039a6;
            color: white;
            foLabel {
          nt-size: 13pt;
            font-weight: bold;
            padding: 10px;
            border-top-left-radius: 8px;
            border-top-right-radius: 8px;
        }
    )");
    layout->addWidget(wowLabel);

    // 제목
    QLabel *mainLabel = new QLabel("\n쿠팡이츠 로그인", dialog);
    mainLabel->setAlignment(Qt::AlignLeft);
    mainLabel->setStyleSheet("font-size: 16pt; font-weight: bold;");
    layout->addWidget(mainLabel);

    // 부제
    QLabel *subLabel = new QLabel("사용 중인 쿠팡 앱이 있다면\n더 빠르고 간편하게 로그인할 수 있습니다.", dialog);
    subLabel->setAlignment(Qt::AlignLeft);
    subLabel->setStyleSheet("font-size: 14pt;"); //font-weight: bold;
    layout->addWidget(subLabel);

    // 간편 로그인 버튼
    QPushButton *easyLoginBtn = new QPushButton("쿠팡 앱으로 간편 로그인", dialog);
    easyLoginBtn->setMinimumHeight(50);
    easyLoginBtn->setStyleSheet("font-size: 14pt; background-color: #00A8FF; color: white;");
    layout->addWidget(easyLoginBtn);

    // 이메일 로그인 버튼
    QPushButton *emailLoginBtn = new QPushButton("쿠팡 아이디(이메일)로 로그인", dialog);
    emailLoginBtn->setMinimumHeight(50);
    emailLoginBtn->setStyleSheet("font-size: 14pt;");
    layout->addWidget(emailLoginBtn);

    // 가로 정렬 회원가입 안내
    QHBoxLayout *signupLayout = new QHBoxLayout();
    QLabel *signupLabel = new QLabel("아직 회원이 아니신가요?", dialog);
    signupLabel->setStyleSheet("font-size: 12pt;");
    signupLabel->setAlignment(Qt::AlignCenter);
    QPushButton *signupBtn = new QPushButton("회원가입", dialog);
    signupBtn->setFlat(true);
    signupBtn->setCursor(Qt::PointingHandCursor);
    signupBtn->setStyleSheet("font-size: 13pt; color: blue; text-decoration: underline;");
    signupLayout->addWidget(signupLabel);
    signupLayout->addWidget(signupBtn);
    // signupLayout->addStretch(); //오른쪽 여백 없앰
    layout->addLayout(signupLayout);

    //버튼 동작
    QObject::connect(easyLoginBtn, &QPushButton::clicked, dialog, [=]() {
        dialog->close();
        overlay->close();
    });

    //다이얼로그 위치를 하단으로 조정
    int x = (overlay->width() - dialog->width()) / 2;
    int y = (overlay->height() - dialog->height()); //
    dialog->move(x, y);

    //실행
    dialog->show();

    // 회원가입 페이지로 이동
    connect(signupBtn, &QPushButton::clicked, this, [=](){
        login = new main2_login(client, this);
        ui->stackedWidget->addWidget(login);
        ui->stackedWidget->setCurrentWidget(login);
        login->getStackedWidget()->setCurrentWidget(login->getSignupPage());
        dialog->close();
        overlay->close();
        connect(login, &main2_login::reqTurnToMain, this, [=](){
            ui->stackedWidget->setCurrentWidget(ui->page3Main);
        });
    });

    // 로그인 페이지로 이동
    connect(emailLoginBtn, &QPushButton::clicked, this, [=](){
        login = new main2_login(client, this);
        ui->stackedWidget->addWidget(login);
        ui->stackedWidget->setCurrentWidget(login);
        login->getStackedWidget()->setCurrentWidget(login->getLoginPage());
        dialog->close();
        overlay->close();
        //이부분 수정함  ----------------------------추가해야함
        connect(login, &main2_login::reqTurnToMain, this, [=](){
            ui->stackedWidget->setCurrentWidget(ui->page3Main);
        });
    });

}

CouCouMain::~CouCouMain()
{
    delete ui;
}
