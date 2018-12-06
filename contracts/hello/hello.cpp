#include <eosiolib/eosio.hpp>
using namespace eosio;

class hello : public eosio::contract {
  public:
      using contract::contract;

      /// @abi action 
      void hi( account_name user ) {
         using namespace std;
         std::hash<string> hasher;
         string s = "4e07408562bedb8b60ce05c1decfe3ad16b72230967de01f640b7e4729b49fce";
         print( "Hello, ", hasher(s) );
      }
};

EOSIO_ABI( hello, (hi) )
