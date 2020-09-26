//
//  utils.cpp
//  MF_ZMT
//
//  Created by Francis on 2020/9/25.
//  Copyright © 2020 Francis. All rights reserved.
//

#include "utils.hpp"


void BFS(MAP_T& map) {
    int size_r = map.size.first;
    int size_c = map.size.second;
    
    my_queue<PAIR_T> queue = my_queue<PAIR_T>();
    // enqueue entry point
    std::get<1>(map.map[map.entry.first][map.entry.second]) = 0;
    queue.enqueue(map.entry);
    
    while (!queue.empty()) {
        PAIR_T p = queue.dequeue();
        int r = p.first;
        int c = p.second;
        int current_dist = std::get<1>(map.map[r][c]);
        // visit four neighbor
        if (r>0
            &&  std::get<1>(map.map[r-1][c]) == INT_MAX
            && std::get<0>(map.map[r-1][c]) != OBJECT::OBSTACLE) {
            ELEM_T& elem = map.map[r-1][c];
            std::get<1>(elem) = current_dist+1;
            std::get<2>(elem) = DIRECTION::N;
            
            queue.enqueue(std::make_pair(r-1, c));
        }
        if (c+1<size_c
            &&  std::get<1>(map.map[r][c+1]) == INT_MAX
            && std::get<0>(map.map[r][c+1]) != OBJECT::OBSTACLE) {
            ELEM_T& elem = map.map[r][c+1];
            std::get<1>(elem) = current_dist+1;
            std::get<2>(elem) = DIRECTION::E;
            
            queue.enqueue(std::make_pair(r, c+1));
        }
        if (r+1<size_r
            && std::get<1>(map.map[r+1][c]) == INT_MAX
            && std::get<0>(map.map[r+1][c]) != OBJECT::OBSTACLE) {
            ELEM_T& elem = map.map[r+1][c];
            std::get<1>(elem) = current_dist+1;
            std::get<2>(elem) = DIRECTION::S;
            
            queue.enqueue(std::make_pair(r+1, c));
        }
        if (c>0
            &&  std::get<1>(map.map[r][c-1]) == INT_MAX
            && std::get<0>(map.map[r][c-1]) != OBJECT::OBSTACLE) {
            ELEM_T& elem = map.map[r][c-1];
            std::get<1>(elem) = current_dist+1;
            std::get<2>(elem) = DIRECTION::W;
            
            queue.enqueue(std::make_pair(r, c-1));
        }
    }
}


void DFS(MAP_T& map) {
    int size_r = map.size.first;
    int size_c = map.size.second;
    my_stack<PAIR_T> stack = my_stack<PAIR_T>();
    
    std::get<1>(map.map[map.entry.first][map.entry.second]) = 0;
    stack.push(map.entry);
    
    while (!stack.empty()) {
        //
        PAIR_T p = stack.pop();
        
        int r = p.first;
        int c = p.second;
        int current_dist = std::get<1>(map.map[r][c]);
        // visit four neighbor
        if (c>0
            &&  std::get<1>(map.map[r][c-1]) == INT_MAX
            && std::get<0>(map.map[r][c-1]) != OBJECT::OBSTACLE) {
            ELEM_T& elem = map.map[r][c-1];
            std::get<1>(elem) = current_dist+1;
            std::get<2>(elem) = DIRECTION::W;
            
            stack.push(std::make_pair(r, c-1));
        }
        if (r+1<size_r
            && std::get<1>(map.map[r+1][c]) == INT_MAX
            && std::get<0>(map.map[r+1][c]) != OBJECT::OBSTACLE) {
            ELEM_T& elem = map.map[r+1][c];
            std::get<1>(elem) = current_dist+1;
            std::get<2>(elem) = DIRECTION::S;
            
            stack.push(std::make_pair(r+1, c));
        }
        if (c+1<size_c
            &&  std::get<1>(map.map[r][c+1]) == INT_MAX
            && std::get<0>(map.map[r][c+1]) != OBJECT::OBSTACLE) {
            ELEM_T& elem = map.map[r][c+1];
            std::get<1>(elem) = current_dist+1;
            std::get<2>(elem) = DIRECTION::E;
            
            stack.push(std::make_pair(r, c+1));
        }
        if (r>0
            &&  std::get<1>(map.map[r-1][c]) == INT_MAX
            && std::get<0>(map.map[r-1][c]) != OBJECT::OBSTACLE) {
            ELEM_T& elem = map.map[r-1][c];
            std::get<1>(elem) = current_dist+1;
            std::get<2>(elem) = DIRECTION::N;
            
            stack.push(std::make_pair(r-1, c));
        }
    }
}


char DirectToChar(DIRECTION d) {
    switch (d) {
        case DIRECTION::N:
            return 'N';
        case DIRECTION::E:
            return 'E';
        case DIRECTION::S:
            return 'S';
        case DIRECTION::W:
            return 'W';
        default:
            return 'X';
    }
}


char ObjectToChar(OBJECT obj) {
    switch (obj) {
        case OBJECT::OBSTACLE:
            return '@';
        case OBJECT::FREE:
            return '.';
        case OBJECT::ENTRY:
            return 'I';
        case OBJECT::EXIT:
            return 'E';
        case OBJECT::TUNNEL:
            return 'T';
        default:
            return 'X';
    }
}


void TraceBack(const MAP_T& map) {
    std::vector<DIRECTION> tmp;
    DIRECTION direct = DIRECTION::X;
    
    int r = map.exit.first;
    int c = map.exit.second;
    
    // NSEW
    // add additional one step
    if (std::get<0>(map.map[r][c]) == OBJECT::EXIT) {
        if (r==0) {
            tmp.push_back(DIRECTION::N);
        } else if(r == map.size.first-1){
            tmp.push_back(DIRECTION::S);
        } else if (c == map.size.second-1) {
            tmp.push_back(DIRECTION::E);
        } else {
            tmp.push_back(DIRECTION::W);
        }
    }
    
    while (true) {
        if (r == map.entry.first && c == map.entry.second) {
            break;
        }
        direct = std::get<2>(map.map[r][c]);
        tmp.push_back(direct);
        switch (direct) {
            case DIRECTION::N:
                r++;
                break;
            case DIRECTION::E:
                c--;
                break;
            case DIRECTION::S:
                r--;
                break;
            case DIRECTION::W:
                c++;
                break;
            default:
                break;
        }
    }
    std::for_each(tmp.rbegin(), tmp.rend(), [](const DIRECTION d){
        std::cout<<DirectToChar(d);
    });
    std::cout<<std::endl;
}


std::vector<MAP_T> ParseMap() {
    int map_num;
    int row, col;
    char tmp;
    std::cin>>map_num;
    std::vector<MAP_T> map_array = std::vector<MAP_T>(map_num);
    
    for (int map_iter=0; map_iter<map_num; map_iter++) {
        // iter per map
        std::cin>>row>>col;
        // init map
        MAP_T& map = map_array[map_iter];
        map.size = std::make_pair(row, col);
        DIM2ARR_T dim2array = std::vector<std::vector<ELEM_T>>(row);
        for (int i=0; i<row; i++) {
            dim2array[i] = std::vector<ELEM_T>(col);
            for (int j=0; j<col; j++) {
                dim2array[i][j] = std::make_tuple(OBJECT::FREE, INT_MAX, DIRECTION::X);
            }
        }
        // parse map
        for (int row_iter=0; row_iter<row; row_iter++) {
            // iter per row
            for (int col_iter=0; col_iter<col; col_iter++) {
                std::cin>>tmp;
                ELEM_T& p = dim2array[row_iter][col_iter];
                if (tmp == '@') {
                    std::get<0>(p) = OBJECT::OBSTACLE;
                } else if (tmp == '.') {
                    std::get<0>(p) = OBJECT::FREE;
                } else if (tmp == 'I') {
                    std::get<0>(p) = OBJECT::ENTRY;
                    map.entry = std::make_pair(row_iter, col_iter);
                } else if(tmp == 'O'){
                    std::get<0>(p) = OBJECT::EXIT;
                    map.exit = std::make_pair(row_iter, col_iter);
                } else {
                    // T
                    std::get<0>(p) = OBJECT::TUNNEL;
                    map.exit = std::make_pair(row_iter, col_iter);
                }
            }
        }
        map.map = std::move(dim2array);
    }
    return map_array;
}


void PrintMap(const MAP_T& map) {
    printf("size: %dX%d\n", map.size.first, map.size.second);
    printf("entry: %dX%d; exit: %dX%d\n", map.entry.first, map.entry.second, map.exit.first, map.exit.second);
    for (const auto& row: map.map) {
        for (const auto& col: row) {
            std::cout<<ObjectToChar(std::get<0>(col));
            std::cout<<":"<<DirectToChar(std::get<2>(col))<<" ";
        }
        std::cout<<std::endl;
    }
}


void PrintTraceVerbose(const MAP_T& map) {
    int size_r = map.size.first;
    int size_c = map.size.second;
    
    char** char_map = new char*[size_r];
    for (int i=0; i<size_r; i++) {
        char_map[i] = new char[size_c];
    }
    // copy map
    for (int r=0; r<size_r; r++) {
        for (int c=0; c<size_c; c++) {
            char_map[r][c] = ObjectToChar(std::get<0>(map.map[r][c]));
        }
    }
    
    std::vector<DIRECTION> tmp;
    DIRECTION direct = DIRECTION::X;
    
    int r = map.exit.first;
    int c = map.exit.second;
    
    // add trace route
    while (true) {
        if (r == map.entry.first && c == map.entry.second) {
            break;
        }
        direct = std::get<2>(map.map[r][c]);
        char_map[r][c] = '*';
        switch (direct) {
            case DIRECTION::N:
                r++;
                break;
            case DIRECTION::E:
                c--;
                break;
            case DIRECTION::S:
                r--;
                break;
            case DIRECTION::W:
                c++;
                break;
            default:
                break;
        }
    }
    // exit is been override to *
    // recover exit
    char_map[map.exit.first][map.exit.second] =
        ObjectToChar(std::get<0>(map.map[map.exit.first][map.exit.second]));
    
    for (int r=0; r<size_r; r++) {
        for (int c=0; c<size_c; c++) {
            if (char_map[r][c] == '*') {
                printf("\033[0;31;40m*\033[0m");
            } else {
                printf("%c", char_map[r][c]);
            }
        }
        printf("\n");
    }
}


void PrintMapArray(const std::vector<MAP_T>& map_array) {
    int index= 0;
    for(const MAP_T& map: map_array) {
        printf("##########MAP: %d #########\n", index);
        PrintMap(map);
        index++;
    }
}
