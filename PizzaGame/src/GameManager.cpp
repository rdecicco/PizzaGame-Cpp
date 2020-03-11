#include <QRandomGenerator>
#include "include/GameManager.h"
#include <QtMath>
#include <QDateTime>

GameManager::GameManager(QObject *parent):
    QObject(parent),
    m_state(GameStates::GameOver),
    m_numberOfPizzas(0),
    m_playerA(Player(1, "Player A")),
    m_playerB(Player(2, "Player B")),
    m_pizzasGenerator(QRandomGenerator(QDateTime::currentDateTime().toTime_t()))
{

}

GameManager::GameStates GameManager::state() {
    return m_state;
}

void GameManager::newGame() {
    m_numberOfPizzas = 10 + m_pizzasGenerator.generate() % 11;
    m_playerA.setState(Player::PlayerStates::Alive);
    m_playerA.setLastNumberOfEatenPizzas(0);
    m_playerA.setCurrentPlayer(true);
    m_playerA.setEatPizzas([&](uint eatenPizzas){return eatPizzas(eatenPizzas);});
    m_playerA.setCanPass([&](){return canPass();});
    m_playerB.setState(Player::PlayerStates::Alive);
    m_playerB.setLastNumberOfEatenPizzas(0);
    m_playerB.setCurrentPlayer(false);
    m_playerB.setEatPizzas([&](uint eatenPizzas){return eatPizzas(eatenPizzas);});
    m_playerB.setCanPass([&](){return canPass();});
    m_state = GameStates::Game;
    emit numberOfPizzasChanged(m_numberOfPizzas);
    emit stateChanged(m_state);
}

bool GameManager::eatPizzas(uint numberOfEatenPizzas) {
    if (m_state != GameStates::Game)
        return false;

    Player& currentPlayer = m_playerA.currentPlayer() ? m_playerA : m_playerB;
    Player& otherPlayer = getOtherPlayer(currentPlayer.playerId());

    if (!currentPlayer.currentPlayer() || otherPlayer.currentPlayer())
        return false;

    if (numberOfEatenPizzas > m_numberOfPizzas)
        return false;

    currentPlayer.setLastNumberOfEatenPizzas(numberOfEatenPizzas);

    if (numberOfEatenPizzas == 0) {
        swapPlayers(currentPlayer, otherPlayer);
        return true;
    }

    m_numberOfPizzas -= numberOfEatenPizzas;
    emit numberOfPizzasChanged(m_numberOfPizzas);

    if (fullGame) {
        if (m_numberOfPizzas == 0) {
            currentPlayer.setState(Player::PlayerStates::Dead);
            emit dead(currentPlayer);
            m_state = GameStates::GameOver;
            emit stateChanged(m_state);
            return true;
        }
    }
    else
    {
        if (m_numberOfPizzas == 0 || m_numberOfPizzas == 1) {
            currentPlayer.setState(Player::PlayerStates::Dead);
            emit dead(currentPlayer);
            m_state = GameStates::GameOver;
            emit stateChanged(m_state);
            return true;
        }
        else if (m_numberOfPizzas == 2) {
            otherPlayer.setState(Player::PlayerStates::Dead);
            emit dead(otherPlayer);
            m_state = GameStates::GameOver;
            emit stateChanged(m_state);
            return true;
        }
    }

    swapPlayers(currentPlayer, otherPlayer);
    return true;
}

Player& GameManager::getOtherPlayer(int playerId) {
    if (m_playerA.playerId() == playerId)
        return m_playerB;
    return m_playerA;
}

bool GameManager::canPass() {
    Player* otherPlayer;
    if (m_playerA.currentPlayer()) {
        otherPlayer = &m_playerB;
    }
    else
    {
        otherPlayer = &m_playerA;
    }

    if (otherPlayer->lastNumberOfEatenPizzas() == 0)
        return false;

    for (uint i = 1; i < 4; i++) {
        if (i != otherPlayer->lastNumberOfEatenPizzas() && i<= m_numberOfPizzas)
        {
            return false;
        }
    }

    return true;
}

uint GameManager::numberOfPizzas() {
    return m_numberOfPizzas;
}

Player& GameManager::playerA() {
    return m_playerA;
}

Player& GameManager::playerB() {
    return m_playerB;
}

void GameManager::swapPlayers(Player &currentPlayer, Player &otherPlayer) {
    currentPlayer.setCurrentPlayer(false);
    otherPlayer.setCurrentPlayer(true);
    otherPlayer.setComboPizzasModel(currentPlayer.lastNumberOfEatenPizzas());
}
