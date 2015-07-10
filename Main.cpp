#include "VMap.h"
#include "MySprite.h"

int main(){
    
    auto mapCells = boost::shared_ptr<std::map<int, boost::shared_ptr<MapCell<MySprite>>>>(new std::map<int, boost::shared_ptr<MapCell<MySprite>>>());
    unsigned int cellWidth = 10;
    unsigned int cellHeight = 10;
    unsigned int rowCount = 20;
    unsigned int columnCount = 20;
    boost::shared_ptr<VMap<MySprite>> vmapPtr = boost::shared_ptr<VMap<MySprite>>(new VMap<MySprite>(mapCells, cellWidth, cellHeight, rowCount, columnCount));
    
    vmapPtr->setCleanSpritesFlag(true);
    
    vmapPtr->initMapCells();
    
    int maxX = cellWidth * columnCount;
    int maxY = cellHeight * rowCount;
    for(int i = 0; i < 10; i++){
        unsigned randX = std::rand() % maxX;
        unsigned randY = std::rand() % maxY;

        //std::cout << "id:" << i << " (" << randX << "," << randY << ")" <<std::endl;

        vmapPtr->addToMap(boost::shared_ptr<MySprite>(new MySprite(i)), randX, randY);
    }
    
    
}