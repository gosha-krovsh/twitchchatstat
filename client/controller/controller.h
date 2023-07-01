#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "view/view.h"

class Controller : public AbstractController {
 public:
  Controller();
  ~Controller() override = default;

  bool HandleLogin() override;

 private:
  std::shared_ptr<View> view_;
};

#endif  // CONTROLLER_H_
