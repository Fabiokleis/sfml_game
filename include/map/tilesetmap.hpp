#include <iostream>
#include "document.h"
#pragma once

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
