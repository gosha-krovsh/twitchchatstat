#include "main_window.h"

#include <utility>

MainWindow::MainWindow(std::shared_ptr<AbstractController> controller,
                       QWidget* parent) :
    QWidget(parent),
    plus_label_(new QLabel("+(plus): ")),
    minus_label_(new QLabel("-(minus): ")),
    update_button_(new QPushButton("Update")),
    hello_button_(new QPushButton("Hello")),
    layout_(new QVBoxLayout(this)),
    controller_(std::move(controller)) {
  SetUI();
  SetGraphics();

  show();
}

void MainWindow::SetGraphics() {
  plus_label_->setMinimumSize(200, 40);
  minus_label_->setMinimumSize(200, 40);
  setSizePolicy(QSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding));
}

void MainWindow::SetUI() {
  layout_->addWidget(plus_label_);
  layout_->addWidget(minus_label_);
  layout_->addWidget(update_button_);
  layout_->addWidget(hello_button_);

  layout_->setSizeConstraint(QLayout::SizeConstraint::SetMaximumSize);
  layout_->setAlignment(Qt::Alignment::enum_type::AlignCenter);
  setLayout(layout_);

  connect(update_button_,
          &QPushButton::released,
          this,
          &MainWindow::UpdateButtonClickedHandle);
  connect(hello_button_,
          &QPushButton::released,
          this,
          &MainWindow::HelloButtonClickedHandle);
}

void MainWindow::UpdateButtonClickedHandle() {
  try {
    auto update = controller_->HandleUpdate();

    plus_label_->setText(
        "+(plus): " + QString(std::to_string(update.plus).c_str()));
    minus_label_->setText(
        "-(minus): " + QString(std::to_string(update.minus).c_str()));
  } catch (...) {
    qDebug("Bad update!");
  }
}

void MainWindow::HelloButtonClickedHandle() {
  try {
    controller_->SendHello();
  } catch (...) {
    qDebug("Bad Hello!");
  }
}
