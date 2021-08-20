# Advanced Algorithm Project 
#### Consonni Andrea
#### Personal code: 10560164 
#### Matricola: 945095

## <ins> Repository description </ins>

Code folder contains all the C++ files necessary to create and manage a graph. 
Graph.hpp contains the three functions to be tested (fill_in, lex_p, lex_m) and the structures that define the graph. The other .hpp and .cpp files are auxiliary structures.

Test folder is divided into three sections. The unit_test folder contains files to verify the correct behaviour of the project. Temporal folder contains files to assess the temporal complexity of the project functions. Spatial folder contains files to profile the memory consumption of the project functions.

Other stuff folder contains the presentation and some collected data.

## <ins> Requirements </ins>

* BOOST (Version 1.74.0)
* Google Benchmark
* Valgrind
* Make utility

## <ins> How to compile and execute</ins>

To make the project work it's necessary to fix inside the makefile the BOOSTDIR and BENCHINC variables. More information can be found inside the makefile.

Unit tests:
`make unit_test`

Assess temporal complexity of fill_in function: <br/>
`make temporal_fill`

Similarly for the other functions: <br/>
`make temporal_lex_p` <br/>
`make temporal_lex_m` 

Memory profiling <br/>
It's mandatory to define a variable `NUM_ELEMENTS = x` that represents the sum between the number of vertices and the number of edges that will be contained in the graph.

Profiling fill_in <br/>
`make spatial_fill NUM_ELEMENTS = <elements>`

Similarly for the other functions: <br/>
`make spatial_lex_p NUM_ELEMENTS = <elements>` <br/>
`make spatial_lex_m NUM_ELEMENTS = <elements>` 

Example (fill_in) <br/>
`make spatial_fill NUM_ELEMENTS = 128`

The line above profiles the fill_in function that will have a number of elements equal to 128 (elements = num_vertices + num_edges).

Clean the out files produced by the previous commands. <br/>
`make clear`




