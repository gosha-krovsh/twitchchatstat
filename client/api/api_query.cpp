#include "api_query.h"

ApiQuery::ApiQuery(const std::shared_ptr<AbstractController>& controller,
                   QObject* parent) :
    QObject(parent),
    manager_(new QNetworkAccessManager(this)),
    controller_(controller) {
}

AbstractController::Update ApiQuery::GetUpdates(const QString& client_id,
                                                const QString& token) {
  QEventLoop eventLoop;
  connect(manager_,
          SIGNAL(finished(QNetworkReply * )),
          &eventLoop,
          SLOT(quit()));

  QUrl main_url = QUrl(kServerUrl + "/update");
  QUrlQuery url_query;
  url_query.addQueryItem("client_id", client_id);
  url_query.addQueryItem("token", token);

  main_url.setQuery(url_query);
  QNetworkRequest request(main_url);

  QNetworkReply* reply = manager_->get(request);
  eventLoop.exec();

  if (reply->error() == QNetworkReply::NoError) {
    qDebug("Success");

    QJsonDocument json_document = QJsonDocument::fromJson(reply->readAll());
    QJsonObject update_object = json_document.object();
    int plus = update_object.value("plus").toInt(0);
    int minus = update_object.value("minus").toInt(0);

    delete reply;
    return {plus, minus};
  } else {
    qDebug() << reply->error();

    delete reply;
    throw std::runtime_error("Bad update request");
  }
}

void ApiQuery::SendHello(const QString& client_id,
                         const QString& token) {
  QEventLoop eventLoop;
  connect(manager_,
          SIGNAL(finished(QNetworkReply * )),
          &eventLoop,
          SLOT(quit()));

  QUrl main_url = QUrl(kServerUrl + "/hello");
  QUrlQuery url_query;
  url_query.addQueryItem("client_id", client_id);
  url_query.addQueryItem("token", token);

  main_url.setQuery(url_query);
  QNetworkRequest request(main_url);

  QNetworkReply* reply = manager_->get(request);
  eventLoop.exec();

  if (reply->error() == QNetworkReply::NoError) {
    delete reply;
  } else {
    qDebug() << reply->error();

    delete reply;
    throw std::runtime_error("Bad hello request");
  }
}
