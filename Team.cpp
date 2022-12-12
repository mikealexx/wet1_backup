#include "Team.h"

Team::Team(int id, int points):
    id(id),
    gamesPlayed(0),
    points(points),
    playersNum(0),
    goalKeepers(0),
    totalCards(0),
    totalGoals(0),
    topScorer(nullptr),
    nextKosher(nullptr)
{
    playersById = new AVLTree<Player, int>();
    playersByStats = new AVLTree<Player, Stats>();
}

Team::~Team() {
    this->setNextKosher(nullptr);
    delete (this->playersById);
    delete (this->playersByStats);
}

int Team::getID() const{
    return this->id;
}

int Team::getGamesPlayed() const{
    return this->gamesPlayed;
}

int Team::getPoints() const{
    return this->points;
}

int Team::getPlayersNum() const{
    return this->playersNum;
}

int Team::getTotalGoals() const {
    return this->totalGoals;
}

int Team::getTotalCards() const {
    return this->totalCards;
}

int Team::getGoalKeepers() const {
    return this->goalKeepers;
}

void Team::addGoalKeepers(int goalKeepers) {
    this->goalKeepers += goalKeepers;
}

void Team::addPlayersNum(int players) {
    this->playersNum += players;
}

void Team::addTotalGoals(int goals) {
    this->totalGoals += goals;
}

void Team::addTotalCards(int cards) {
    this->totalCards += cards;
}

void Team::addPoints(int points) {
    this->points += points;
}

void Team::addGamesPlayed(int games) {
    this->gamesPlayed += games;
}

void Team::setPlayersNum(int players) {
    this->playersNum = players;
}

shared_ptr<Player> Team::getTopScorer() const{
    return this->topScorer;
}

void Team::setTopScorer(shared_ptr<Player> player) {
    this->topScorer = player;
}

shared_ptr<Team> Team::getNextKosher() const{
    return this->nextKosher;
}

void Team::setNextKosher(shared_ptr<Team> team){
    this->nextKosher = team;
}

bool Team::isKosher() const {
    return (this->getPlayersNum() >= 11 && this->getGoalKeepers() >= 1);
}

AVLTree<Player, int>* Team::getPlayersById() const{
    return this->playersById;
}

AVLTree<Player, Stats>* Team::getPlayersByStats() const{
    return this->playersByStats;
}

/*
void Team::destruct(){
    this->setNextKosher(nullptr);
    delete (this->playersById);
    delete (this->playersByStats);
} */