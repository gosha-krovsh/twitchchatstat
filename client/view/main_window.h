#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <QHBoxLayout>
#include <QLabel>
#include <QResizeEvent>
#include <QStackedWidget>
#include <QDebug>
#include <QPushButton>
#include <QFormLayout>

#include "controller/abstract_controller.h"

class MainWindow : public QWidget {
  Q_OBJECT
 public:
  explicit MainWindow(std::shared_ptr<AbstractController> controller,
                      QWidget* parent = nullptr);
  ~MainWindow() override = default;

  void UpdateButtonClickedHandle();
  void HelloButtonClickedHandle();

 private:
  void SetGraphics();
  void SetUI();

 private:
  QLabel* plus_label_;
  QLabel* minus_label_;
  QPushButton* update_button_;
  QPushButton* hello_button_;

  QVBoxLayout* layout_;

  std::shared_ptr<AbstractController> controller_;
};

#endif  // MAIN_WINDOW_H_
