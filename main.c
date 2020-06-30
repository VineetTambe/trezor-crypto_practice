#include<stdio.h>
#include<stdint.h>
#include "bip39.h"
int main()
{
    char* mnemonic = "smoke tiny walnut keep pact wet jar glance turkey erase unique fancy wedding usage unaware avoid left patient amazing stuff wing absent guilt ceiling";
    //char* mnemonic = "smkoe smkoe smkoe smoke smoke smkoe smkoe smoke smoke smoke smoke smoke smoke smoke smoke smoke smoke smoke smoke smoke smoke smoke smoke smoke";
    printf("mnemonic = %s\n",mnemonic);
    uint8_t en;
    int entropy = mnemonic_to_entropy(mnemonic,&en);
    printf("%d\n",entropy);
    return 0;
}