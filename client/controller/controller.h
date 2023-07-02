#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <QtCore>

#include "view/view.h"
#include "auth/twitch_auth.h"
#include "api/api_query.h"

class Controller : public AbstractController {
 public:
  Controller();
  ~Controller() override = default;

  void HandleLogin() override;
  void ProcessLogin() override;
  Update HandleUpdate() override;
  void SendHello() override;

 private:
  std::shared_ptr<View> view_;
  std::shared_ptr<TwitchAuth> auth_;
  std::shared_ptr<ApiQuery> api_query_;
};

#endif  // CONTROLLER_H_
