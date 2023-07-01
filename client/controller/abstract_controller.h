#ifndef ABSTRACT_CONTROLLER_H_
#define ABSTRACT_CONTROLLER_H_

class AbstractController {
 public:
  virtual ~AbstractController() = default;
  /* Handles any auth and returns success */
  virtual bool HandleLogin() = 0;

 private:
  // Auth
};

#endif  // ABSTRACT_CONTROLLER_H_
