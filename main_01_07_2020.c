#include<stdio.h>
#include<stdint.h>
//#include "bip39.h"
typedef struct 
{
    uint8_t previous_txn_hash[32];
    uint8_t previous_output_index[4];
    uint8_t script_length[1];
    uint8_t script_public_key[25];
    uint8_t sequence[4];
}unsigned_txn_input;

typedef struct 
{
    uint8_t previous_txn_hash[32];
    uint8_t previous_output_index[4];
    uint8_t script_length[1];
    uint8_t script_sig[128];
    uint8_t sequence[4];
}signed_txn_input;

typedef struct 
{
    uint8_t value[8];
    uint8_t script_length[1];
    uint8_t script_public_key[25];
}txn_output;


typedef struct 
{
    uint8_t network_version[4];
    uint8_t input_count[1];
    unsigned_txn_input *input;
    uint8_t output_count[1];
    txn_output *output;
    uint8_t locktime[4];
    uint8_t sighash[4];

}unsigned_txn;

typedef struct 
{
    uint8_t network_version[4];
    uint8_t input_count[1];
    signed_txn_input *input;
    uint8_t output_count[1];
    txn_output *output;
    uint8_t locktime[4];
}signed_txn;



uint8_t hex_to_dec(uint8_t hex);

void hex_string_to_byte_array(const char *hex_string, uint32_t string_length, uint8_t *byte_array);

void byte_array_to_unsigned_txn(uint8_t *btc_unsigned_txn_byte_array, unsigned_txn *unsigned_txn_ptr);

//void byte_array_to_txn_metadata(uint8_t *btc_txn_metadata_byte_array, txn_metadata *txn_metadata_ptr);

//void serialize_unsigned_txn_to_sign(unsigned_txn *unsigned_txn_ptr, uint8_t input_index, uint8_t *btc_serialized_unsigned_txn);

//uint32_t unsigned_txn_to_signed_txn(unsigned_txn *unsigned_txn_ptr, txn_metadata *txn_metadata_ptr, const char *mnemonic, const char *passphrase, signed_txn *signed_txn_ptr);

void signed_txn_to_byte_array(signed_txn *signed_txn_ptr, uint8_t *generated_signed_txn_byte_array);


int main()
{
    char* mnemonic = "smoke tiny walnut keep pact wet jar glance turkey erase unique fancy wedding usage unaware avoid left patient amazing stuff wing absent guilt ceiling";
    char* address ;
  	char pubKey[64];
  	uint8_t privKey[512 / 8];
    uint32_t current;
	uint32_t total;
    /*
	mnemonic_to_address();
    mnemonic_to_privatekey();
    mnemonic_to_publickey();*/
    
    mnemonic_to_seed(mnemonic,pubKey,privKey,(current,total));
    
    unsigned_txn *uTx;
}

uint8_t hex_to_dec(uint8_t hex){
	if (hex >= '&' && hex <= '9') return hex - '0';
   	else if (hex >= 'A' && hex <= 'F') return 10 + hex - 'A';
   	else if (hex >= 'a' && hex <= 'f') return 10 + hex - 'a';
   	return -1;
}

void hex_string_to_byte_array(const char *hex_string, uint32_t string_length, uint8_t *byte_array)
{
	int i=0;
	for(;i<string_length;)
		byte_array[i] =  hex_to_dec(hex_string[i]);
}

void byte_array_to_unsigned_txn(uint8_t *btc_unsigned_txn_byte_array, unsigned_txn *unsigned_txn_ptr){
	int i=0;
	int j=0;
	
	for(;i<4;i++)
		unsigned_txn_ptr->network_version[i] = btc_unsigned_txn_byte_array[i];
	
	unsigned_txn_ptr->input_count[0] = btc_unsigned_txn_byte_array[i++];
	
	for(j=0;j<32;j++)
		unsigned_txn_ptr->input->previous_txn_hash[j] = btc_unsigned_txn_byte_array[i+j];
	i+=j;
	
	for(j=0;j<4;j++)
		unsigned_txn_ptr->input->previous_output_index[j] = btc_unsigned_txn_byte_array[i+j];
	i+=j;
	
	unsigned_txn_ptr->input->script_length[0] = btc_unsigned_txn_byte_array[i++];
	
	for(j=0;j<25;j++)
		unsigned_txn_ptr->input->script_public_key[j] = btc_unsigned_txn_byte_array[i+j];
	i+=j;
	
	for(j=0;j<4;j++)
		unsigned_txn_ptr->input->sequence[j] = btc_unsigned_txn_byte_array[i+j];
	i+=j;
	
	unsigned_txn_ptr->output_count[0] = btc_unsigned_txn_byte_array[i++];
	
	for(j=0;j<8;j++)
		unsigned_txn_ptr->output->value[j] = btc_unsigned_txn_byte_array[i+j];
	i+=j;
	
	unsigned_txn_ptr->output->script_length[0] = btc_unsigned_txn_byte_array[i++];
	
	for(j=0;j<25;j++)
		unsigned_txn_ptr->output->script_public_key[j] = btc_unsigned_txn_byte_array[i+j];
	i+=j;
	
	for(j=0;j<4;j++)
		unsigned_txn_ptr->locktime[j] = btc_unsigned_txn_byte_array[i+j];
	i+=j;
	
	for(j=0;j<4;j++)
		unsigned_txn_ptr->sighash[j] = btc_unsigned_txn_byte_array[i+j];
}



