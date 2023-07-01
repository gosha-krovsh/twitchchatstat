#include "main_window.h"

#include <utility>

MainWindow::MainWindow(std::shared_ptr<AbstractController> controller,
                       QWidget* parent) : QWidget(parent),
                                          controller_(std::move(controller)) {
  SetUI();
  SetGraphics();

  hide(); // Default policy of created windows is hidden
}

void MainWindow::SetGraphics() {
}

void MainWindow::SetUI() {

}
