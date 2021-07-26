#ifndef SETS_H_
#define SETS_H_

#include <unordered_set>
#include <unordered_map>
#include <list>

using namespace std;

struct Cell {
    struct Cell *next, *back;
    unordered_set<unsigned int> set_values;
};

struct Sets {
public:

    Sets(unordered_set<unsigned int> vertices);
    unsigned int get();
    void remove(unsigned int vertex);
    void removeDefinitely(unsigned int vertex);
    Cell* getVertexPosition(unsigned int vertex);
    void addCell(Cell* cell, unsigned int vertex);
    void addSet(Cell* prev_cell, unsigned int vertex);
    unsigned int size();
    void clearEmptyCells();

private:
    struct Cell *sets;
    unordered_map<unsigned int, Cell*> vertex_positions;
    list<Cell*> empty_cells;
};

#endif