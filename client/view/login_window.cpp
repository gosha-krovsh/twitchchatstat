#include "login_window.h"

#include <utility>

LoginWindow::LoginWindow(std::shared_ptr<AbstractController> controller,
                         QWidget* parent) :
    QWidget(parent),
    login_button_(new QPushButton("Login", this)),
    controller_(std::move(controller)) {
  SetUI();
  SetGraphics();

  hide(); // Default policy of created windows is hidden
}

void LoginWindow::SetGraphics() {
  login_button_->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,
                                           QSizePolicy::Expanding));
  login_button_->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
}

void LoginWindow::SetUI() {
  connect(login_button_,
          &QPushButton::released,
          this,
          &LoginWindow::LoginClickedHandle);
}

void LoginWindow::LoginClickedHandle() {
  controller_->HandleLogin();
}
