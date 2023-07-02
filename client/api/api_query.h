#ifndef API_QUERY_H_
#define API_QUERY_H_

#include <QtCore>
#include <QtNetwork>

#include "controller/abstract_controller.h"

class ApiQuery : public QObject {
 Q_OBJECT
 public:
  explicit ApiQuery(const std::shared_ptr<AbstractController>& controller,
                    QObject* parent = nullptr);

  AbstractController::Update GetUpdates(const QString& client_id,
                                        const QString& token);
  void SendHello(const QString& client_id,
                 const QString& token);

 private:
  const QString kServerUrl = "<server-url>";
  QNetworkAccessManager* manager_;

  std::shared_ptr<AbstractController> controller_;
};

#endif  // API_QUERY_H_
