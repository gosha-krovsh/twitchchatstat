#ifndef VIEW_H_
#define VIEW_H_

#include <QHBoxLayout>
#include <QLabel>
#include <QResizeEvent>
#include <QStackedWidget>
#include <QDebug>
#include <QMainWindow>

#include "controller/abstract_controller.h"

class View : public QMainWindow {
 Q_OBJECT
 public:
  explicit View(std::shared_ptr<AbstractController> controller,
                QWidget* parent = nullptr);
  ~View() override = default;

 private:
  void setGraphics();
  void setUi();
  void resizeEvent(QResizeEvent*) override;

  QWidget* main_window_;
  QWidget* login_window_;

  QStackedWidget* stacked_widget_{};

 private:
  std::shared_ptr<AbstractController> controller_;
};

#endif  // VIEW_H_
