//
//  utils.hpp
//  MF_ZMT
//
//  Created by Francis on 2020/9/25.
//  Copyright © 2020 Francis. All rights reserved.
//

#ifndef utils_hpp
#define utils_hpp

#include <iostream>
#include <vector>
#include <limits>
#include "container.hpp"


enum class DIRECTION {
    N,
    E,
    S,
    W,
    X   // denotes unknown(used when init)
};

char DirectToChar(DIRECTION d);

enum class OBJECT {
    FREE,
    OBSTACLE,
    ENTRY,
    EXIT,
    TUNNEL,
};

// for print obj
char ObjectToChar(OBJECT obj);

typedef std::pair<int, int> PAIR_T;

// object type, distance, direction of previous
typedef std::tuple<OBJECT, int, DIRECTION> ELEM_T;

// map, 2-dimensional vector
typedef std::vector<std::vector<ELEM_T>> DIM2ARR_T;


typedef struct {
    DIM2ARR_T map;  // 2-dimensional array
    PAIR_T entry;   // entry point
    PAIR_T exit;    // exit point(exit and tunnel)
    PAIR_T size;    // map size
} MAP_T;

// bfs
void BFS(MAP_T& map);

// dfs
void DFS(MAP_T& map);

// trace back from exit to entry, print the route out
void TraceBack(const MAP_T& map);

// read from file and return an array of map object
std::vector<MAP_T> ParseMap();

//  print the map
void PrintMap(const MAP_T& map);

// print the map and the route
void PrintTraceVerbose(const MAP_T& map);

// print an array of map
void PrintMapArray(const std::vector<MAP_T>& map_array);


#endif /* utils_hpp */
