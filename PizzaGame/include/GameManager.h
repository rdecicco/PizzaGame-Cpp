#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QtCore>
#include <QRandomGenerator>
#include "Player.h"

class GameManager: public QObject
{
   Q_OBJECT
   Q_PROPERTY(GameManager::GameStates state MEMBER m_state READ state NOTIFY stateChanged)
   Q_PROPERTY(uint numberOfPizzas MEMBER m_numberOfPizzas READ numberOfPizzas NOTIFY numberOfPizzasChanged)
   Q_PROPERTY(Player playerA MEMBER m_playerA READ playerA NOTIFY playerAChanged)
   Q_PROPERTY(Player playerB MEMBER m_playerB READ playerB NOTIFY playerBChanged)

   const bool fullGame = true;

public:
    enum class GameStates {
        GameOver,
        Game
    };

    Q_ENUM(GameStates)

    GameManager(QObject *parent = nullptr);

    static GameManager& getInstance() {
        static GameManager gameManager;
        return gameManager;
    }

    GameStates state();
    Q_INVOKABLE void newGame();
    Q_INVOKABLE bool eatPizzas(uint numberOfPizzas);
    Q_INVOKABLE bool canPass();
    uint numberOfPizzas();
    Player& playerA();
    Player& playerB();
    Player& currentPlayer();

signals:
    void stateChanged(GameStates state);
    void numberOfPizzasChanged(uint number);
    void playerAChanged(Player& player);
    void playerBChanged(Player& player);
    void dead(Player& player);

private:
    GameStates m_state;
    uint m_numberOfPizzas;
    Player m_playerA;
    Player m_playerB;
    QRandomGenerator m_pizzasGenerator;

    void swapPlayers(Player& currentPlayer, Player& otherPlayer);
    Player& getOtherPlayer(int playerId);
};

Q_DECLARE_METATYPE(GameManager::GameStates)

#endif // GAMEMANAGER_H
