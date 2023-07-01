#include "view.h"

#include <utility>

View::View(std::shared_ptr<AbstractController> controller, QWidget* parent) :
    QMainWindow(parent),
    login_window_(new QWidget(this)),
    main_window_(new QWidget(this)),
    stacked_widget_(new QStackedWidget(this)),
    controller_(std::move(controller)) {
  setUi();
  setGraphics();

  show();
}

void View::setUi() {
  stacked_widget_->addWidget(login_window_);
  stacked_widget_->addWidget(main_window_);
  stacked_widget_->setCurrentIndex(0);
}

void View::setGraphics() {
  setWindowTitle("Twitch Statistics");
  // Policies
  // main_window_->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,
  //                                         QSizePolicy::Expanding));

  // Window customisation:
  setMinimumSize(600, 500);
  main_window_->setStyleSheet("background-color: rgb(145, 252, 255);");
}
