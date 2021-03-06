#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>

#include <eosio.token/eosio.token.hpp>

#include "../wallet.sx.hpp"

using namespace eosio;
using namespace std;

class [[eosio::contract("basic")]] example : public contract {

public:
	using contract::contract;

	[[eosio::action]]
	void deposit( const name account, const name contract, const asset quantity )
	{
		token::transfer_action transfer( contract, { account, "active"_n });
	    transfer.send( account, "wallet.sx"_n, quantity, "" );
	}

	[[eosio::action]]
	void withdraw( const name account, const name contract, const asset quantity )
	{
		walletSx::withdraw_action withdraw( "wallet.sx"_n, { account, "active"_n });
	    withdraw.send( account, contract, quantity );
	}

	[[eosio::action]]
	void move( const name from, const name to, const name contract, const asset quantity, const string memo )
	{
		walletSx::move_action move( "wallet.sx"_n, { from, "active"_n });
	    move.send( from, to, contract, quantity, memo );
	}

	[[eosio::action]]
	void internal( const name from, const name contract, const asset quantity )
	{
		walletSx::move_action move( "wallet.sx"_n, { "wallet.sx"_n, "active"_n });
	    move.send( from, get_self(), contract, quantity, "internal transfer" );
	}

	[[eosio::action]]
	void balance( const name account, const name contract, const symbol_code symcode )
	{
		const asset balance = walletSx::get_balance("wallet.sx"_n, account, contract, symcode );
		print( balance.to_string() );
	}
};
