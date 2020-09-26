//
//  container.hpp
//  MF_ZMT
//
//  Created by Francis on 2020/9/25.
//  Copyright © 2020 Francis. All rights reserved.
//

// self-implemented queue and stack
// distincted by namespace prefix: my

#ifndef container_hpp
#define container_hpp

#include <iostream>
#include <vector>
#include <queue>


template <typename value_type>
class my_queue{
private:
    std::queue<value_type> queue;
public:
    my_queue() {}
    
    value_type dequeue() {
        value_type t = queue.front();
        queue.pop();
        return t;
    }
    
    void enqueue(const value_type& v) {
        queue.push(v);
    }
    
    size_t count() {
        return queue.size();
    }
    
    bool empty() {
        return queue.empty();
    }
    
};

template <typename value_type>
class my_stack{
private:
    std::vector<value_type> vec;
public:
    my_stack() {}
    
    void push(const value_type& v) {
        vec.push_back(v);
    }
    
    value_type pop() {
        value_type t = vec[vec.size()-1];
        vec.erase(vec.end()-1);
        return t;
    }
    
    size_t count() {
        return vec.size();
    }
    
    bool empty() {
        return vec.empty();
    }
    
};



#endif /* container_hpp */
