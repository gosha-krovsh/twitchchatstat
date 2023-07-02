#include <QDesktopServices>
#include "twitch_auth.h"

TwitchAuth::TwitchAuth(const std::shared_ptr<AbstractController>& controller,
                       QObject* parent) :
    QObject(parent),
    oauth2_(new QOAuth2AuthorizationCodeFlow(this)),
    controller_(controller) {

  oauth2_->setAuthorizationUrl(auth_url_);
  oauth2_->setAccessTokenUrl(token_url_);
  oauth2_->setClientIdentifier(client_id_);
  oauth2_->setClientIdentifierSharedKey(client_secret_);
  oauth2_->setScope(scope_);

  oauth2_->setModifyParametersFunction([](QAbstractOAuth::Stage stage,
                                        QVariantMap* parameters) {
    (*parameters)["redirect_uri"] = QUrl("http://localhost:3000/");
  });

  connect(oauth2_, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser,
          &QDesktopServices::openUrl);
}

void TwitchAuth::Grant() {
  auto replyHandler = new QOAuthHttpServerReplyHandler(3000);
  oauth2_->setReplyHandler(replyHandler);

  oauth2_->grant();
  connect(oauth2_, &QOAuth2AuthorizationCodeFlow::statusChanged, [=, this](
      QAbstractOAuth::Status status) {
    if (status == QAbstractOAuth::Status::Granted) {
      controller_->ProcessLogin();
    } else {
      qDebug("Authentication failed");
    }
  });
}

QString TwitchAuth::GetClientID() {
  return client_id_;
}

QString TwitchAuth::GetToken() {
  return oauth2_->token();
}
