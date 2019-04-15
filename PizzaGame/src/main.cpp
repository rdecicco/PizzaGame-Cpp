#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "include/GameManager.h"
#include "include/Player.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<Player>("Player", 1, 0, "Player");
    qRegisterMetaType<Player::PlayerStates>("PlayerStates");
    qmlRegisterType<GameManager>("GameManager", 1, 0, "GameManager");
    qRegisterMetaType<GameManager::GameStates>("GameStates");

    static GameManager& gameManager = GameManager::getInstance();
    engine.rootContext()->setContextProperty("gameManager", &gameManager);
    engine.rootContext()->setContextProperty("playerA", &gameManager.playerA());
    engine.rootContext()->setContextProperty("playerB", &gameManager.playerB());

    engine.addImportPath("qrc:/ui");

    engine.load(QUrl(QStringLiteral("qrc:/ui/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
