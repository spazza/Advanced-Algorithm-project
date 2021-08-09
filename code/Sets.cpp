#include "Sets.hpp"

/**
 * @brief Construct a new Sets object with a set of vertices that will be placed in a initial cell.
 * @param vertices set of vertices.
 */
Sets::Sets(unordered_set<unsigned int> vertices) {
    sets = new Cell();
    sets->back = NULL;
    sets->next = NULL;

    for(auto vertex : vertices) {
        sets->set_values.insert(vertex);
        vertex_positions[vertex] = sets;
    } 
}

/**
 * @brief Get a vertex that is on the top of the list.
 * @return unsigned int vertex number.
 */
unsigned int Sets::get() {
    return *(sets->set_values.begin());
}

/**
 * @brief Remove a vertex in the set with a specific value, but do not remove its cell position.
 * @param vertex value of the vertex.
 */
void Sets::remove(unsigned int vertex) {
    if(vertex_positions.find(vertex) != vertex_positions.end()) {
        vertex_positions[vertex]->set_values.erase(vertex);
        if(vertex_positions[vertex]->set_values.size() == 0)
            empty_cells.push_back(vertex_positions[vertex]);
    }
}

/**
 * @brief Remove a vertex in the set with a specific value.
 * @param vertex value of the vertex.
 */
void Sets::removeDefinitely(unsigned int vertex) {
    if(vertex_positions.find(vertex) != vertex_positions.end()) {
        remove(vertex);
        vertex_positions.erase(vertex);
    }
}

/**
 * @brief Get the Vertex Position object that represents the current position of the vertex in the list.
 * @param vertex value to be searched.
 * @return Cell* object containing the vertex.
 */
Cell* Sets::getVertexPosition(unsigned int vertex) {
    if(vertex_positions.find(vertex) != vertex_positions.end())
        return vertex_positions[vertex];
    else
        return NULL;
}

/**
 * @brief Add to a cell the value of the vertex.
 * @param cell pointer to a cell in the set.
 * @param vertex value of the vertex to be added.
 */
void Sets::addCell(Cell* cell, unsigned int vertex) {
    if(vertex_positions.find(vertex) != vertex_positions.end()) {
        cell->set_values.insert(vertex);
        vertex_positions[vertex] = cell;
    }
}

/**
 * @brief Add a new cell to the set that will be placed above the previous cell specified in input. Then insert the vertex
 * value inside this cell.
 * @param prev_cell previous cell where the vertex where contained.
 * @param vertex value of the vertex to be added.
 */
void Sets::addSet(Cell* prev_cell, unsigned int vertex) {
    if(vertex_positions.find(vertex) != vertex_positions.end()) {
        
        Cell *new_cell = new Cell();

        new_cell->back = prev_cell;
        new_cell->next = prev_cell->next;

        if(prev_cell->next != nullptr) 
            prev_cell->next->back = new_cell;

        prev_cell->next = new_cell;

        addCell(new_cell, vertex);  

        // if the new cell is the first update sets
        if(new_cell->next == nullptr)
            sets = new_cell;
    }
}

/**
 * @brief Get the number of vertices in the set.
 * @return unsigned int number of vertices in the set.
 */
unsigned int Sets::size() {
    return vertex_positions.size();
}


/**
 * @brief Delete from the sets object the cells that are empty.
 */
void Sets::clearEmptyCells() {
    for(auto cell : empty_cells) {
        if(cell == sets) 
            sets = sets->back;

        if(cell->next != nullptr && cell->back != nullptr) {
            cell->next->back = cell->back;
            cell->back->next = cell->next;
        }

        if(cell->next == nullptr && cell->back != nullptr)
            cell->back->next = nullptr;

        if(cell->next != nullptr && cell->back == nullptr) 
            cell->next->back = nullptr;
        
        delete cell;
    }
    empty_cells.clear();
}