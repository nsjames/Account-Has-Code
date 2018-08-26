# Account Has Code

This contract is an oracle that provides dapps with the ability to query whether a given account on the network
has code installed. If an account has run the `set_code` action with empty code and removed code from 
their account they will be removed from the oracle.

## Checking for accounts on the mainnet

The mainnet account for this contract is

## `codeaccounts`

You can query it within your contracts by calling the table and checking for the existence of an account.
If the singleton table comes back with no rows then the account does not exist.

Check out the `testcontract` for an example of how to use this from within your contracts.

