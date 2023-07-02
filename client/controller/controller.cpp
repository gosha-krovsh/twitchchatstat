#include "controller.h"

Controller::Controller() :
    view_(std::make_shared<View>(std::shared_ptr<AbstractController>(this))),
    auth_(std::make_shared<TwitchAuth>(std::shared_ptr<AbstractController>(this),
                                       view_.get())),
    api_query_(std::make_shared<ApiQuery>(std::shared_ptr<AbstractController>(this),
               view_.get())) {
}

void Controller::HandleLogin() {
  auth_->Grant();
}

AbstractController::Update Controller::HandleUpdate() {
  return api_query_->GetUpdates(auth_->GetClientID(), auth_->GetToken());
}

void Controller::ProcessLogin() {
  /* This update is needed to authorise a new user */
  api_query_->GetUpdates(auth_->GetClientID(), auth_->GetToken());
  view_->SetMainScreen();

  qInfo("Auth success!");
}

void Controller::SendHello() {
  api_query_->SendHello(auth_->GetClientID(), auth_->GetToken());
}
