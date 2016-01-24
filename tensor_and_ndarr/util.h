#include <iostream>
#include <vector>

std::vector<int> arg_put_back(std::string str, std::string back_str){
	std::vector<int> eraced, ret;
	for (auto a : back_str){
		size_t pos(str.find(a));
		if (std::string::npos != pos)
			eraced.push_back(pos);
	}

	bool flag;
	for (int i = 0; i < str.size(); i++){
		flag = false;
		for (auto a : eraced)
			if (i == a)
				flag = true;
		if (flag)
			continue;
		ret.push_back(i);
	}

	for (auto a : eraced)
		ret.push_back(a);

	return ret;
}

std::string put_back(std::string str, std::string back_str){
	std::string ret(str);
	for (auto a : back_str){
		size_t pos(ret.find(a));
		if (std::string::npos != pos)
			ret = ret.erase(pos, 1);
	}
	return ret + back_str;
}

template<typename T>
std::vector<T> arg_sort(std::vector<int> numlst, std::vector<T> vallst){
	std::vector<T> ret(numlst.size());

	for (int i = 0; i < numlst.size(); i++){
		ret[i] = vallst[numlst[i]];
	}
	return ret;
}

std::vector<int> str_align(std::string str1, std::string str2){

	std::vector<int> arg;

	for (int i = 0; i < str1.size(); i++){
		for (int j = 0; j < str2.size(); j++){
			if (str1[i] == str2[j])
				arg.push_back(j);
		}
	}
	return arg;
}
