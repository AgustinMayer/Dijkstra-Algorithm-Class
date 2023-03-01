#include "dijkstra.h"
#include <iostream>
#include <ostream>
#include <stdexcept>

Dijkstra::Dijkstra(int c_WALL, int c_FREE, int c_CM) : WALL(c_WALL), FREE(c_FREE), cmDistance(c_CM)
{
}

Dijkstra::~Dijkstra(){
    // Eliminar la matriz dinámica
    for (int i = 0; i < ROW; i++) {
        delete[] grid[i];
    }
    delete[] grid;
}

void Dijkstra::ejecDijkstra(int** matrix, int n, int m, int startX, int startY, int endX, int endY){

    try {
        path.clear();
        totalDistance = -1;
        ROW = n;
        COL = m;
        grid = matrix;

        // Verificar que las celdas de origen y destino son válidas y no son paredes
        if(!isValid(startX, startY) || !isValid(endX, endY) || grid[startX][startY] == 1 || grid[endX][endY] == 1) {
            throw std::invalid_argument("Flaco un punto es invalido");
        }

        // Arrays para representar los movimientos hacia arriba, abajo, izquierda y derecha
        int row[] = {-1, 0, 0, 1};
        int col[] = {0, -1, 1, 0};

        // Crear una matriz para almacenar las distancias desde (x1, startY) hasta todas las celdas
        int dist[ROW][COL];
        memset(dist, -1, sizeof(dist));
        dist[startX][startY] = 0;

        // Crear una cola para almacenar las celdas visitadas
        queue<Cell> q;
        q.push({startX, startY});

        // Recorrer la matriz utilizando BFS
        while(!q.empty()) {
            int x = q.front().x;
            int y = q.front().y;
            q.pop();

            // Revisar las celdas adyacentes
            for(int k = 0; k < 4; k++) {
                int r = x + row[k];
                int c = y + col[k];

                // Si la celda es válida, no es una pared y no ha sido visitada, calcular su distancia
                if(isValid(r, c) && grid[r][c] != 1 && dist[r][c] == -1) {
                    dist[r][c] = dist[x][y] + 1;
                    q.push({r, c});
                }
            }
        }

        // Si no se pudo llegar a la celda de destino, retornar -1
        if(dist[endX][endY] == -1) {
            throw std::invalid_argument("No existe un camino posible entre estas coordenadas");
        } else {
            int i = endX, j = endY;
            path.push_back({i, j});

            while(dist[i][j] != 0) {
                int minDist = INT_MAX;
                int newRow, newCol;

                for(int k = 0; k < 4; k++) {
                    int r = i + row[k];
                    int c = j + col[k];

                    if(isValid(r, c) && dist[r][c] != -1 && dist[r][c] < minDist) {
                        minDist = dist[r][c];
                        newRow = r;
                        newCol = c;
                    }
                }

                i = newRow;
                j = newCol;
                path.push_back({i, j});
            }
            // Mostrar las coordenadas del recorrido
            totalDistance = dist[endX][endY];
        }
    } catch (const std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
        throw e.what();
        return;
    } catch (...) {
        throw std::invalid_argument("Error inesperado");
        return;
    }
}
