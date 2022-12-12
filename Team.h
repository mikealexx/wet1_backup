#ifndef Team_h
#define Team_h

#include "Player.h"
#include "AVLTree.h"
#include <memory>

using std::shared_ptr;

class Player;
class Player;

class Team {
    private:
        int id;
        int gamesPlayed;
        int points;
        int playersNum;
        int goalKeepers;
        int totalCards;
        int totalGoals;
        shared_ptr<Player> topScorer;
        shared_ptr<Team> nextKosher;
        AVLTree<Player, int>* playersById;
        AVLTree<Player, Stats>* playersByStats;


    public:
        Team() = delete;
        Team(int id, int points);
        ~Team();

        int getID() const;
        int getGamesPlayed() const;
        int getPoints() const;
        int getPlayersNum() const;
        int getTotalCards() const;
        int getTotalGoals() const;
        int getGoalKeepers() const;
        void addGoalKeepers(int goalKeepers);
        void addPlayersNum(int players);
        void addTotalGoals(int goals);
        void addTotalCards(int cards);
        void addPoints(int points);
        void addGamesPlayed(int games);
        void setPlayersNum(int players);
        shared_ptr<Player> getTopScorer() const;
        void setTopScorer(shared_ptr<Player> player);
        shared_ptr<Team> getNextKosher() const;
        void setNextKosher(shared_ptr<Team> team);
        bool isKosher() const;
        AVLTree<Player, int>* getPlayersById() const;
        AVLTree<Player, Stats>* getPlayersByStats() const;
        void destruct();
};

#endif