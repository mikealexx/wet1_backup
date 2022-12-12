#include "Stats.h"

Stats::Stats(const int goals, const int cards, const int playerId):
    goals(goals),
    cards(cards),
    playerId(playerId)
{}

Stats::Stats():
    goals(),
    cards(),
    playerId()
{}

int Stats::getClosest(Stats* stats1, Stats* stats2){
    if(stats1 == nullptr && stats2 != nullptr) {
        return stats2->playerId;
    }
    else if(stats1 != nullptr && stats2 == nullptr) {
        return stats1->playerId;
    }
    int goalsDiff1 = abs(this->goals - stats1->goals);
    int goalsDiff2 = abs(this->goals - stats2->goals);
    if (goalsDiff1 > goalsDiff2){
        return stats2->playerId;
    }
    else if (goalsDiff1 < goalsDiff2){
        return stats1->playerId;
    }
    int cardsDiff1 = abs(this->cards - stats1->cards);
    int cardsDiff2 = abs(this->cards - stats2->cards);
    if (cardsDiff1 > cardsDiff2){
        return stats2->playerId;
    }
    else if (cardsDiff1 < cardsDiff2){
        return stats1->playerId;
    }
    int idDiff1 = abs(this->playerId - stats1->playerId);
    int idDiff2 = abs(this->playerId - stats2->playerId);
    if (idDiff1 > idDiff2){
        return stats2->playerId;
    }
    else if (idDiff1 < idDiff2){
        return stats1->playerId;
    }
    if (stats1->playerId > stats2->playerId){
        return stats1->playerId;
    } 
    return stats2->playerId;
}