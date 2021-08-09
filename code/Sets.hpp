#ifndef SETS_H_
#define SETS_H_

#include <unordered_set>
#include <unordered_map>
#include <list>

using namespace std;

/**
 * @brief Auxiliary structure to manage a cell of a list used for the lex_p algorithm.
 */
struct Cell {

    /**  
     * @brief pointers to the next and previous cell of the list.
     */
    struct Cell *next, *back;

    /**
     * @brief values contained in the cell.
     */
    unordered_set<unsigned int> set_values;
};

/**
 * @brief Auxiliary structure that helps to implement the cells model of the lex_p algorithm.
 * In particular it allows to manage a cell that will contain the vertices and to keep track of the 
 * cell where a vertex is contained in a easy way.
 */
struct Sets {
public:
    /**
     * @brief Construct a new Sets object with a set of vertices that will be placed in a initial cell.
     * @param vertices set of vertices.
     */
    Sets(unordered_set<unsigned int> vertices);

    /**
     * @brief Get a vertex that is on the top of the list.
     * @return unsigned int vertex number.
     */
    unsigned int get();

    /**
     * @brief Remove a vertex in the set with a specific value, but do not remove its cell position.
     * @param vertex value of the vertex.
     */
    void remove(unsigned int vertex);

    /**
     * @brief Remove a vertex in the set with a specific value.
     * @param vertex value of the vertex.
     */
    void removeDefinitely(unsigned int vertex);

    /**
     * @brief Get the Vertex Position object that represents the current position of the vertex in the list.
     * @param vertex value to be searched.
     * @return Cell* object containing the vertex.
     */
    Cell* getVertexPosition(unsigned int vertex);

    /**
     * @brief Add to a cell the value of the vertex.
     * @param cell pointer to a cell in the set.
     * @param vertex value of the vertex to be added.
     */
    void addCell(Cell* cell, unsigned int vertex);

    /**
     * @brief Add a new cell to the set that will be placed above the previous cell specified in input. Then insert the vertex
     * value inside this cell.
     * @param prev_cell previous cell where the vertex where contained.
     * @param vertex value of the vertex to be added.
     */
    void addSet(Cell* prev_cell, unsigned int vertex);

    /**
     * @brief Get the number of vertices in the set.
     * @return unsigned int number of vertices in the set.
     */
    unsigned int size();

    /**
     * @brief Delete from the sets object the cells that are empty.
     */
    void clearEmptyCells();

private:
    /**
     * @brief Pointer to the first cell of the list.
     */
    struct Cell *sets;

    /**
     * @brief Structure that contains the positions of each vertex in the set.
     */
    unordered_map<unsigned int, Cell*> vertex_positions;

    /**
     * @brief List of cells that will be eliminated after the call of the clearEmptyList() funcion
     * 
     */
    list<Cell*> empty_cells;
};

#endif