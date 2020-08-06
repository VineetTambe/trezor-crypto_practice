#include "ECDSA_sign_verify.h"
#include "ecdsa.h"


uint8_t hex_to_dec(uint8_t hex)
{
    uint8_t decimal = 0;
    if(hex >= '0' && hex <= '9')
        {
            decimal = hex - 48;
        }
    else if (hex >= 'a' && hex <= 'f')
        {
            decimal = hex - 97 + 10;
        }
    else if (hex >= 'A' && hex <= 'F')
        {
            decimal = hex - 65 + 10;
        }
    return decimal;
}

void hex_string_to_byte_array(const char *hex_string, uint32_t string_length, uint8_t *byte_array)
{
    uint32_t i = 0, j = 0;
    
    for(i = 0, j = 0; j < string_length/2; i+=2, j++)
    {
        byte_array[j] = (hex_to_dec(hex_string[i])*16) + (hex_to_dec(hex_string[i+1]));

    }
}

void gen_pub_sig(){
    uint8_t r[32];
    uint8_t s[32];
    uint8_t hash[32];
    uint8_t privatekey[32];
    char *privKey = "8000238ac88eef15f5dae0c5ec08525f26ebe36a23fb81255a1595098b559c02";
    char *msg_str = "10202120131020212013102021201310202120131020212013102021201310202120131020";


    hex_string_to_byte_array(privKey,64,privatekey);
    printf("\nPrivate Key : ");
    for(int i=0;i<32;i++)
    {
        printf("%02x",privatekey[i]);
    }
    printf("\n");

    
    hex_string_to_byte_array(msg_str,64,&hash[0]);
    printf("\nHash : ");
    for(int i=0;i<32;i++)
    {
        printf("%02x",hash[i]);
    }
    printf("\n");

    ecdsaSign(r, s, hash, privatekey);
    printf("\nSignature : ");
    for(int i=0;i<32;i++)
    {
        printf("%02x",r[i]);
    }
    for(int i=0;i<32;i++)
    {
        printf("%02x",s[i]);
    }
    printf("\n");

    //int res = crappyVerifySignature(r,s,hash,);
}
