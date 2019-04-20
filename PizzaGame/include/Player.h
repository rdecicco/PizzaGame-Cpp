#ifndef PLAYER_H
#define PLAYER_H

#include <QtCore>
#include <QString>

class Player: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int playerId MEMBER m_playerId READ playerId WRITE setPlayerId NOTIFY playerIdChanged)
    Q_PROPERTY(bool currentPlayer MEMBER m_currentPlayer READ currentPlayer WRITE setCurrentPlayer NOTIFY currentPlayerChanged)
    Q_PROPERTY(Player::PlayerStates state MEMBER m_state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QString name MEMBER m_name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(uint lastNumberOfEatenPizzas MEMBER m_lastNumberOfEatenPizzas READ lastNumberOfEatenPizzas WRITE setLastNumberOfEatenPizzas NOTIFY lastNumberOfEatenPizzasChanged)
    Q_PROPERTY(QVariantList comboPizzasModel MEMBER m_comboPizzasModel READ comboPizzasModel NOTIFY comboPizzasModelChanged)

public:
    enum class PlayerStates {
        Dead,
        Alive
    };

    Q_ENUM(PlayerStates)

    Player(QObject* parent=nullptr);
    Player(const Player& player, QObject* parent=nullptr);
    Player(int playerId, const QString &name, QObject* parent=nullptr);

    Player& operator=(const Player& player);

    bool operator==(const Player& player);
    bool operator!=(const Player& player);

    int playerId();
    void setPlayerId(int playerId);
    bool currentPlayer();
    void setCurrentPlayer(bool currentPlayer);
    PlayerStates state();
    void setState(PlayerStates state);
    QString name();
    void setName(const QString &name);
    uint lastNumberOfEatenPizzas();
    void setLastNumberOfEatenPizzas(uint lastNumberEatedPizzas);
    QVariantList comboPizzasModel();
    void setComboPizzasModel(uint disabledValue);

signals:
    void playerIdChanged(int playerId);
    void currentPlayerChanged(bool currentPlayer);
    void stateChanged(const PlayerStates& state);
    void nameChanged(const QString& name);
    void lastNumberOfEatenPizzasChanged(uint lastNumberOfEatenPizzas);
    void comboPizzasModelChanged(QVariantList comboPizzasModel);

private:
    bool m_currentPlayer;
    int m_playerId;
    PlayerStates m_state;
    QString m_name;
    uint m_lastNumberOfEatenPizzas;
    QVariantList m_comboPizzasModel;
};

#endif // PLAYER_H
