#pragma once
#include<iostream>
#include<iomanip>
#include<vector>
#include<string>
#include<numeric>
#include<cmath>
#include<cstdarg>
#include "utils.hpp"
using namespace std;

template<typename T>
class ndarr{
public:
	//typedef std::vector<ndarr<T> >::iterator iterator;
	//typedef std::vector<ndarr<T> >::const_iterator const_iterator;
	
	////begin, end
	//iterator begin(){ return ndarr<T>.begin(); }
	//const_iterator begin() const { return ndarr<T>.begin(); }
	//iterator end(){ return ndarr<T>.end(); }
	//const_iterator end() const {return ndarr<T>.end(); }

    vector<int> shape;
    int ndim;
    vector<T> v;
    //included ndarr_constructor.cpp----------------------
	ndarr(){}
    ndarr(initializer_list<int> list);
    ndarr(vector<T> vec, vector<int> tmp_shape);
//    ndarr(const ndarr<T> obj);
    //included ndarr_ref.cpp------------------------------
    ndarr<T> at(int n);
    //included ndarr_view.cpp-----------------------------
    void view();
    //included ndarr_operators.cpp------------------------
    ndarr<T> operator [](int n);
    ndarr<T> operator +(ndarr<T> obj);
    ndarr<T> operator -(ndarr<T> obj);
    ndarr<T> operator *(ndarr<T> obj);
    ndarr<T> operator /(ndarr<T> obj);
    ndarr<T> operator +(T val);
    ndarr<T> operator -(T val);
    ndarr<T> operator *(T val);
    ndarr<T> operator /(T val);
	ndarr<T>& operator =(T val);
	friend ostream& operator <<<T> (ostream& os,  ndarr<T> &arr);
	void view_rec_for_os(ostream &os, vector<int> arr, int w);
    //included ndarr_broadcast.cpp------------------------
    vector<int> check_shape(ndarr &obj);
    void broadcast(ndarr &obj);
    //included ndarr_transpose.cpp------------------------
    ndarr<T> transpose(vector<int> &t_lst);
    ndarr<T> transpose(int num, ...);
    //included ndarr_gen.cpp------------------------------
    void zeros();
    void range();
    //included ndarr_math.cpp-----------------------------
    ndarr<T> dot(ndarr<T> &obj);
    void dot_rec(ndarr<T> &obj, vector<int> arr);
    ndarr<T> diad(ndarr<T> &obj);
    void diad_rec(ndarr<T> &obj, vector<int> arr);
    ndarr<T> cross(ndarr<T> &obj);
    T min();
    T max();
    T sum();
    T mean();
private:
    vector<T> tmp_vec;
    int cnt;
    vector<T> tmp_v;
    int tmp;
    int size=1;
    string idxz;
    //included ndarr_ref.cpp------------------------------
    void at_rec(vector<int> tmp_shape);
    //included ndarr_view.cpp-----------------------------
    void view_rec(vector<int> arr, int w);
    //included ndarr_broadcast.cpp------------------------
    void broadcast_rec(int shape_n);
    //included ndarr_transpose.cpp------------------------
    void transpose_rec(int tmp2, vector<int> &mult_arr, vector<int> &arr);
};

// utils.cpp
//#include "ndarr.hpp"

template<typename T>
ndarr<T> zeros(initializer_list<int> list){
	ndarr<T> ret{list};
	ret =0;
	return ret;
}

template<typename T>
ndarr<T> zeros(std::vector<int> list){
	int total(1);
	for (auto a : list) total *= a;
	std::vector<T> v(total, 0);
	ndarr<T> ret(v, list);
	return ret;
}

template<typename T>
ndarr<T> ones(initializer_list<int> list){
	ndarr<T> ret{list};
	ret =1;
	return ret;
}

template<typename T>
ndarr<T> ones(std::vector<int> list){
	int total(1);
	for (auto a : list) total *= a;
	std::vector<T> v(total, 1);
	ndarr<T> ret(v, list);
	return ret;
}

template<typename T>
vector<T> slice(vector<T> v, int st, int en){
    vector<T> ret_v;
    for (int i=st; i<en; i++) ret_v.push_back(v[i]);
    return ret_v;
}

template<typename T, T Func(T)>
ndarr<T> ufunc(ndarr<T> obj){
    vector<T> ret_v;
    for (auto a:obj.v) ret_v.push_back(Func(a));
    ndarr<T> ret(ret_v, obj.shape);
    return ret;
}


// ndarr_constructor.cpp
template<typename T>
ndarr<T>::ndarr(initializer_list<int> list){
    for (auto a:list) shape.push_back(a);
    for (auto a:shape) size *= a;
    v.resize(size);
    ndim = shape.size();
}

template<typename T>
ndarr<T>::ndarr(vector<T> vec, vector<int> tmp_shape){
    shape = tmp_shape;
    v = vec;
    ndim = shape.size();
}

//template<typename T>
//ndarr<T>::ndarr(const ndarr<T> obj){
//    shape = obj.shape;
//    v = obj.v;
//    ndim = obj.shape.size();

//}
//ndarr_ref.cpp
template<typename T>
void ndarr<T>::at_rec(vector<int> tmp_shape){
    vector<T> pre_v;

    if (tmp_shape.size() == 1){
            int end = cnt + tmp_shape[0];
            
            for(int i=cnt; i<end; i++){ 
                tmp_vec.push_back(v[i]);
            }
            cnt = end;
            
    }
    else{
        vector<int> tmp_shape2 = slice(shape, 1, tmp_shape.size());
        for (int i = 0; i < tmp_shape[0]; i++) at_rec(tmp_shape2);
    }
}
    
template<typename T>
ndarr<T> ndarr<T>::at(int n){
    tmp_vec.clear();
    vector<int> ret_shape;
    if (shape.size() == 1) {
        tmp_vec.push_back(v[n]);
        ret_shape.push_back(1);
    }
    else{
        cnt = n;
        ret_shape = slice(shape, 1, shape.size());
        for (auto a:ret_shape) cnt *= a;
        at_rec(shape);
    }
    ndarr<T> ret_t(tmp_vec, ret_shape);
    return ret_t;
}
//template<typename T>
//ndarr<T> ndarr<T>::at(int n){
//    tmp_vec.clear();
//	std::vector<T> ;
//	for (for int i=-1; i = shape.size();i--)


//	
//    vector<int> ret_shape;
//    if (shape.size() == 1) {
//        tmp_vec.push_back(v[n]);
//        ret_shape.push_back(1);
//    }
//    else{
//        cnt = n;
//        ret_shape = slice(shape, 1, shape.size());
//        for (auto a:ret_shape) cnt *= a;
//        at_rec(shape);
//    }
//    ndarr<T> ret_t(tmp_vec, ret_shape);
//    return ret_t;
//}
// ndarr_view.cpp
template<typename T>
void ndarr<T>::view_rec(vector<int> arr, int w){
    int n = arr[0];
    if (arr.size() == 1){
        cout << "[";
        int end = cnt + arr[0];
        for(int i=cnt; i<end; i++){
            cout << scientific << setprecision(2) 
            << v[i] << " ";
        }
        cnt = end;
        cout << "]";
    }
    else{
        vector<int> arr2 = slice(arr, 1, arr.size());
        cout << "[";
        w++;
        view_rec(arr2, w);
        if (n != 1) cout << endl;
        for (int i = 1; i < n; i++){ 
            cout << setw(w);
            view_rec(arr2, w);
            if (i != n-1) cout << endl;
        }
        cout << "]";
    }

}

template<typename T>
void ndarr<T>::view(){
   cnt = 0;
   view_rec(shape, 1);
   cout << endl << endl;
}

template<typename T>
void ndarr<T>::view_rec_for_os(ostream &os, vector<int> arr, int w){
    int n = arr[0];
    if (arr.size() == 1){
        cout << "[";
        int end = cnt + arr[0];
        for(int i=cnt; i<end; i++){
            os << scientific << setprecision(2) 
            << v[i] << " ";
        }
        cnt = end;
        os << "]";
    }
    else{
        vector<int> arr2 = slice(arr, 1, arr.size());
        os << "[";
        w++;
        view_rec(arr2, w);
        if (n != 1) os << endl;
        for (int i = 1; i < n; i++){ 
            os << setw(w);
            view_rec(arr2, w);
            if (i != n-1) os << endl;
        }
        os << "]";
    }
}

template<typename T>
ostream& operator <<(ostream& os, ndarr<T> &arr){
   arr.cnt = 0;
   arr.view_rec_for_os(os, arr.shape, 1);
   os  << endl << endl;
   return os;
}

template<typename T>
void ndarr<T>::broadcast_rec(int shape_n){
    vector<T> tmp_v(v);
    shape.insert(shape.begin(), shape_n);
    for (int i=0; i<shape_n-1; i++)
        v.insert(v.end(), tmp_v.begin(), tmp_v.end());
}

template<typename T>
void ndarr<T>::broadcast(ndarr &obj){
   try{
       vector<int> conca_shape(check_shape(obj));
        enum objects which_is_small = shape.size() < obj.shape.size() ? THIS : OBJ;
        switch(which_is_small){
            case THIS:
                for (auto a:conca_shape) broadcast_rec(a);
                break;
            case OBJ:
                for (auto a:conca_shape) obj.broadcast_rec(a);
                break;
        }

   } catch(const char*  mismatch){
       cerr << mismatch << endl;
       exit(1);
   }
}

// ndarr_transpose.cpp
//template<typename T>
//void ndarr<T>::transpose_rec(int tmp2, vector<int> &mult_arr, vector<int> &arr){
//    int n = arr[0];
//    int mult = mult_arr[0];
//    if (arr.size() == 1){
//        for(int i=0; i<n; i++){
//            tmp_v[mult*i+tmp2] = v[i+cnt];
//        }
//        cnt += n;
//      
//    }
//    else{
//        vector<int> arr2 = slice(arr, 1, arr.size());
//        vector<int> mult_arr2 = slice(mult_arr, 1, mult_arr.size());
//        for (int i = 0; i < n; i++){ 
//            transpose_rec(tmp2,mult_arr2, arr2);
//            tmp2 += mult;
//        }
//        tmp = 0;
//    }
//}


//template<typename T>
//ndarr<T> ndarr<T>::transpose(vector<int> &t_lst){
//    int n(t_lst.size());
//    vector<int> t_shape(n); 
//    vector<int> t_shape2(n); 
//    vector<int> mult_t_shape(n,1); 
//    vector<int> mult_shape(n);
//    for (int i=0; i<n; i++) t_shape[i] = shape[t_lst[i]];
//    for (int i=n-1; i>=0; i--) t_shape2[i] = shape[t_lst[i]];
//    int mul(1);
//    for (int i=shape.size()-1; i>=0; i--) {
//        mult_shape[i] = mul;
//        mul *= t_shape[i];
//    }
//    for (int i=0; i<n; i++) mult_t_shape[i] = mult_shape[t_lst[i]];
//    cnt = 0;
//    tmp_v.clear();
//    tmp_v.resize(v.size());
//    tmp =0;
//    
//    transpose_rec(0, mult_t_shape, shape);
//    ndarr<T> ret_arr(tmp_v, t_shape);
//    return ret_arr;
//}

template<typename T>
ndarr<T> ndarr<T>::transpose(vector<int> &t_lst){
    vector<int> D_idx = t_lst, D(ndim);
    for (int j=0; j<ndim; j++) D[j] = shape[D_idx[j]];

	int num_j(shape.size());
	std::vector<int> B(num_j, 1), C(num_j, 1);
	int cnt(1);
	for (int j = num_j-1; j > 0; j--){
		cnt *= D[j];
		B[j-1] = cnt;
	}

	std::vector<int> B2(num_j, 1);
	std::vector<int> t_B(num_j, 1);
	cnt = 1;
	for (int j = num_j-1; j > 0; j--){
		cnt *= shape[j];
		B2[j-1] = cnt;
	}

    for (int j=0; j<ndim; j++) t_B[j] = B2[D_idx[j]];

	cnt = 1;
	for (int j = num_j-1; j >= 0; j--){
		cnt *= D[j];
		C[j] = cnt;
	}

	int num_k(1);
	for (auto a : D)
		if (num_k < a)
			num_k = a;

	std::vector < std::vector<int> > M(num_k, std::vector<int>(num_j, 0));
	std::vector<int> R(num_k, 0);
	for (int k = 0; k < num_k; k++){
		for (int j = 0; j < num_j; j++){
			if (k < D[j])
				M[k][j] = 1;
		}
		R[k] = k;
	}


	int num_i(1);
	for (auto a : shape)
		num_i *= a;

	std::vector<std::vector < std::vector<int> > > u(num_i, 
		std::vector < std::vector<int> > (num_j,
		std::vector<int>(num_k, 0)));

	int rec_i;
	for (int i = 0; i < num_i; i++){
		for (int j = 0; j < num_j; j++){
			for (int k = 0; k < num_k; k++){
				if (i > C[j])
					rec_i = i%C[j];
				else
					rec_i = i;
				if ((rec_i >= B[j]*R[k]) && (rec_i < B[j]*R[k] + B[j]))
						u[i][j][k] = 1;
			}
		}
	}

	std::vector<int> a(num_i, 0);
	for (int i = 0; i < num_i; i++){
		for (int j = 0; j < num_j; j++){
			for (int k = 0; k < num_k; k++){
				a[i] += R[k] * M[k][j] * t_B[j] * u[i][j][k];
			}
		}
	}

	std::vector<T> t_v(num_i);
	for (int i = 0; i < num_i; i++){
		t_v[i] = v[a[i]];
	}

	ndarr<T> ret_arr(t_v, D);

    return ret_arr;
}

//template<typename T>
//ndarr<T> ndarr<T>::transpose(int num, ...){
//    va_list args;
//    vector<int> t_lst(ndim);

//    va_start(args, num);
//    t_lst[0] = num;
//    for (int i=1; i<ndim; i++) t_lst[i] = va_arg(args, int);
//    ndarr<T> ret_arr(transpose(t_lst));
//    va_end(args);
//    return ret_arr;
//}

template<typename T>
ndarr<T> ndarr<T>::transpose(int num, ...){
    va_list args;
    vector<int> D_idx(ndim), D(ndim);

    va_start(args, num);
    D_idx[0] = num;
    for (int i=1; i<ndim; i++) D_idx[i] = va_arg(args, int);
    va_end(args);

	return transpose(D_idx);

}


// ndarr_gen.cpp
template<typename T>
void ndarr<T>::zeros(){
    show(shape);
    for (int i = 0; size > i; i++)
        v[i] = 0;
}



template<typename T>
void ndarr<T>::range(){
    for (int i = 0; size > i; i++)
        v[i] = i;
}

    


template<typename T>
ndarr<T> permutation_symbol(int n){
    int plus;
    int minus;
    int quo;
    int mod;
    vector<int> ret_shape;
    vector<T> ret_v(pow(n,n));
    vector<int> comp_v;
    bool unique;
    for(int i=0; i<pow(n,n); i++){
        plus = 0;
        minus = 0;
        quo = i;
        comp_v.clear();
        unique = true;

        for (int j=n-1; j>=0; j--){
            mod  = quo % n;
            quo /= n;
            for (auto a:comp_v)
                if(a == mod) unique = false;
            comp_v.push_back(mod);
            if (mod - j == 0) continue;
            (mod - j) < 0 ? minus++ : plus++;
        }
        if (!unique) ret_v[i] = 0;
        else if (minus > plus) ret_v[i] = minus % 2 ? -1 : 1;
        else  ret_v[i] = plus % 2  ? -1 : 1;
    }
    for (int i = 0; i<n; i++) ret_shape.push_back(n);
    ndarr<T> ret_arr(ret_v, ret_shape);
    return ret_arr;
}

// ndarr_math.cpp
template<typename T>
T ndarr<T>::max(){
    T max(v[0]);
    for (int i = 1; v.size() > i; i++){
        if (max < v[i]) max = v[i];
    }
    return max;
}

template<typename T>
T ndarr<T>::min(){
    T min(v[0]);
    for (int i = 1; v.size() > i; i++){
        if (min > v[i]) min = v[i];
    }
    return min;
}

template<typename T>
T ndarr<T>::sum(){
    T sum(0);
    for (int i = 0; v.size() > i; i++){
        sum += v[i];
    }
    return sum;
}

template<typename T>
T ndarr<T>::mean(){
    return sum() / v.size();
}

template<typename T>
void ndarr<T>::dot_rec(ndarr<T> &obj, vector<int> arr){
    int n = arr[0];
    if (arr.size() == 1){
        T ret_val(0);
        for(int j=0; j<obj.v.size(); j+=n){

            ret_val = 0;
            for(int i=0; i<n; i++){
               ret_val += v[i+cnt] * obj.v[i+j];
            }
            tmp_v.push_back(ret_val);
        }
        cnt += n;
    } else{
        vector<int> arr2 = slice(arr, 1, arr.size());
        for (int i = 0; i < n; i++){ 
            dot_rec(obj, arr2);
        }
    }
}

template<typename T>
ndarr<T> ndarr<T>::dot(ndarr<T> &obj){
   cnt = 0;
   tmp_v.clear();
   dot_rec(obj, shape);

   vector<int> conca_shape(shape);
   vector<int> obj_shape(obj.shape);
   conca_shape.pop_back();
   obj_shape.pop_back();
   conca_shape.insert(conca_shape.end(), obj_shape.begin(), obj_shape.end());
   ndarr<T> ret_arr(tmp_v, conca_shape);
   tmp_v.clear();
   return ret_arr;
}

template<typename T>
ndarr<T> ndarr<T>::diad(ndarr<T> &obj){
    tmp_v.clear();
    for(int j=0; j < v.size(); j++){
        for(int i=0; i< obj.v.size(); i++){
                tmp_v.push_back(v[i] * obj.v[j]);}
        }
    vector<int> conca_shape(shape);
    conca_shape.insert(conca_shape.end(), obj.shape.begin(), obj.shape.end());
    ndarr<T> ret_arr(tmp_v, conca_shape);
    tmp_v.clear();
    return ret_arr;
}


template<typename T>
ndarr<T> ndarr<T>::cross(ndarr<T> &obj){
    ndarr<T> arr(permutation_symbol<T>(shape[shape.size()-1]));
    ndarr<T> dot1(obj.dot(arr));
    ndarr<T> dot2(dot(dot1));
    ndarr<T> ret_arr(dot2);
    return ret_arr;
}