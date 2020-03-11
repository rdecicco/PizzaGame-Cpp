#include "include/Player.h"

Player::Player(QObject *parent):
    QObject(parent),
    m_playerId(0),
    m_state(PlayerStates::Alive),
    m_name(""),
    m_lastNumberOfEatenPizzas(0)
{
    setComboPizzasModel(0);
}

Player::Player(const Player& player, QObject* parent):
    Player(parent)
{
    m_playerId = player.m_playerId;
    m_state = player.m_state;
    m_name = player.m_name;
    m_lastNumberOfEatenPizzas = player.m_lastNumberOfEatenPizzas;
    m_eatPizzas = player.m_eatPizzas;
    m_canPass = player.m_canPass;
    setComboPizzasModel(0);
}

Player::Player(int playerId, const QString& name, QObject *parent):
    Player(parent)
{
    m_playerId = playerId;
    m_name = name;
}

Player& Player::operator=(const Player& player) {
    m_playerId = player.m_playerId;
    m_state = player.m_state;
    m_name = player.m_name;
    m_lastNumberOfEatenPizzas = player.m_lastNumberOfEatenPizzas;
    m_comboPizzasModel = player.m_comboPizzasModel;
    m_eatPizzas = player.m_eatPizzas;
    m_canPass = player.m_canPass;
    return *this;
}

bool Player::operator==(const Player& player) {
    return this->m_playerId == player.m_playerId && this->m_state == player.m_state && this->m_name == player.m_name && this->m_lastNumberOfEatenPizzas == player.m_lastNumberOfEatenPizzas;
}

bool Player::operator!=(const Player& player) {
    return this->m_playerId != player.m_playerId || this->m_state != player.m_state || this->m_name != player.m_name || this->m_lastNumberOfEatenPizzas != player.m_lastNumberOfEatenPizzas;
}

int Player::playerId() {
    return m_currentPlayer;
}

void Player::setPlayerId(int playerId) {
    m_playerId = playerId;
    emit playerIdChanged(m_playerId);
}

bool Player::currentPlayer() {
    return m_currentPlayer;
}

void Player::setCurrentPlayer(bool currentPlayer) {
    m_currentPlayer = currentPlayer;
    emit currentPlayerChanged(m_currentPlayer);
}

Player::PlayerStates Player::state() {
    return m_state;
}

void Player::setState(PlayerStates state) {
    m_state = state;
    emit stateChanged(m_state);
}

QString Player::name() {
    return m_name;
}

void Player::setName(const QString& name) {
    m_name = name;
    emit nameChanged(m_name);
}

uint Player::lastNumberOfEatenPizzas() {
    return m_lastNumberOfEatenPizzas;
}

void Player::setLastNumberOfEatenPizzas(uint lastNumberEatedPizzas) {
    m_lastNumberOfEatenPizzas = lastNumberEatedPizzas;
    emit lastNumberOfEatenPizzasChanged(m_lastNumberOfEatenPizzas);
}

QVariantList Player::comboPizzasModel() {
    return m_comboPizzasModel;
}

void Player::setComboPizzasModel(uint disabledValue) {
    m_comboPizzasModel.clear();
    for (uint i = 1; i < 4; i++) {
        if (i != disabledValue) {            
            QVariantMap item;
            item.insert("value", i);
            m_comboPizzasModel.push_back(item);
        }
    }
    emit comboPizzasModelChanged(m_comboPizzasModel);
}

void Player::setEatPizzas(std::function<bool(uint)> eatPizzas)
{
    m_eatPizzas = eatPizzas;
}

bool Player::eatPizzas(uint eatenPizzas)
{
    return m_eatPizzas(eatenPizzas);
}

void Player::setCanPass(std::function<bool()> canPass)
{
    m_canPass = canPass;
}

bool Player::canPass()
{
    return m_canPass();
}
