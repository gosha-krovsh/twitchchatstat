#include "controller.h"

Controller::Controller() :
    view_(std::make_shared<View>(std::shared_ptr<AbstractController>(this))) {
}

bool Controller::HandleLogin() {
  // TODO view set another window
  // Now always true
  return true;
}
