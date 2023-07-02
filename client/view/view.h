#ifndef VIEW_H_
#define VIEW_H_

#include <QHBoxLayout>
#include <QLabel>
#include <QResizeEvent>
#include <QStackedWidget>
#include <QDebug>
#include <QMainWindow>

#include "controller/abstract_controller.h"

#include "view/login_window.h"
#include "view/main_window.h"

class View : public QMainWindow {
 Q_OBJECT
 public:
  explicit View(std::shared_ptr<AbstractController> controller,
                QWidget* parent = nullptr);
  ~View() override = default;

  void SetMainScreen();

 private:
  void setGraphics();
  void setUi();

  LoginWindow* login_window_;
  MainWindow* main_window_;

  QStackedWidget* stacked_widget_{};

 private:
  std::shared_ptr<AbstractController> controller_;
};

#endif  // VIEW_H_
