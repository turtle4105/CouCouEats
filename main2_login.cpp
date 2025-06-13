#include "main2_login.h"
#include "ui_main2_login.h"

main2_login::main2_login(TcpClient *client, QWidget *parent)
    : QWidget(parent), ui(new Ui::main2_login), client(client)
{
    ui->setupUi(this);


    // 서버로부터 받은 JSON 응답을 여기 처리
    connect(client, &TcpClient::jsonReceived, this, [=](QJsonObject json){

        QString signal = json["signal"].toString();
        // Signal 분기 처리 시작
        // 휴대폰 번호 중복검사 결과
        if (signal == "sign_up_result") {
            QString message = json["result"].toString();
            if(message == "success"){
                QMessageBox::information(this, "입력 완료", "입력이 확정되어 더 이상 수정할 수 없습니다.");
                ui->input_email->setEnabled(false);
                ui->input_pass->setEnabled(false);
                ui->input_name->setEnabled(false);
                ui->input_phone->setEnabled(false);
                ui->birthday->setEnabled(false);
            } else if (message == "fail"){
                qDebug()<<"여기 Fail";
                QMessageBox::warning(this, "알림", "※ 이미 등록된 번호는 사용할 수 없습니다 ※");
                ui->input_phone->clear();
            }
        }
        //로그인 결과
        else if(signal == "login_result")
        {
            QString message = json["result"].toString();
            if(message == "success"){
                //로그인 성공하면 로그인한 채로 메인으로 이동

            } else if (message == "fail"){
                QMessageBox::warning(this, "알림", "※ 이메일 또는 비밀번호가 일치하지 않습니다. ※");
                ui->insert_id->clear();
                ui->insert_pass->clear();
            }
        }
        //아이디 비번 찾기 결과
        else if(signal == "find_id_result")
        {
            QString message = json["result"].toString();
            QString message1 = json["user_id"].toString();
            if(message == "success"){
                QMessageBox::information(this, "완료", "사용자의 PW:."+message1);
            } else if (message == "fail"){
                QMessageBox::warning(this, "알림", "※ 이름과 번호가 일치하지 않습니다. ※");
                ui->search_id1->clear();
                ui->search_id2->clear();
            }
        }
        else if(signal == "find_pw_result")
        {
            QString message = json["result"].toString();
            QString message1 = json["user_pw"].toString();
            if(message == "success"){
                QMessageBox::information(this, "완료", "사용자의 PW:."+message1);
            } else if (message == "fail"){
                QMessageBox::warning(this, "알림", "※ 회원 정보가 일치하지 않습니다. ※");
                ui->search_pw1->clear();
                ui->search_pw2->clear();
                ui->search_pw3->clear();
            }
        }

        //여기에 다른 시그널 넣어주기
    });




    //회원가입 페이지로 이동 후 회원가입
    connect(ui->makeid_btn, &QPushButton::clicked, this, &main2_login::move_page);
    make_id();
    connect(ui->fix_btn, &QPushButton::clicked, this, &main2_login::fix_everything);

    //로그인 페이지로 이동
    connect(ui->back_to_login, &QPushButton::clicked, this, &main2_login::move_page_to_login);
    connect(ui->back_to_login_2, &QPushButton::clicked, this, &main2_login::move_page_to_login);
    connect(ui->back_to_login_3, &QPushButton::clicked, this, &main2_login::move_page_to_login);

    //아이디 찾기 페이지로 이동
    connect(ui->search_id, &QPushButton::clicked, this, &main2_login::move_page_to_search_id);
    connect(ui->for_search_id, &QPushButton::clicked, this, &main2_login::move_page_to_search_id);
    connect(ui->for_search_id1, &QPushButton::clicked, this, &main2_login::move_page_to_search_id);
    //비밀번호 찾기 페이지로 이동
    connect(ui->search_pw, &QPushButton::clicked, this, &main2_login::move_page_to_search_pw);
    connect(ui->for_search_pw, &QPushButton::clicked, this, &main2_login::move_page_to_search_pw);
    connect(ui->for_search_pw1, &QPushButton::clicked, this, &main2_login::move_page_to_search_pw);



    //아이디 찾기, 비밀번호 찾기 글자 변경 (UI)
    ui->search_id->setStyleSheet("QPushButton { border: none; color : rgb(17, 62, 245)};");
    ui->search_pw->setStyleSheet("QPushButton { border: none; color : rgb(17, 62, 245)};");


    //아이디 찾기-> Lineedit 테두리 없애기 + 안내문구 넣어주기
    ui->for_search_id1->setStyleSheet("QPushButton {"" color: rgb(17, 62, 245);"" border: 2px solid rgb(17, 62, 245);"" }");
    // ui->search_id_btn->setStyleSheet("QPushButton { background-color :  rgb(17, 62, 245); color : white; border-radius: 7px;}"); //색상변경
    ui->search_id1->setStyleSheet("border: none;");
    ui->search_id2->setStyleSheet("border : none;");
    ui->search_id1->setPlaceholderText("이름을 입력해주세요");
    ui->search_id2->setPlaceholderText("휴대폰 번호를 입력해주세요");
    connect(ui->search_id_btn, &QPushButton::clicked, this, [=](){
        QJsonObject req;
        req["signal"] = "find_id";
        req["name"] = ui->search_id1->text();
        req["pnum"] = ui->search_id2->text();
        req["role"] = "user";
        client->sendJson(req);
    });

    //비밀번호 찾기 -> Lineedit 테두리 없애기 + 안내문구 넣어주기
    // ui->search_pw_btn->setStyleSheet("QPushButton { background-color :  rgb(17, 62, 245); color : white; border-radius: 7px;}"); //색상변경
    ui->for_search_pw->setStyleSheet("QPushButton {"" color: rgb(17, 62, 245);"" border: 2px solid rgb(17, 62, 245);"" }");
    ui->search_pw1->setStyleSheet("border: none;");
    ui->search_pw2->setStyleSheet("border : none;");
    ui->search_pw3->setStyleSheet("border : none;");
    ui->search_pw1->setPlaceholderText("이름을 입력해주세요");
    ui->search_pw2->setPlaceholderText("휴대폰 번호를 입력해주세요");
    ui->search_pw3->setPlaceholderText("이메일을 입력해주세요");
    connect(ui->search_pw_btn, &QPushButton::clicked, this, [=](){
        QJsonObject req;
        req["signal"] = "find_pw";
        req["name"] = ui->search_pw1->text();
        req["pnum"] = ui->search_pw2->text();
        req["e_mail"] = ui->search_pw3->text();
        req["role"] = "user";
        client->sendJson(req);
    });

    //로그인하기 버튼 누르면 로그인 시그널 보내주기, 위에서 결과 처리함
    connect(ui->login_btn, &QPushButton::clicked, this, [=](){
        QJsonObject req;
        req["signal"] = "login";
        req["e_mail"] = ui->insert_id->text();
        req["pw"] = ui->insert_pass->text();
        req["role"] = "user";
        client->sendJson(req);
    });

    //자식임 메인과 연결 -> 메인 화면으로 이동
    connect(ui->back_to_main, &QPushButton::clicked, this, [=](){
        emit reqTurnToMain();
    });

    //필수 체크박스 리스트 생성
    QList<QCheckBox*> checkList = {
        ui->must_1,ui->must_2, ui->must_3,ui->must_4,ui->must_5
    };
    //선택 체크박스 리스트 생성
    QList<QCheckBox*> optionalCheckList = {
                                            ui->select_1, ui->select_2, ui->select_3, ui->select_4, ui->select_5, ui->select_6
    };
    //전체 체크박스 리스트 생성
    QList<QCheckBox*> allCheckList = checkList + optionalCheckList;
    // 모든 체크박스가 체크되었는지 확인해요
    for (QCheckBox* cb : allCheckList) {
        connect(cb, &QCheckBox::toggled, this, [=]() {
            bool allChecked = std::all_of(allCheckList.begin(), allCheckList.end(),
                                          [](QCheckBox* c) { return c->isChecked(); });

            // 전체 체크박스 상태 바꿔줌
            ui->check_all->blockSignals(true);
            ui->check_all->setChecked(allChecked);
            ui->check_all->blockSignals(false);
        });
    }
    //전체동의를 누르면 모두 체크하거나 해제한다
    connect(ui->check_all, &QCheckBox::toggled, this, [=](bool checked) {
        for (QCheckBox* cb : checkList + optionalCheckList) {
            cb->setChecked(checked);
        }
    });

    // 각 체크박스의 상태 변화 시 버튼 조건 검사
    for (QCheckBox* cb : checkList) {
        connect(cb, &QCheckBox::toggled, this, &main2_login::updateSignupButton);
    }



}
//회원가입
void main2_login::make_id(){

    // 회원가입/확인 버튼 비활성화 시켜놓기
    ui->signup_btn->setEnabled(false);
    ui->fix_btn->setEnabled(false);
    //로그인페이지 아이디, 비밀번호 입력 테두리 비활성화
    ui->login_btn->setStyleSheet("QPushButton { background-color :  rgb(17, 62, 245); color : white; border-radius: 7px;}"); //색상변경
    // ui->makeid_btn->setStyleSheet("QPushButton {border-radius: 7px;}");
    ui->insert_id->setStyleSheet("border: none;");
    ui->insert_pass->setStyleSheet("border : none;");
    // === 이메일 ===
    ui->input_email->setPlaceholderText("이메일을 입력해주세요");
    connect(ui->input_email, &QLineEdit::textChanged, this, [=](const QString &text) {
        static bool email_valid = false;  // 이전 상태 저장

        QRegularExpression regex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
        bool now_valid = regex.match(text).hasMatch();

        if (now_valid != email_valid) {
            check_count += (now_valid ? 1 : -1);  // 상태가 바뀔 때만 점수 변경
            email_valid = now_valid;

            qDebug() << "이메일 상태 변경됨, count:" << check_count;
            updateSignupButton();
        }

        ui->email_check_icon->setText(now_valid ? "✔" : "");
        ui->email_check_icon->setStyleSheet("color: green;");
    });

    // === 비밀번호 ===
    ui->input_pass->setPlaceholderText("8~11자 비밀번호를 입력해주세요");
    ui->input_pass->setEchoMode(QLineEdit::Password);
    connect(ui->input_pass, &QLineEdit::textChanged, this, [=](const QString &text) {
        static bool pass_valid = false;  // 이전 상태 저장

        QRegularExpression regex("^[A-Za-z0-9]{8,11}$");
        bool now_valid = regex.match(text).hasMatch();

        // 상태가 바뀌었을 때만 점수 반영
        if (now_valid != pass_valid) {
            this->check_count += (now_valid ? 1 : -1);
            pass_valid = now_valid;
            updateSignupButton();
            qDebug() << "비밀번호 조건 변경, count:" << this->check_count;
        }

        // 아이콘과 메시지 표시
        ui->pass_check_icon->setText(now_valid ? "✔" : "");
        ui->pass_check_icon->setStyleSheet("color: green;");
        ui->pass_notice->setText(now_valid ? "사용 가능한 비밀번호 입니다." : "");
        ui->pass_notice->setStyleSheet("color: green;");
    });

    // === 이름 ===
    ui->input_name->setPlaceholderText("이름을 입력해주세요");
    connect(ui->input_name, &QLineEdit::textChanged, this, [=](const QString &text) {
        static bool name_valid = false;  // 이전 상태 저장
        bool now_valid = !text.trimmed().isEmpty();  // 공백 제거 후 내용이 있으면 유효

        if (now_valid != name_valid) {
            this->check_count += (now_valid ? 1 : -1);  // 상태 변경 시만 점수 조정
            name_valid = now_valid;
            updateSignupButton();
            qDebug() << "이름 조건 변경, count:" << this->check_count;
        }

        // 체크 아이콘 표시
        ui->name_check_icon->setText(now_valid ? "✔" : "");
        ui->name_check_icon->setStyleSheet("color: green;");
    });

    // === 전화번호 ===
    ui->input_phone->setPlaceholderText("전화번호를 입력해주세요");
    connect(ui->input_phone, &QLineEdit::textChanged, this, [=](const QString &text) {
        static bool phone_valid = false;  // 이전 상태 저장
        QRegularExpression regex("^[0-9]{11}$");  // 숫자만 11자리
        bool now_valid = regex.match(text).hasMatch();

        if (now_valid != phone_valid) {
            this->check_count += (now_valid ? 1 : -1);  // 상태 변화 시만 점수 반영
            phone_valid = now_valid;
            updateSignupButton();
            qDebug() << "전화번호 조건 변경, count:" << this->check_count;
        }

        ui->num_check_icon->setText(now_valid ? "✔" : "");
        ui->num_check_icon->setStyleSheet("color: green;");
    });

    // === 생일 ===
    ui->birthday->setCalendarPopup(true);
    ui->birthday->setDisplayFormat("yyyy-MM-dd");
    ui->birthday->setDate(QDate(2000, 1, 1));
    ui->birthday->setMaximumDate(QDate::currentDate().addYears(-14));  // 만 14세 제한

    connect(ui->birthday, &QDateEdit::dateChanged, this, [=](const QDate &date) {
        static bool birth_valid = false;  // 이전 유효 여부 저장
        bool now_valid = (date <= QDate::currentDate().addYears(-14));  // 만 14세 이상 확인

        if (now_valid != birth_valid) {
            this->check_count += (now_valid ? 1 : -1);  // 상태가 바뀌었을 때만 점수 조정
            birth_valid = now_valid;
            updateSignupButton();
            qDebug() << "생일 조건 변경, count:" << this->check_count;
            if (this->check_count == 5)
            {
                ui->fix_btn->setEnabled(true);
            }
        }
    });
    qDebug()<<"dd:"<<this->check_count;


    // === 회원가입 버튼 클릭 시 서버 전송 ===
    connect(ui->signup_btn, &QPushButton::clicked, this, [=](){
        QJsonObject req;
        req["signal"] = "sign_up";
        req["e_mail"] = ui->input_email->text();
        req["pw"] = ui->input_pass->text();
        req["name"] = ui->input_name->text();
        req["pnum"] = ui->input_phone->text();
        req["birth"] = ui->birthday->date().toString("yyyy-MM-dd");
        req["role"] = "user";
        client->sendJson(req);

    });
    connect(ui->signup_btn, &QPushButton::clicked, this, &main2_login::move_page_to_login);
}
//확인하기 중복 검사
void main2_login::fix_everything(){
    QJsonObject req;
    req["signal"] = "sign_up_result";
    req["pnum"] = ui->input_phone->text();
    req["role"] = "user";
    client->sendJson(req);
    };



QStackedWidget* main2_login::getStackedWidget() const {
    return ui->stackedWidget;
}

QWidget* main2_login::getSignupPage() const {
    return ui->signup_page;
}

QWidget* main2_login::getLoginPage() const {
    return ui->login_page;
}


// 모든 조건 충족 시 버튼 활성화 함수
void main2_login::updateSignupButton() {
    bool allChecked =
        ui->must_1->isChecked() &&
        ui->must_2->isChecked() &&
        ui->must_3->isChecked() &&
        ui->must_4->isChecked() &&
        ui->must_5->isChecked();

    ui->signup_btn->setEnabled(check_count == 5 && allChecked);
}

// 회원가입 페이지 이동
void main2_login::move_page() {
    ui->stackedWidget->setCurrentIndex(1);
}
//로그인 페이지로 이동
void main2_login::move_page_to_login()
{
    ui->stackedWidget->setCurrentIndex(0);
}
//아이디 찾기 페이지로 이동
void main2_login::move_page_to_search_id()
{
    ui->stackedWidget->setCurrentIndex(2);
}
void main2_login::move_page_to_search_pw()
{
    ui->stackedWidget->setCurrentIndex(3);
}

// 소멸자
main2_login::~main2_login()
{
    delete ui;
}


