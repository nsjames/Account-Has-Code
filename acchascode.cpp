#include <eosiolib/eosio.hpp>
#include <eosiolib/singleton.hpp>

using namespace eosio;

class acchascode : contract {
private:

    // @abi table trustees
    struct Trustee {
        account_name account;

        account_name primary_key() const { return account; }
        EOSLIB_SERIALIZE( Trustee, (account) )
    };

    // @abi table hascode i64
    struct boolwrap {
        uint64_t coded;
    };

    typedef multi_index<N(trustees), Trustee> Trustees;
    typedef singleton<N(hascode), boolwrap> Accounts;

public:
    using contract::contract;
    acchascode( name self ) : contract(self){}

    // @abi action
    void trustee(account_name account){
        require_auth(_self);
        Trustees trustees(_self, _self);
        auto exists = trustees.find(account);
        if(exists != trustees.end()) trustees.erase(exists);
        else trustees.emplace(_self, [&](auto& record){
            record.account = account;
        });
    }

    // @abi action
    void add(account_name account, account_name trustee, uint8_t remove){
        eosio_assert(is_account(account), "account does not exist");
        require_auth(trustee);
        eosio_assert(remove == 0 || remove == 1, "remove must be either a 1 or a 0");

        Trustees trustees(_self, _self);
        eosio_assert(trustees.find(trustee) != trustees.end(), "Trustee is not a trusted oracle seeder");

        if(remove == 0){
            if(!Accounts(_self, account).exists())
                Accounts(_self, account).set(boolwrap{1}, _self);
        } else if (remove == 1) {
            if(Accounts(_self, account).exists())
                Accounts(_self, account).remove();
        }
    }

};

EOSIO_ABI( acchascode, (trustee)(add) )