
// A Class for comparing players by the rules of get_closest_player.
class Stats {
public:
int goals;
int cards;
int playerId;

static int abs(int x) {
    return (x >= 0) ? x : -x;
}

Stats(const int goals, const int cards, const int playerId);

Stats();

int getClosest(Stats* stats1, Stats* stats2);

friend bool operator<(const Stats& l, const Stats& r) {
    if (l.goals < r.goals) {
        return true;
    }
    else if (l.goals == r.goals) {
        if (l.cards > r.cards) {
            return true;
        }
        else if (l.cards == r.cards) {
            if (l.playerId < r.playerId) {
                return true;
            }
        }
    }
    return false;
}

friend bool operator>(const Stats& l, const Stats& r) {
    return (r < l);
}

friend bool operator==(const Stats& l, const Stats& r) {
    return l.goals == r.goals && l.cards == r.cards && l.playerId == r.playerId;
}

friend bool operator!=(const Stats& l, const Stats& r) {
    return !(l == r);
}

};