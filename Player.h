#ifndef Player_h
#define Player_h

#include "Stats.h"
#include "Team.h"
#include <memory>

using std::shared_ptr;

class Team;

class Player {
    private:
        int id;
        int teamId;
        shared_ptr<Team> team;
        int gamesPlayed;
        int goals;
        int cards;
        bool goalKeeper;
        shared_ptr<Player> pre;
        shared_ptr<Player> succ;
        

    public:
        Player() = default;
        ~Player();
        Player(int id, int teamId, shared_ptr<Team> team, int gamesPlayed, int goals, int cards, bool goalKeeper);
        Player(const Player& other) = default;
        Player& operator=(const Player& other) = default;

        int getId() const;
        int getTeamId() const;
        shared_ptr<Team> getTeam() const;
        int getGamesPlayed() const;
        int gamesWithoutTeam() const;
        int getGoals() const;
        int getCards() const;
        Stats getStats() const;
        bool isGoalKeeper() const;
        shared_ptr<Player> getPre() const;
        shared_ptr<Player> getSucc() const;

        void setId(const int id);
        void setTeamId(const int teamId);
        void setTeam(shared_ptr<Team> myTeam);
        void addGamesPlayed(const int gamesPlayed);
        void addGoals(const int goals);
        void addCards(const int cards);
        void setGoalKeeper(const bool isGoalKeeper);
        void setPre(shared_ptr<Player> player);
        void setSucc(shared_ptr<Player> player);
        void updateStats(int gamesPlayed, int scoredGoals, int cardsReceived);
        void destruct();
};

#endif