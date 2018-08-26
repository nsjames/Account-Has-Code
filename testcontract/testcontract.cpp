#include <eosiolib/eosio.hpp>
#include <eosiolib/singleton.hpp>

using namespace eosio;

class testcontract : contract {
private:

    typedef singleton<N(hascode), uint8_t> Accounts;

public:
    using contract::contract;
    testcontract( name self ) : contract(self){}

    // @abi action
    void testme(account_name account){
        bool exists = Accounts(N(codeaccounts), account).exists();
        if(exists) eosio_assert(false, "This account has code");
        else eosio_assert(false, "This account does not have code");
    }

};

EOSIO_ABI( testcontract, (testme) )