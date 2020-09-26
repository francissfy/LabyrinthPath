//
//  main.cpp
//  MF_ZMT
//
//  Created by Francis on 2020/9/25.
//  Copyright © 2020 Francis. All rights reserved.
//

#include <iostream>
#include <vector>

#include "container.hpp"
#include "utils.hpp"


int main(int argc, const char * argv[]) {
    if (argc != 2) {
        fprintf(stderr, "ERROR: please provide exactly one option among -Stack, -Queue!\n");
        exit(-1);
    } else if (strcmp(argv[1], "-Stack") == 0) {
        std::vector<MAP_T> map_array = ParseMap();
        for (MAP_T& map: map_array) {
            DFS(map);
            TraceBack(map); // print out answer
            PrintTraceVerbose(map); // visualize the path, for debugging's ease
        }
    } else if (strcmp(argv[1], "-Queue") == 0) {
        std::vector<MAP_T> map_array = ParseMap();
        for (MAP_T& map: map_array) {
            BFS(map);
            TraceBack(map);
            PrintTraceVerbose(map);
        }
    } else {
        fprintf(stderr, "ERROR: please provide exactly one option among -Stack, -Queue!\n");
        exit(-1);
    }
    return 0;
}
