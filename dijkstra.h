#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <stdlib.h>
#include <queue>
#include <cstring>
#include <conio.h>
#include <string>

using namespace std;

struct Cell {
    int x, y;
};

class Dijkstra
{
public:
    Dijkstra(int c_WALL = 1, int c_FREE = 0, int c_CM = 10);
    ~Dijkstra();

    //devolver la distancia calculada
    inline int getTotalDistance(){return totalDistance;}
    inline int getTotalDistance_cm(){return cmDistance*totalDistance;}

    //devolver la ruta calculada
    inline vector<Cell> getPath(){return path;}


    void ejecDijkstra(int** matrix, int n, int m, int startX, int startY, int endX, int endY);

    inline void setWall(int c_WALL, int c_FREE){ WALL = c_WALL; FREE = c_FREE; }

    inline void setCellDistance(int c_CM){ cmDistance = c_CM; }

private:
    int WALL, FREE;
    int ROW, COL;
    int **grid;
    vector<Cell> path;
    int x1, y1, x2, y2;
    int totalDistance, cmDistance;

    inline bool isValid(int row, int col) { return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);}

};

#endif // DIJKSTRA_H
