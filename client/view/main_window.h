#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <QHBoxLayout>
#include <QLabel>
#include <QResizeEvent>
#include <QStackedWidget>
#include <QDebug>
#include <QPushButton>

#include "controller/abstract_controller.h"

class MainWindow : QWidget {
  Q_OBJECT
 public:
  explicit MainWindow(std::shared_ptr<AbstractController> controller,
                      QWidget* parent = nullptr);
  ~MainWindow() override = default;

  // void TranslateButtonOnClick();

 private:
  void SetGraphics();
  void SetUI();

 private:
  QLabel* plus_label_;
  QLabel* minus_label_;
  QPushButton* update_button_;

  std::shared_ptr<AbstractController> controller_;
};

#endif  // MAIN_WINDOW_H_
