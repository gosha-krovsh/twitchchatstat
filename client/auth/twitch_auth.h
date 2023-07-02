#ifndef TWITTER_AUTH_H_
#define TWITTER_AUTH_H_

#include <QtCore>

#include <QtNetwork>
#include <QtNetworkAuth>

#include "controller/abstract_controller.h"

class TwitchAuth : public QObject {
 Q_OBJECT

 public:
  explicit TwitchAuth(const std::shared_ptr<AbstractController>& controller,
                      QObject* parent = nullptr);

 public:
  void Grant();

 public:
  QString GetClientID();
  QString GetToken();

 private:
  const QUrl auth_url_ = QUrl("https://id.twitch.tv/oauth2/authorize");
  const QUrl token_url_ = QUrl("https://id.twitch.tv/oauth2/token");
  const QString scope_ = "chat%3Aread+chat%3Aedit";

  /* This variables can be found on dev.twitch.tv */
  const QString client_id_ = "<client-id>";
  const QString client_secret_ = "<client-secret>";

  QOAuth2AuthorizationCodeFlow* oauth2_;
  std::shared_ptr<AbstractController> controller_;
};

#endif  // TWITTER_AUTH_H_
