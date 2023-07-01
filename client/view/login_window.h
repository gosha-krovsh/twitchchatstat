#ifndef LOGIN_WINDOW_H_
#define LOGIN_WINDOW_H_

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QResizeEvent>
#include <QStackedWidget>
#include <QDebug>

#include "controller/abstract_controller.h"

class LoginWindow : public QWidget {
 Q_OBJECT
 public:
  explicit LoginWindow(std::shared_ptr<AbstractController> controller,
                       QWidget* parent = nullptr);
  ~LoginWindow() override = default;

  void LoginClickedHandle();

 private:
  void SetGraphics();
  void SetUI();

  QPushButton* login_button_;

  std::shared_ptr<AbstractController> controller_;
};

#endif // LOGIN_WINDOW_H_
