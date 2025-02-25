# Twitch Chat Statistics

Twitch Chat Statistics is an application, that can be usefull to monitor twitch in-chat activity online during streams. It includes both a client and a server. Webhooks are used on the server side for the fastest responce during online streaming process.

## Set up
1) Update CMakelists.txt with you Qt
```cmake
set(CMAKE_PREFIX_PATH "[Path]/Qt/5.15.2/gcc_64/lib/cmake/Qt5")
```
2) Update Authentification credentials in client/auth/twitch_auth.h. They are available at dev.twitch.tv
```c++
const QString client_id_ = "<client-id>";
const QString client_secret_ = "<client-secret>";
```
3) Update server URL
```c++
const QString kServerUrl = "<server-url>";
```

## Run
1) Build server
```bash
(cd cmd/twitchstatserver && go build .)
```
1) Launch server on specified port
```bash
twitchstatserver --port=<port>
```
2) Build Qt (!!! You need Qt libs installed to do it)
3) Run client and play :)
