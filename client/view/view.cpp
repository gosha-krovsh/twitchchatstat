#include "view.h"

#include <utility>

View::View(std::shared_ptr<AbstractController> controller, QWidget* parent) :
    QMainWindow(parent),
    login_window_(new LoginWindow(controller, this)),
    main_window_(new MainWindow(controller, this)),
    stacked_widget_(new QStackedWidget(this)),
    controller_(std::move(controller)) {
  setUi();
  setGraphics();

  show();
  stacked_widget_->show();
}

void View::setUi() {
  stacked_widget_->addWidget(login_window_);
  stacked_widget_->addWidget(main_window_);
  stacked_widget_->setCurrentIndex(0);
}

void View::setGraphics() {
  setWindowTitle("Twitch Statistics");

  stacked_widget_->setMinimumSize(600, 500);
  stacked_widget_->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,
                            QSizePolicy::Expanding));


  setMinimumSize(600, 500);
  main_window_->setStyleSheet("background-color: rgb(145, 252, 255);");
}

void View::SetMainScreen() {
  stacked_widget_->setCurrentIndex(1);
}
