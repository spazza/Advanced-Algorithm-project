#include "Sets.hpp"

Sets::Sets(unordered_set<unsigned int> vertices) {
    sets = new Cell();
    sets->back = NULL;
    sets->next = NULL;

    for(auto vertex : vertices) {
        sets->set_values.insert(vertex);
        vertex_positions[vertex] = sets;
    } 
}

unsigned int Sets::get() {
    return *(sets->set_values.begin());
}

void Sets::remove(unsigned int vertex) {
    if(vertex_positions.find(vertex) != vertex_positions.end()) {
        vertex_positions[vertex]->set_values.erase(vertex);
        if(vertex_positions[vertex]->set_values.size() == 0)
            empty_cells.push_back(vertex_positions[vertex]);
    }
}

void Sets::removeDefinitely(unsigned int vertex) {
    if(vertex_positions.find(vertex) != vertex_positions.end()) {
        remove(vertex);
        vertex_positions.erase(vertex);
    }
}

Cell* Sets::getVertexPosition(unsigned int vertex) {
    if(vertex_positions.find(vertex) != vertex_positions.end())
        return vertex_positions[vertex];
    else
        return NULL;
}

void Sets::addCell(Cell* cell, unsigned int vertex) {
    if(vertex_positions.find(vertex) != vertex_positions.end()) {
        cell->set_values.insert(vertex);
        vertex_positions[vertex] = cell;
    }
}

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

unsigned int Sets::size() {
    return vertex_positions.size();
}

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