#include "Strategy.hpp"

class SparseStrategy : public Strategy {
    static const int SPARSE_POINT = 1;
    public: 
        int bonus() {
            return SPARSE_POINT;
        }
};