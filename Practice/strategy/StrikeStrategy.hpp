#include "Strategy.hpp"

class StrikeStrategy : public Strategy {
    static const int STRIKE_POINT = 1;
    public: 
        int bonus() {
            return STRIKE_POINT;
        }
};