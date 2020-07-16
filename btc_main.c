#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

#include "BTC_btc.h"

int main()
{
    //char* mnemonic = "smoke tiny walnut keep pact wet jar glance turkey erase unique fancy wedding usage unaware avoid left patient amazing stuff wing absent guilt ceiling";
    const char *mnemonic = "velvet embrace divorce stable street win rate tribe squeeze tunnel word video hold bright lucky popular wall napkin silly people celery grit village absurd";
	char* address ;
  	char *passphrase = "";
  	uint8_t seed[512/8];
    int i,len;

    //const char *received_unsigned_txn_string = "02000000021245fe7c5455b43e73743d83ccb5587303586a4e9a5b8f56a3eb08593624bb02000000001976a914d46d05e6ac27683aa5d63a6efc44969798acf13688acfdffffff1245fe7c5455b43e73743d83ccb5587303586a4e9a5b8f56a3eb08593624bb02010000001976a914dacc24d8b195ce046a40caedd5e2e649beee4e3388acfdffffff01f4ff0000000000001976a9142d77ece155f6b80dcab97a373834543e4b70b3e988ac84431a0001000000";    
    //const char *received_unsigned_txn_string = "0200000001748dccb662fd73e8f0d8435132b8528dd3739f55388a15795c7e7afe4f555f9f010000001976a9140ce400ffe51ab038f6134beeb14ef56c683ce00088acfdffffff02204e0000000000001976a914d46d05e6ac27683aa5d63a6efc44969798acf13688ac28b30000000000001976a914dacc24d8b195ce046a40caedd5e2e649beee4e3388ac49211a0001000000";
    const char *received_unsigned_txn_string = "02000000015c41f877ebde4f6faea75053059ef6a01cf9efc59c4b8e2eb5479e91df67ed92000000001976a9140ce400ffe51ab038f6134beeb14ef56c683ce00088acffffffff0346000000000000001976a9140ce400ffe51ab038f6134beeb14ef56c683ce00088ace8250000000000001976a91498f6358e235af6488da3ddc17977cd379badb1cb88acc7421900000000001976a9145c6f07624ccc5b02d558e5fa903235e0b46ad51d88ac0000000001000000";
	//const char *received_txn_metadata_string = "018000002c8000000180000000020000000000000001000000010000000001000000000000000200";
    //const char *received_txn_metadata_string = "018000002c80000001800000000100000000000000000200000000000000010000000100000000010000000100000000";
    const char *received_txn_metadata_string = "018000002c80000001800000000100000000000000000200000000000000010000000100000000010000000100000001";

    len=0;
	while(received_unsigned_txn_string[len]!='\0')
		len++;
	uint8_t unsigned_txn_byte_array[len/2];

	hex_string_to_byte_array(received_unsigned_txn_string,len,&unsigned_txn_byte_array[0]);// converting string to byte array

	unsigned_txn *unsigned_txn_ptr;
    unsigned_txn_ptr = (unsigned_txn*)malloc(sizeof(unsigned_txn));
	byte_array_to_unsigned_txn(unsigned_txn_byte_array, unsigned_txn_ptr);// cast into the unsigned_txn structure

	len=0;
	while(received_txn_metadata_string[len]!='\0')
		len++;
	uint8_t txn_metadata_byte_array[len/2];
	hex_string_to_byte_array(received_txn_metadata_string,len,&txn_metadata_byte_array[0]);// converting string to byte array
    /*
    printf("Metadata = ");
    for(int i=0;i<len;i++)
        printf("%c",received_txn_metadata_string[i]);
    printf("\n");
    printf("Metadata = ");
    for(int i=0;i<len/2;i++)
        printf("%02x",txn_metadata_byte_array[i]);
    printf("\n");
    */


	txn_metadata *txn_metadata_ptr;
    txn_metadata_ptr = (txn_metadata*)malloc(sizeof(txn_metadata));
	byte_array_to_txn_metadata(txn_metadata_byte_array, txn_metadata_ptr);// cast into the txn_metadata structure
	
    //displayMetadata(txn_metadata_ptr);

	signed_txn *signed_txn_ptr;

	len = sizeof(unsigned_txn_input); 
    signed_txn_ptr = (signed_txn*)malloc(len);

    len = unsigned_txn_to_signed_txn(unsigned_txn_ptr,txn_metadata_ptr,mnemonic,"",signed_txn_ptr);

    uint8_t *signed_txn_byte_array;
    signed_txn_byte_array = (uint8_t*)malloc(len);

    signed_txn_to_byte_array(signed_txn_ptr, signed_txn_byte_array);
    
    printf("\nSigned txn : \n");
    for(int i=0;i<len;i++)
    {
        printf("%02x",signed_txn_byte_array[i]);
    }
    printf("\n");

    return 0;
}
