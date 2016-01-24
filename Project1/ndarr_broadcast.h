#pragma once
#include "ndarr_decl.h"

enum objects {THIS, OBJ};
template<typename T>
vector<int> ndarr<T>::check_shape(ndarr &obj){
    enum objects which_is_small = shape.size() < obj.shape.size() ? THIS : OBJ;
    vector<int> small_shape;
    vector<int> large_shape;
    switch(which_is_small){
        case THIS:
            small_shape = shape;
            large_shape = obj.shape;
            //vector<int> ret_shape(shape);
            break;
        case OBJ:
            small_shape = obj.shape;
            large_shape = shape;
            break;
    }

    cnt = 0;
    for (int i=1; i<=small_shape.size(); i++){
        if( shape[shape.size()-i] != obj.shape[obj.shape.size()-i]) throw "shape mismatch.";
        large_shape.pop_back();
        
    }

    return large_shape;
}
