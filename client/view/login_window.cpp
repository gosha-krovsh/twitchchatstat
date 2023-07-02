#include "login_window.h"

#include <utility>

LoginWindow::LoginWindow(std::shared_ptr<AbstractController> controller,
                         QWidget* parent) :
    QWidget(parent),
    login_button_(new QPushButton("Login")),
    layout_(new QHBoxLayout(this)),
    controller_(std::move(controller)) {
  SetUI();
  SetGraphics();

  show();
}

void LoginWindow::SetGraphics() {
  login_button_->setMaximumSize(200, 100);
  login_button_->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,
                                           QSizePolicy::Expanding));
}

void LoginWindow::SetUI() {
  layout_->addWidget(login_button_);
  layout_->setAlignment(Qt::Alignment::enum_type::AlignCenter);
  setLayout(layout_);

  connect(login_button_,
          &QPushButton::released,
          this,
          &LoginWindow::LoginClickedHandle);
}

void LoginWindow::LoginClickedHandle() {
  controller_->HandleLogin();
}
