#pragma once

#include <iostream>
#include <map>
#include "MapCell.h"
#include "MapHelper.h"
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"

//using namespace boost;

template<class T>
class MapCell;

template<class T>
class VMap
{
private:
    unsigned int cellWidth;
    unsigned int cellHeight;
    unsigned int rowCount;
    unsigned int columnCount;

    boost::shared_ptr<std::map<int, boost::shared_ptr<MapCell<T>>>> mapCells;

    boost::shared_ptr<std::map<int, boost::shared_ptr<T>>> sprites;
    bool cleanSprites;
public:
    VMap(){
       new(this) VMap(nullptr, 0, 0, 0, 0);
    }

    VMap(boost::shared_ptr<std::map<int, boost::shared_ptr<MapCell<T>>>>& mapCells, const unsigned int cellWidth, const unsigned int cellHeight, const unsigned int rowCount, const unsigned int columnCount):
        mapCells(mapCells), cellWidth(cellWidth), cellHeight(cellHeight), rowCount(rowCount), columnCount(columnCount){
        sprites = boost::shared_ptr<std::map<int, boost::shared_ptr<T>>>(new std::map<int, boost::shared_ptr<T>>());
    }

    void addToMap(boost::shared_ptr<T>& t, unsigned int x, unsigned int y);

    inline void setCleanSpritesFlag(const bool cleanSprites){
        this->cleanSprites = cleanSprites;
    }

    void initMapCells();

    virtual ~VMap(void);
        
};

template<class T>
void VMap<T>::addToMap(boost::shared_ptr<T>& t, unsigned int x, unsigned int y){
    unsigned int cellX = x / cellWidth * cellWidth;
    unsigned int cellY = y / cellHeight * cellHeight;

    MapCell<T>* oldMapCell = t.get()->getMapCell();
    auto it = mapCells.get()->find(MapHelper::getCellKey(cellX, cellY));
    if(it != mapCells.get()->end()){
        boost::shared_ptr<MapCell<T>> mapCell =  it->second;
        if(mapCell.get() != oldMapCell){
            if(oldMapCell != nullptr){
                oldMapCell->removeSprite(t);
            }
            mapCell.get()->addSprite(t);
            std::cout<< "id:" << t->getId() << " (" << x << "," << y << ")" << " cell(" << mapCell.get()->getCellX() << "," << mapCell.get()->getCellY() << ")" << std::endl;
        }
    }else{
       if(oldMapCell != nullptr){
            oldMapCell->removeSprite(t);
        }
    }
}

template<class T>
void VMap<T>::initMapCells(){
    for(int i = 0; i < columnCount; i++){
        for(int j = 0; j < rowCount; j++){
            unsigned int cellX = i * cellWidth;
            unsigned int cellY = j * cellHeight;
            (*(mapCells.get()))[MapHelper::getCellKey(cellX, cellY)] = boost::shared_ptr<MapCell<T>>(new MapCell<T>(cellX, cellY));
            //mapCells->insert(std::map<int, T>::value_type (MapHelper::getCellKey(cellX, cellY), mapCell));
        }
    }

    std::cout<<mapCells.get()->size()<<std::endl;
   
    auto it = mapCells.get()->begin();
    while (it != mapCells.get()->end())
    {
        boost::shared_ptr<MapCell<T>> mapCell = it->second;
        if(mapCell.get() != nullptr){
            unsigned int cellX = mapCell.get()->getCellX();
            unsigned int cellY = mapCell.get()->getCellY();
            if(cellX > 0){
                //left cell
                auto it = mapCells.get()->find(MapHelper::getCellKey(cellX - cellWidth, cellY));
                boost::shared_ptr<MapCell<T>> leftCell = it->second;
                mapCell.get()->addSurroundCell(boost::weak_ptr<MapCell<T>>(leftCell));
                if(cellY > 0){
                    //左下角
                    auto it = mapCells.get()->find(MapHelper::getCellKey(cellX - cellWidth, cellY - cellHeight));
                   boost::shared_ptr<MapCell<T>>  leftBottomCell = it->second;
                    mapCell.get()->addSurroundCell(boost::weak_ptr<MapCell<T>>(leftBottomCell));
                }
                 if(cellY < (rowCount - 1) * cellHeight){
                     //左上角
                     auto it = mapCells->find(MapHelper::getCellKey(cellX - cellWidth, cellY + cellHeight));
                    boost::shared_ptr<MapCell<T>> leftTopCell = it->second;
                    mapCell.get()->addSurroundCell(boost::weak_ptr<MapCell<T>>(leftTopCell));
                 }
            }
            if(cellX < (columnCount - 1) * cellWidth){
                //添加右边的cell
                 auto it = mapCells->find(MapHelper::getCellKey(cellX + cellWidth, cellY));
                boost::shared_ptr<MapCell<T>> rightCell = it->second;
                mapCell.get()->addSurroundCell(boost::weak_ptr<MapCell<T>>(rightCell));
                if(cellY > 0){
                    //右下角
                    auto it = mapCells->find(MapHelper::getCellKey(cellX + cellWidth, cellY - cellHeight));
                    boost::shared_ptr<MapCell<T>> rightBottomCell = it->second;
                    mapCell.get()->addSurroundCell(boost::weak_ptr<MapCell<T>>(rightBottomCell));
                }
                 if(cellY < (rowCount - 1) * cellHeight){
                     //右上角
                    auto it = mapCells->find(MapHelper::getCellKey(cellX + cellWidth, cellY + cellHeight));
                    boost::shared_ptr<MapCell<T>> rightTopCell = it->second;
                    mapCell.get()->addSurroundCell(boost::weak_ptr<MapCell<T>>(rightTopCell));
                 }
            }
            if(cellY > 0){
                //添加下面的cell
                 auto it = mapCells->find(MapHelper::getCellKey(cellX, cellY - cellHeight));
                boost::shared_ptr<MapCell<T>> bottomCell = it->second;
                mapCell.get()->addSurroundCell(boost::weak_ptr<MapCell<T>>(bottomCell));
            }
            if(cellY < (rowCount - 1) * cellHeight){
                //添加上面的cell
                 auto it = mapCells->find(MapHelper::getCellKey(cellX, cellY + cellHeight));
                boost::shared_ptr<MapCell<T>> topCell = it->second;
                mapCell.get()->addSurroundCell(boost::weak_ptr<MapCell<T>>(topCell));
            }
        }
        it++;
    }
}

template<class T>
VMap<T>::~VMap(void){
   
}

