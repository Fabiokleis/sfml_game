#ifndef TILESETMAP_HPP_6ZOHXKJ1
#define TILESETMAP_HPP_6ZOHXKJ1
#include <iostream>
#include "../rapidjson/document.h"

namespace Maps {

    class TileSetMap {
        private:
            int firstid;
            std::string source;
    
    
        public:
            
            TileSetMap(rapidjson::Value& value);
            TileSetMap();
            ~TileSetMap();
    
            int get_firstg_id();
    	    std::string get_source();
    };
}
#endif /* end of include guard: TILESETMAP_HPP_6ZOHXKJ1 */
