#pragma once
#include "MapCell.h"
#include "boost/shared_ptr.hpp"


class MySprite
{
private:
    int id;
    MapCell<MySprite> * mapCell;
public:
    MySprite(int id):id(id){
        mapCell = nullptr;
    }
    ~MySprite(void);
    inline int getId(){
        return id;
    }

    inline MapCell<MySprite> * getMapCell() const{
        return mapCell;
    }

    inline void setMapCell(MapCell<MySprite> * mapCell){
        this->mapCell = mapCell;
    }
};

