#pragma once
class MapHelper
{
public:
    inline static int getCellKey(unsigned int cellX, unsigned int cellY){
        return (cellX << 16) | cellY;
    }
};

