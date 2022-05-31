#ifndef TILESETWRAPPER_HPP_6ZOHXKJ1
#define TILESETWRAPPER_HPP_6ZOHXKJ1
#include <iostream>
#include "../rapidjson/document.h"

namespace Levels {

    class TileSetWrapper {
        private:
            int firstid;
            std::string source;

        public:
            TileSetWrapper(rapidjson::Value& value);
            TileSetWrapper();
            ~TileSetWrapper();
    
            int get_firstg_id() const;
    	    std::string get_source();
    };
}
#endif /* end of include guard: TILESETWRAPPER_HPP_6ZOHXKJ1 */
