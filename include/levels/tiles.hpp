#ifndef TILES_HPP_30AHWVXM
#define TILES_HPP_30AHWVXM
#include "object.hpp"
#include <iostream>
#include <vector>
#include "config.h"
#include "coin.hpp"

namespace Levels {

    class Tiles : public Object {
        private:
            std::vector<Object> tiles_array;
            std::vector<Entities::Coin> coins;

        public:
            Tiles();
            Tiles(rapidjson::Value& value);
            std::vector<Object> get_tiles();
            std::vector<Entities::Coin> get_coins();
            ~Tiles();
    };
}
#endif /* end of include guard: TILES_HPP_30AHWVXM */
