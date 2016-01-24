#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "ndarr.h"
#include "util.h"



/// Tensor like class
// This class simplyfy calculating of multivaliates
// with tensor like calclus.
// The information of tensor-like calclus is indicated
// there.
template<typename T>
class tensor{
public:
	tensor(){}
	tensor(ndarr<T> set_arr, std::string set_idx = "i", std::string set_ud = "d");
	ndarr<T> arr;
	int ndim;
	std::string idx, ud;
	void view();
	void transpose(std::string str);
	int check_need_dot_product(tensor<T> &obj);
	void broadcast( tensor<T> &obj, ndarr<T> &arr1, ndarr<T> &arr2, std::string &sum_idx, std::string &sum_ud) ;
	std::vector<std::string> ud_check(tensor<T> &obj);

    //included tensor.cpp------------------------
    tensor<T> operator [](int n);
    tensor<T> operator +(tensor<T> obj);
    tensor<T> operator -(tensor<T> obj);
    tensor<T> operator *(tensor<T> obj);
    tensor<T> operator /(tensor<T> obj);
    tensor<T> operator %(tensor<T> obj);
    tensor<T> operator +(T val);
    tensor<T> operator -(T val);
    tensor<T> operator *(T val);
    tensor<T> operator /(T val);
    tensor<T> operator %(T val);
	tensor<T>& operator =(T val);

};

template<typename T>
tensor<T>::tensor(ndarr<T> set_arr, std::string set_idx, std::string set_ud)
	: arr(set_arr), idx(set_idx), ud(set_ud), ndim(set_arr.ndim){
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
void tensor<T>::transpose(std::string set_idx){
	int num(0);
	std::vector<int> numlst(set_idx.size());

	for (int i = 0; i < ndim; i++)
		numlst[i] = idx.find(set_idx[i]);

	arr = arr.transpose(numlst);
	idx = set_idx;
}

template<typename T>
std::vector<std::string> tensor<T>::ud_check(tensor<T> &obj){
	std::string ud_lst;
	for (int i = 0; i < obj.ndim; i++){
		int j(obj.idx.find(idx[i]));
		if (std::string::npos != j)
			if (ud[i] == obj.ud[j])
				obj.idx;
		ud_lst.push_back(idx[i]);
	}

	return ud_lst;
}

template<typename T>
tensor<T> tensor<T>::operator -(tensor<T> obj){
	std::string sum_idx, sum_ud;
	ndarr<T> arr1, arr2;
	broadcast(obj, arr1, arr2, sum_idx, sum_ud);
	tensor<T> ret_t(arr1 - arr2, sum_idx, sum_ud);
   return ret_t;
}

template<typename T>
tensor<T> tensor<T>::operator +(tensor<T> obj){
	std::string sum_idx, sum_ud;
	ndarr<T> arr1, arr2;
	broadcast(obj, arr1, arr2, sum_idx, sum_ud);
	tensor<T> ret_t(arr1 + arr2, sum_idx, sum_ud);
   return ret_t;
}

//template<typename T>
//tensor<T> tensor<T>::operator *(tensor<T> &obj){
//	std::string sum_idx, sum_ud;
//	ndarr<T> arr1, arr2;
//	tensor<T> ret_t;
//	broadcast(obj, arr1, arr2, sum_idx, sum_ud);
//	switch (check_need_dot_product(obj)){
//		case 0:
//			ret_t = tensor<T>(arr1 * arr2, sum_idx, sum_ud);
//			break;
//		case 1:
//			for (auto a : ud_check(obj)){
//				std::vector<int> tlst = arg_put_back(idx, a);
//				std::string idx = put_back(idx, a);
//				std::string t_idx, t_ud;
//				
//				for (auto b : tlst){
//					t_idx.push_back(idx[b]);
//					t_ud.push_back(ud[b]);
//				}
//				ret_t = tensor<T>(arr1.transpose(tlst).dot(arr2.transpose(tlst)), t_idx, t_ud);
//				break;
//			}
//	}
//   return ret_t;
//}

template<typename T>
int tensor<T>::check_need_dot_product(tensor<T> &obj){
	for (int i = 0; i < sum_idx.size(); i++){
		for (int j = 0; j < sum_idx.size(); j++){
			if (idx[i] == obj.idx[j]){
				if (ud[i] != obj.ud[j]){
					transpose(ud[i]);
					obj.transpose(ud[i]);
					break;
				}
			}
		}
	}
}

template<typename T>
tensor<T> tensor<T>::operator /(tensor<T> obj){
	std::string sum_idx, sum_ud;
	ndarr<T> arr1, arr2;
	broadcast(obj, arr1, arr2, sum_idx, sum_ud);
	tensor<T> ret_t(arr1 / arr2, sum_idx, sum_ud);
   return ret_t;
}

template<typename T>
tensor<T> tensor<T>::operator %(tensor<T> obj){
	std::string sum_idx, sum_ud;
	ndarr<T> arr1, arr2;
	broadcast(obj, arr1, arr2, sum_idx, sum_ud);
	tensor<T> ret_t(arr1 % arr2, sum_idx, sum_ud);
   return ret_t;
}

template<typename T>
void tensor<T>::broadcast( tensor<T> &obj, ndarr<T> &arr1, ndarr<T> &arr2, std::string &sum_idx, std::string &sum_ud) {
	std::string prod_idx;
	std::vector<int> sum_shape, prod_shape;
	for (int i = 0; i < obj.ndim; i++)
		if (std::string::npos == sum_idx.find(obj.idx[i])){
			sum_idx.push_back(obj.idx[i]);
			sum_ud.push_back(obj.ud[i]);
			sum_shape.push_back(obj.arr.shape[i]);
		}

	for (int i = 0; i < ndim; i++)
		if (std::string::npos == sum_idx.find(idx[i])){
			sum_idx.push_back(idx[i]);
			sum_ud.push_back(ud[i]);
			sum_shape.push_back(arr.shape[i]);
		}
	//aa..aa
	//std::string t_sum_idx = put_back(sum_idx, prod_idx);
	//std::vector<int> t_sum_num = arg_put_back(sum_idx, prod_idx);
	//std::vector<int> t_sum_shape = arg_sort(t_sum_num, sum_shape);
	//std::string t_idx = put_back(idx, prod_idx);
	//std::vector<int> t_num = arg_put_back(idx, prod_idx);
	//std::string t_obj_idx = put_back(obj.idx, prod_idx);
	//std::vector<int> t_obj_num = arg_put_back(obj.idx, prod_idx);
	std::string t_sum_idx = put_back(sum_idx, idx);
	std::vector<int> t_sum_num = arg_put_back(sum_idx, idx);
	std::vector<int> t_sum_shape = arg_sort(t_sum_num, sum_shape);
	std::string t_obj_sum_idx = put_back(sum_idx, obj.idx);
	std::vector<int> t_obj_sum_num = arg_put_back(sum_idx, obj.idx);
	std::vector<int> t_obj_sum_shape = arg_sort(t_obj_sum_num, sum_shape);

	ndarr<T> o(ones<T>(t_sum_shape).v, t_sum_shape);
	ndarr<T> o2(ones<T>(t_obj_sum_shape).v, t_obj_sum_shape);
	//arr.transpose(t_shape).view();
	o.view();
	//obj.arr.transpose(t_obj_shape).view();
	arr1 = (arr * o).transpose(t_sum_num);
	arr2 = obj.arr * o2;
	cout << arr1 << arr2 << endl;
	sum_idx = t_sum_idx;
}

template<typename T>
void tensor<T>::view(){
	std::cout << "idx:" << idx << std::endl
		<< "ud:" << ud << std::endl
		<< "arr:" << arr << std::endl;
}