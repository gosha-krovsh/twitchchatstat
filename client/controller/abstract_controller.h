#ifndef ABSTRACT_CONTROLLER_H_
#define ABSTRACT_CONTROLLER_H_

class AbstractController {
 public:
  struct Update {
    int plus;
    int minus;
  };

 public:
  virtual ~AbstractController() = default;

  virtual void HandleLogin() = 0;
  virtual void ProcessLogin() = 0;
  virtual Update HandleUpdate() = 0;
  virtual void SendHello() = 0;
};

#endif  // ABSTRACT_CONTROLLER_H_
