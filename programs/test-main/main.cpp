//
// Created by 超超 on 2018/9/7.
//

#include <iostream>
#include <vector>
#include <set>

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

#include <eosio/chain/block_header_state.hpp>
#include <eosio/chain/producer_schedule.hpp>
#include <eosio/chain/types.hpp>
#include <eosio/chain/controller.hpp>
#include <eosio/chain/incremental_merkle.hpp>
#include <eosio/chain/merkle.hpp>

#include <exception>


using namespace std;
using namespace eosio::chain;

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

void block_header_state_digest() {
	auto pbk = public_key_type(std::string("EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV") );

	vector<producer_key> pks;
	pks.push_back(producer_key{N(eosio), pbk});
	pks.push_back(producer_key{N(yuanc), pbk});
	pks.push_back(producer_key{N(tester), pbk});

	auto pst = producer_schedule_type{0, pks};

	auto bhs = block_header_state{};
	bhs.active_schedule   = pst;
	bhs.pending_schedule  = pst;
	bhs.pending_schedule_hash = fc::sha256::hash(pst);
	bhs.header 		       = signed_block_header{};
	bhs.header.timestamp  = block_timestamp_type(1162339200);
	bhs.id 					 = bhs.header.id();
	bhs.block_num			 = bhs.header.block_num();
	bhs.block_signing_key = pbk;

	cout << bhs.sig_digest().str() << endl;
}

void mercle_get_root() {
	incremental_merkle m;
	m.append(fc::sha256("00000043df9347b6d053a03a78499bc420acb05c5c3bec6acbd8d37a68b3f195"));
	m.append(fc::sha256("00000042332b70edb826b578924218b8b509c3dcb2011608829f9f5f85d983b0"));

	cout << m.get_root().str() << endl;
}

void mercle() {
	vector<digest_type> ids = {fc::sha256("00000043df9347b6d053a03a78499bc420acb05c5c3bec6acbd8d37a68b3f195"),
	fc::sha256("00000042332b70edb826b578924218b8b509c3dcb2011608829f9f5f85d983b0")};

	cout << eosio::chain::merkle(ids).str() << endl;
}

void print_ids(vector<digest_type> ids) {
	cout << "[";
	for (auto id : ids) {
		cout << id.str() << " ";
	}
	cout << "]" << endl;
}
void mercle_active_node() {
	incremental_merkle m;
	m.append(fc::sha256("00000043df9347b6d053a03a78499bc420acb05c5c3bec6acbd8d37a68b3f195"));
	print_ids(m._active_nodes);
	m.append(fc::sha256("00000042332b70edb826b578924218b8b509c3dcb2011608829f9f5f85d983b0"));
	print_ids(m._active_nodes);
	m.append(fc::sha256("0000002033c7b70cdeadd2e71aa0f4adf38579904656754d3f4d14b68444bc08"));
	print_ids(m._active_nodes);
	m.append(fc::sha256("00000030cf4390afd0b1755c166a83ac3c49a9c017ffb1c5ffb41df2e03e614b"));
	print_ids(m._active_nodes);
}

int main() {
	// mercle_get_root();
	using eosio::chain::detail::calcluate_max_depth;
	// cout << calcluate_max_depth(0) << endl;
	// cout << calcluate_max_depth(1) << endl;
	// cout << calcluate_max_depth(2) << endl;
	// cout << calcluate_max_depth(3) << endl;
	// mercle();
	mercle_active_node();
}
//namespace std {
//	 typedef unsigned int size_t;
//}

//extern "C" {
int main0() {

//	std::set<int> setint;
//	setint.lower_bound()
//	controller::config cfg;
//	controller c1(cfg);
//	c1.startup([](){ return false; });
//
////	controller c2(cfg);
////	c2.startup([](){ return true; });
//
//	fc::static_variant<FFS, int> trx;
//	trx = FFS{};


//	block_header_state_digest();

	string msg = "rethrow msg";

try {
	try {
		try {
			EOS_ASSERT(false, block_net_usage_exceeded, "exception ${what}", ("what", 1));
		} FC_CAPTURE_AND_RETHROW((msg))
	} catch (fc::exception &e) {
		edump((e.to_detail_string()));
		throw e;
	}
} FC_LOG_AND_DROP()

//	try {
//		assert(false);
//
//	} catch (std::exception) {
//		cerr << "std::exception" << endl;
//	} catch (...) {
//		cerr << "other exception" << endl;
//	}

//	try {
//		EOS_ASSERT(false, fc::exception, "eos assert");
//	} FC_LOG_AND_DROP()
//	const char *str = "4e07408562bedb8b60ce05c1decfe3ad16b72230967de01f640b7e4729b49fce";
//	string s = "4e07408562bedb8b60ce05c1decfe3ad16b72230967de01f640b7e4729b49fce";
//	size_t hash = size_t(str);
//	cout << dec << sizeof(size_t) << endl;
//	cout << dec << (std::hash<string>{}(s)) << endl;
//	cout << dec << *(uint32_t*)(str) << endl;
//	cout << dec << *(uint32_t*)(str) << endl;
//	hash = ((hash << 5) + hash) ^ 5381; /* (hash * 33) ^ c */
//	cout << size_t(hash) << endl;
//	cout << hash << endl;
//	cout << std::hash<string>{}(s) << endl;
//	cout << std::hash<size_t>{}(hash) << endl;
//	cout << std::hash<string>{}(s) << endl;
//	cout << size_t(std::hash<string>{}(s)) << endl;
//	block_header_state_digest();
	return 0;
}

int _main() {
	cout << "test-main" << endl;

//	cout << fc::sha256::hash<int>(2).str() << endl;
//
//	print_hash(fc::sha256::hash<int>(2)._hash, "int");
//
//	print_hash(fc::sha256::hash<string>("encode")._hash, "string");
//
//	print_hash(fc::sha256::hash<vector<int>>({1,0,0,8,6})._hash, "vector");
//
//	print_hash(fc::sha256::hash<map<int,int>>({{1,1},{2,3}})._hash, "map");

//   int arr[4] = {1,2,3,4};
	int arr = 1;
//   uint8_t arr[4] = {'1','2','3','4'};

	fc::array<char, 3> fcarr;
	fcarr.data[0] = '1';
	fcarr.data[1] = '1';
	fcarr.data[2] = '1';

//	print_hash(fc::sha256::hash(arr)._hash, "array");
//	print_hash(fc::sha256::hash(fcarr)._hash, "array");
	print_hash(fc::sha256::hash(fc::sha256::hash(arr))._hash, "array");

	/*print_hash(fc::sha256::hash<FFS>(ff)._hash, "struct");

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

	print_hash(fc::sha256::hash(sha)._hash, "sha");*/


//	fc::raw::pack(enc, false);
//	fc::raw::pack(enc, 'M');
//	uint64_t arr[4] = {1,2,3,4};
//	fc::raw::pack(enc, arr);
//	vector<int> vec = {6,7,8};
//	fc::raw::pack(enc, vec);



}
