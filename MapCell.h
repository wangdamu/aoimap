#pragma once

#include "VMap.h"
#include <iostream>
#include <map>
#include <vector>
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"

template<class T>
class Map;

template<class T>
class MapCell
{
private:
    unsigned int cellX;
    unsigned int cellY;

    boost::shared_ptr<std::map<int,  boost::shared_ptr<T>>> sprites;

    boost::shared_ptr<std::vector<boost::weak_ptr<MapCell<T>>>> surroundsCells;

public:
    MapCell(unsigned int cellX, unsigned int cellY);

    void removeSprite(boost::shared_ptr<T>& t);
    void addSprite(boost::shared_ptr<T>& t);

    inline void addSurroundCell(boost::weak_ptr<MapCell<T>>& mapCell){
        surroundsCells.get()->push_back(mapCell);
    }

    inline unsigned int getCellX() const{
        return cellX;
    }

    inline unsigned int getCellY() const{
        return cellY;
    }

    virtual ~MapCell(void);
};


template<class T>
MapCell<T>::MapCell(unsigned int cellX, unsigned int cellY):cellX(cellX),cellY(cellY)
{
}

template<class T>
void MapCell<T>::removeSprite(boost::shared_ptr<T>& t){
    auto itr = sprites.get()->find(t->getId());
    if(itr != sprites.get()->end()){
        sprites.get()->erase(itr);
    }
}

template<class T>
void MapCell<T>::addSprite(boost::shared_ptr<T>& t){
    (*(sprites.get()))[t->getId()] = t;
    t.get()->setMapCell(this);
}

template<class T>
MapCell<T>::~MapCell(void)
{
    //delete sprites;
    //delete surroundsCells;
}