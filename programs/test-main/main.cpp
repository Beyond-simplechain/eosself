//
// Created by 超超 on 2018/9/7.
//

#include <iostream>
#include <fc/container/flat_fwd.hpp>
#include <fc/io/varint.hpp>
#include <fc/io/enum_type.hpp>
#include <fc/crypto/sha224.hpp>
#include <fc/optional.hpp>
#include <fc/safe.hpp>
#include <fc/container/flat.hpp>
#include <fc/string.hpp>
#include <fc/io/raw.hpp>
#include <fc/static_variant.hpp>
#include <fc/smart_ref_fwd.hpp>
#include <fc/crypto/ripemd160.hpp>
#include <fc/fixed_string.hpp>
#include <fc/crypto/private_key.hpp>

using namespace std;

struct FFS {
	 uint32_t 	  id = 1;
	 string   	  name = "a";
	 bool 		  flag = false;
	 char 		  sex = 'M';
	 uint64_t     value[4] = {1,2,3,4};
	 vector<int>  values = {6,7,8};
}ff;

FC_REFLECT(FFS,(id)(name)(flag)(sex)(value)(values))

void print_hash(uint64_t hash[4], string desc = "hash") {
	cout << desc <<": [" ;
	for (int i=0;i<4;i++) {
		cout << hex << "0x" << hash[i] << ",";
	}
	cout << "]" << endl;
}


int main() {
	cout << "test-main" << endl;

	cout << fc::sha256::hash<int>(2).str() << endl;

	print_hash(fc::sha256::hash<int>(2)._hash, "int");

	print_hash(fc::sha256::hash<string>("encode")._hash, "string");

	print_hash(fc::sha256::hash<vector<int>>({1,0,0,8,6})._hash, "vector");

	print_hash(fc::sha256::hash<map<int,int>>({{1,1},{2,3}})._hash, "map");

	print_hash(fc::sha256::hash<int[4]>({1,2,3,4})._hash, "array");

	print_hash(fc::sha256::hash<FFS>(ff)._hash, "struct");

	print_hash(fc::sha256::hash(make_pair(make_pair(1,"a"), make_pair<int, vector<char>>(2, {'x','y'})))._hash, "pair");
   uint64_t hash[4] = {0,0,0,0};
//   memset(hash, 0, sizeof(hash));
	auto pairs = make_pair(make_pair(make_pair(1,"a"),make_pair<int, vector<char>>(2,{'x','y'})), hash);
	print_hash(fc::sha256::hash(pairs)._hash, "pairs");

	int a = 1;
	string b="a";
	fc::sha256::encoder enc;
	fc::raw::pack(enc, a);
	fc::raw::pack(enc, b);
//	print_hash(enc.result()._hash, "twice");



	int c = 2;
	fc::raw::pack(enc, c);
//	print_hash(enc.result()._hash, "third");

	vector<char> bytes = {'x','y'};
	fc::raw::pack(enc, bytes);




//	fc::raw::pack(enc, fc::sha256());

	print_hash(enc.result()._hash, "forth");

	cout << "========= sha test =========" << endl;

	print_hash(fc::sha256::hash((char*)(&hash[0]), 32)._hash, "hash");

	auto sha = fc::sha256();
	cout << dec << sizeof(hash) << " " << sizeof(hash[0]) << " " << sizeof(hash)/sizeof(hash[0])  << endl;
	memcpy(sha._hash, hash, sizeof(hash));

	print_hash(fc::sha256::hash(sha)._hash, "sha");


//	fc::raw::pack(enc, false);
//	fc::raw::pack(enc, 'M');
//	uint64_t arr[4] = {1,2,3,4};
//	fc::raw::pack(enc, arr);
//	vector<int> vec = {6,7,8};
//	fc::raw::pack(enc, vec);



}