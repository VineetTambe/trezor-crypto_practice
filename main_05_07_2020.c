#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

#include "crypto/bip39.h"
#include "crypto/bip32.h"

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

typedef struct 
{
    uint8_t chain_index[4];
    uint8_t address_index[4];
}address_type;

typedef struct 
{
    uint8_t wallet_index[1];
    uint8_t purpose_index[4];
    uint8_t coin_index[4];
    uint8_t account_index[4];
    
    uint8_t input_count[1];
    address_type *input;
    
    uint8_t output_count[1];
    address_type *output;
    
    uint8_t change_count[1];
    address_type *change;

}txn_metadata;


uint8_t hex_to_dec(uint8_t hex);

void hex_string_to_byte_array(const char *hex_string, uint32_t string_length, uint8_t *byte_array);

void byte_array_to_unsigned_txn(uint8_t *btc_unsigned_txn_byte_array, unsigned_txn *unsigned_txn_ptr);
void byte_array_to_txn_metadata(uint8_t *btc_txn_metadata_byte_array, txn_metadata *txn_metadata_ptr);

void Masternode_to_addressNode_m_44_1_0_0(HDNode node);

void serialize_unsigned_txn_to_sign(unsigned_txn *unsigned_txn_ptr, uint8_t input_index, uint8_t *btc_serialized_unsigned_txn);

uint32_t unsigned_txn_to_signed_txn(unsigned_txn *unsigned_txn_ptr, txn_metadata *txn_metadata_ptr, const char *mnemonic, const char *passphrase, signed_txn *signed_txn_ptr);

void signed_txn_to_byte_array(signed_txn *signed_txn_ptr, uint8_t *generated_signed_txn_byte_array);

int main()
{
    char* mnemonic = "smoke tiny walnut keep pact wet jar glance turkey erase unique fancy wedding usage unaware avoid left patient amazing stuff wing absent guilt ceiling";
	char* address ;
  	char *passphrase = "";
  	uint8_t seed[512 / 8];
    uint32_t current;
	uint32_t total;
    /*
	mnemonic_to_address();
    mnemonic_to_privatekey();
    mnemonic_to_publickey();*/
    
    unsigned_txn *uTx;
    int i,len;
    const char *received_unsigned_txn_string = "02000000021245fe7c5455b43e73743d83ccb5587303586a4e9a5b8f56a3eb08593624bb02000000001976a914d46d05e6ac27683aa5d63a6efc44969798acf13688acfdffffff1245fe7c5455b43e73743d83ccb5587303586a4e9a5b8f56a3eb08593624bb02010000001976a914dacc24d8b195ce046a40caedd5e2e649beee4e3388acfdffffff01f4ff0000000000001976a9142d77ece155f6b80dcab97a373834543e4b70b3e988ac84431a0001000000";    
	const char *received_txn_metadata_string = "018000002c8000000180000000020000000000000001000000010000000001000000000000000200";
	
	len = sizeof(received_unsigned_txn_string)/2;
	uint8_t unsigned_txn_byte_array[len];
	hex_string_to_byte_array(received_unsigned_txn_string,len,&unsigned_txn_byte_array[0]);// converting string to byte array
	
	unsigned_txn *unsigned_txn_ptr;
	byte_array_to_unsigned_txn(unsigned_txn_byte_array, &unsigned_txn_ptr);// cast into the unsigned_txn structure
	
	len = sizeof(received_txn_metadata_string)/2;
	uint8_t txn_metadata_byte_array[len];
	hex_string_to_byte_array(received_txn_metadata_string,len,&txn_metadata_byte_array[0]);// converting string to byte array
	
	txn_metadata *txn_metadata_ptr;
	byte_array_to_txn_metadata(txn_metadata_byte_array, &txn_metadata_ptr);// cast into the txn_metadata structure
	
	signed_txn *signed_txn_byte_array;
	len = sizeof(unsigned_txn_input); 
    signed_txn_byte_array = (signed_txn*)malloc(len);
	
	
	mnemonic_to_seed( mnemonic,passphrase,seed,0 );

    HDNode node;

    hdnode_from_seed(&seed[0],64,"secp256k1",&node);
    hdnode_fill_public_key(&node);
    Masternode_to_addressNode_m_44_1_0_0(node);


    return 0;
}


uint8_t hex_to_dec(uint8_t hex){
	char *ref = "0123456789abcdef";
	int j=0;
    while(hex!=ref[j])
        j++;
	return (uint8_t)j;
}

void hex_string_to_byte_array(const char *hex_string, uint32_t string_length, uint8_t *byte_array)
{
	int i=0,j=0;
	char hex[2];
	for(;i<string_length;i+=2,j++)
	{
		hex[0] = hex_string[i];
		hex[1] = hex_string[i+1];
		//printf("%c",hex[0]);
		//printf("%c\t",hex[1]);
		byte_array[j] =  hex_to_dec(hex[0])*16+hex_to_dec(hex[1]);
	}
	/*
	for(;i<string_length;)
		byte_array[i] =  hex_to_dec(hex_string[i]);*/
}

void Masternode_to_addressNode_m_44_1_0_0(HDNode node)
{
    int i=0;
    printf("Master Node\n")    ;
    printf("%02x\n",node.depth);
    printf("%02x\n",node.child_num);
    for(i=0;i<32;i++)
        printf("%02x",node.chain_code[i]);

    printf("\n");    
    for(i=0;i<32;i++)
        printf("%02x",node.private_key[i]);

    printf("\n");
    for(i=0;i<32;i++)
        printf("%02x",node.public_key[i]);
    
    printf("\n\n");

    hdnode_private_ckd(&node,0x8000002C);
    hdnode_fill_public_key(&node);

    printf("Purpose Node 44' \n")    ;
    printf("%02x\n",node.depth);
    printf("%02x\n",node.child_num);
    for(i=0;i<32;i++)
        printf("%02x",node.chain_code[i]);

    printf("\n");    
    for(i=0;i<32;i++)
        printf("%02x",node.private_key[i]);

    printf("\n");
    for(i=0;i<32;i++)
        printf("%02x",node.public_key[i]);
    
    printf("\n\n");
    

    
    hdnode_private_ckd(&node,0x80000001);
    hdnode_fill_public_key(&node);

    
    printf("Coin Node 1' \n")    ;
    printf("%02x\n",node.depth);
    printf("%02x\n",node.child_num);
    for(i=0;i<32;i++)
        printf("%02x",node.chain_code[i]);

    printf("\n");    
    for(i=0;i<32;i++)
        printf("%02x",node.private_key[i]);

    printf("\n");
    for(i=0;i<32;i++)
        printf("%02x",node.public_key[i]);
    
    printf("\n\n");

    hdnode_private_ckd(&node,0x80000000);
    hdnode_fill_public_key(&node);

    
    printf("Account Node 1' \n")    ;
    printf("%02x\n",node.depth);
    printf("%02x\n",node.child_num);
    for(i=0;i<32;i++)
        printf("%02x",node.chain_code[i]);

    printf("\n");    
    for(i=0;i<32;i++)
        printf("%02x",node.private_key[i]);

    printf("\n");
    for(i=0;i<32;i++)
        printf("%02x",node.public_key[i]);
    
    printf("\n\n");

    
    hdnode_private_ckd(&node,0x00000000);
    hdnode_fill_public_key(&node);

    
    printf("Chain Node 0\n");
    printf("%02x\n",node.depth);
    printf("%02x\n",node.child_num);
    for(i=0;i<32;i++)
        printf("%02x",node.chain_code[i]);

    printf("\n");    
    for(i=0;i<32;i++)
        printf("%02x",node.private_key[i]);

    printf("\n");
    for(i=0;i<32;i++)
        printf("%02x",node.public_key[i]);
    
    printf("\n\n");

    hdnode_private_ckd(&node,0x00000000);
    hdnode_fill_public_key(&node);

    
    printf("Address Node 0\n");
    printf("%02x\n",node.depth);
    printf("%02x\n",node.child_num);
    for(i=0;i<32;i++)
        printf("%02x",node.chain_code[i]);

    printf("\n");    
    for(i=0;i<32;i++)
        printf("%02x",node.private_key[i]);

    printf("\n");
    for(i=0;i<32;i++)
        printf("%02x",node.public_key[i]);
    
    printf("\n\n");
}

void byte_array_to_unsigned_txn(uint8_t *btc_unsigned_txn_byte_array, unsigned_txn *unsigned_txn_ptr){
	uint32_t offset = 0, len = 0;
    
      len = sizeof(unsigned_txn_ptr->network_version);
      memcpy(unsigned_txn_ptr->network_version, (btc_unsigned_txn_byte_array+offset), len);
      offset += len;

      len = sizeof(unsigned_txn_ptr->input_count);
      memcpy(unsigned_txn_ptr->input_count, (btc_unsigned_txn_byte_array+offset), len);
      offset += len;

      len = (*unsigned_txn_ptr->input_count)*sizeof(unsigned_txn_input); 
      unsigned_txn_ptr->input = (unsigned_txn_input*)malloc(len);
    
      for (uint8_t i = 0; i < *unsigned_txn_ptr->input_count; i++)
      {
        len = sizeof(unsigned_txn_ptr->input[i].previous_txn_hash);
        memcpy(unsigned_txn_ptr->input[i].previous_txn_hash, (btc_unsigned_txn_byte_array+offset), len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->input[i].previous_output_index);
        memcpy(unsigned_txn_ptr->input[i].previous_output_index, (btc_unsigned_txn_byte_array+offset), len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->input[i].script_length);
        memcpy(unsigned_txn_ptr->input[i].script_length, (btc_unsigned_txn_byte_array+offset), len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->input[i].script_public_key);
        memcpy(unsigned_txn_ptr->input[i].script_public_key, (btc_unsigned_txn_byte_array+offset), len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->input[i].sequence);
        memcpy(unsigned_txn_ptr->input[i].sequence, (btc_unsigned_txn_byte_array+offset), len);
        offset += len;
      }

      len = sizeof(unsigned_txn_ptr->output_count);
      memcpy(unsigned_txn_ptr->output_count, (btc_unsigned_txn_byte_array+offset), len);
      offset += len;

      len = (*unsigned_txn_ptr->output_count)*sizeof(txn_output); 
      unsigned_txn_ptr->output = (txn_output*)malloc(len);

      for (uint8_t i = 0; i < *unsigned_txn_ptr->output_count; i++)
      {
        len = sizeof(unsigned_txn_ptr->output[i].value);
        memcpy(unsigned_txn_ptr->output[i].value, (btc_unsigned_txn_byte_array+offset), len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->output[i].script_length);
        memcpy(unsigned_txn_ptr->output[i].script_length, (btc_unsigned_txn_byte_array+offset), len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->output[i].script_public_key);
        memcpy(unsigned_txn_ptr->output[i].script_public_key, (btc_unsigned_txn_byte_array+offset), len);
        offset += len;
      }

      len = sizeof(unsigned_txn_ptr->locktime);
      memcpy(unsigned_txn_ptr->locktime, (btc_unsigned_txn_byte_array+offset), len);
      offset += len;

      len = sizeof(unsigned_txn_ptr->sighash);
      memcpy(unsigned_txn_ptr->sighash, (btc_unsigned_txn_byte_array+offset), len);
      offset += len;

}

void serialize_unsigned_txn_to_sign(unsigned_txn *unsigned_txn_ptr, uint8_t input_index, uint8_t *btc_serialized_unsigned_txn)
{
	  uint32_t offset = 0, len = 0;
	  uint8_t i;
      unsigned_txn_input temp;
      
	  len = sizeof(temp.script_public_key);
      memcpy(temp.script_public_key,0,len);
 	
      len = sizeof(unsigned_txn_ptr->network_version);
      memcpy((btc_serialized_unsigned_txn+offset),unsigned_txn_ptr->network_version,  len);
      offset += len;

      len = sizeof(unsigned_txn_ptr->input_count);
      memcpy( (btc_serialized_unsigned_txn+offset),unsigned_txn_ptr->input_count, len);
      offset += len;

      len = (*unsigned_txn_ptr->input_count)*sizeof(unsigned_txn_input); 
      unsigned_txn_ptr->input = (unsigned_txn_input*)malloc(len);
    
      for ( i = 0; i < *unsigned_txn_ptr->input_count ; i++)
      {
      	if(i==input_index)
      	{
      		len = sizeof(unsigned_txn_ptr->input[i].previous_txn_hash);
        	memcpy((btc_serialized_unsigned_txn+offset),unsigned_txn_ptr->input[i].previous_txn_hash, len);
        	offset += len;

        	len = sizeof(unsigned_txn_ptr->input[i].previous_output_index);
        	memcpy( (btc_serialized_unsigned_txn+offset),unsigned_txn_ptr->input[i].previous_output_index, len);
        	offset += len;

        	len = sizeof(unsigned_txn_ptr->input[i].script_length);
        	memcpy( (btc_serialized_unsigned_txn+offset),unsigned_txn_ptr->input[i].script_length,len);
        	offset += len;

        	len = sizeof(unsigned_txn_ptr->input[i].script_public_key);
        	memcpy( (btc_serialized_unsigned_txn+offset),unsigned_txn_ptr->input[i].script_public_key, len);
        	offset += len;
		
        	len = sizeof(unsigned_txn_ptr->input[i].sequence);
        	memcpy( (btc_serialized_unsigned_txn+offset),unsigned_txn_ptr->input[i].sequence, len);
        	offset += len;
      		continue;
		}
        len = sizeof(unsigned_txn_ptr->input[i].previous_txn_hash);
        memcpy((btc_serialized_unsigned_txn+offset),unsigned_txn_ptr->input[i].previous_txn_hash, len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->input[i].previous_output_index);
        memcpy( (btc_serialized_unsigned_txn+offset),unsigned_txn_ptr->input[i].previous_output_index, len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->input[i].script_length);
        memcpy( (btc_serialized_unsigned_txn+offset),0,len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->input[i].sequence);
        memcpy( (btc_serialized_unsigned_txn+offset),unsigned_txn_ptr->input[i].sequence, len);
        offset += len;
      }
      
      len = sizeof(unsigned_txn_ptr->output_count);
      memcpy( (btc_serialized_unsigned_txn+offset),unsigned_txn_ptr->output_count, len);
      offset += len;

      len = (*unsigned_txn_ptr->output_count)*sizeof(txn_output); 
      unsigned_txn_ptr->output = (txn_output*)malloc(len);

      for (i = 0; i < *unsigned_txn_ptr->output_count; i++)
      {
        len = sizeof(unsigned_txn_ptr->output[i].value);
        memcpy( (btc_serialized_unsigned_txn+offset),unsigned_txn_ptr->output[i].value, len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->output[i].script_length);
        memcpy((btc_serialized_unsigned_txn+offset), unsigned_txn_ptr->output[i].script_length, len);
        offset += len;

        len = sizeof(unsigned_txn_ptr->output[i].script_public_key);
        memcpy( (btc_serialized_unsigned_txn+offset), unsigned_txn_ptr->output[i].script_public_key,len);
        offset += len;
      }

      len = sizeof(unsigned_txn_ptr->locktime);
      memcpy( (btc_serialized_unsigned_txn+offset), unsigned_txn_ptr->locktime, len);
      offset += len;

      len = sizeof(unsigned_txn_ptr->sighash);
      memcpy( (btc_serialized_unsigned_txn+offset), unsigned_txn_ptr->sighash, len);
}

void byte_array_to_txn_metadata(uint8_t *btc_txn_metadata_byte_array, txn_metadata *txn_metadata_ptr){
	uint32_t offset = 0, len = 0;
	
	txn_metadata_ptr->wallet_index[0] = btc_txn_metadata_byte_array[offset++];
	
	len=4;
	memcpy(txn_metadata_ptr->purpose_index, (btc_txn_metadata_byte_array+offset), len);
	offset+=len;
	
	memcpy(txn_metadata_ptr->purpose_index, (btc_txn_metadata_byte_array+offset), len);
	offset+=len;
	
	memcpy(txn_metadata_ptr->purpose_index, (btc_txn_metadata_byte_array+offset), len);
	offset+=len;
	
	txn_metadata_ptr->input_count[0] = btc_txn_metadata_byte_array[offset++];

	len = (*txn_metadata_ptr->input_count)*sizeof(address_type); 
    txn_metadata_ptr->input = (address_type*)malloc(len);
    len =4;
    for (uint8_t i = 0; i < *txn_metadata_ptr->input_count; i++)
    {
    	memcpy(txn_metadata_ptr->input[i].chain_index, (btc_txn_metadata_byte_array+offset), len);
		offset+=len;
		memcpy(txn_metadata_ptr->input[i].address_index, (btc_txn_metadata_byte_array+offset), len);
		offset+=len;
	}
	
	txn_metadata_ptr->output_count[0] = btc_txn_metadata_byte_array[offset++];
	
	len = (*txn_metadata_ptr->output_count)*sizeof(address_type); 
    txn_metadata_ptr->output = (address_type*)malloc(len);
    len =4;
    for (uint8_t i = 0; i < *txn_metadata_ptr->output_count; i++)
    {
    	memcpy(txn_metadata_ptr->output[i].chain_index, (btc_txn_metadata_byte_array+offset), len);
		offset+=len;
		memcpy(txn_metadata_ptr->output[i].address_index, (btc_txn_metadata_byte_array+offset), len);
		offset+=len;
	}
	
	txn_metadata_ptr->change_count[0] = btc_txn_metadata_byte_array[offset++];
	
	len = (*txn_metadata_ptr->change_count)*sizeof(address_type); 
    txn_metadata_ptr->change = (address_type*)malloc(len);
    len =4;
    for (uint8_t i = 0; i < *txn_metadata_ptr->change_count; i++)
    {
    	memcpy(txn_metadata_ptr->change[i].chain_index, (btc_txn_metadata_byte_array+offset), len);
		offset+=len;
		memcpy(txn_metadata_ptr->change[i].address_index, (btc_txn_metadata_byte_array+offset), len);
		offset+=len;
	}
	
	
}

uint32_t unsigned_txn_to_signed_txn(unsigned_txn *unsigned_txn_ptr, txn_metadata *txn_metadata_ptr, const char *mnemonic, const char *passphrase, signed_txn *signed_txn_ptr){
	int len ;
	len = (*unsigned_txn_ptr->output_count)*sizeof(txn_output); 
    signed_txn_ptr->output = (txn_output*)malloc(len);
    
    len = (*unsigned_txn_ptr->input_count)*sizeof(signed_txn_input); 
    signed_txn_ptr->input = (signed_txn_input*)malloc(len);
    
}



