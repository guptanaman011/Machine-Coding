#include "Strategy.hpp"

class DefaultStrategy : public Strategy {
    static const int DEFAULT_POINT = 1;
    public: 
        int bonus() {
            return DEFAULT_POINT;
        }
};