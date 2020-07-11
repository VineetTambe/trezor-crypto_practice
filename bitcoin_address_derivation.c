        uint8_t HashD1[32];
        uint8_t HashD2[20];
        uint8_t publicKeyVersionHashD[21];
        uint8_t HashD3[32];
        uint8_t HashD4[32];
        uint8_t addr[25];
        char strn[53];
        
        char * hexstring = "031152B47A0496F0EA2CADDE1731F6B710030C48F7A791348DCDEDF559BB834CC7";
        uint8_t pubKey[33];
        hex_string_to_byte_array(hexstring,66, &pubKey[0]);
        /*
        printf("\nPublic key = ");
        for(int j=0;j<33;j++)
            printf("%02x",hdnode.public_key[j]);
        printf("\n");
        */
        //sha256_Raw(hdnode.public_key, 33, HashD1);
        sha256_Raw(pubKey, 33, HashD1);
        printf("\nHashD1 = ");
        for(int j=0;j<32;j++)
            printf("%02x",HashD1[j]);
        printf("\n");
        
        ripemd160(HashD1, 32, HashD2);

        printf("\nHashD2 = ");
        for(int j=0;j<32;j++)
            printf("%02x",HashD2[j]);
        printf("\n");
        
        publicKeyVersionHashD[0] = 0x00;
        //memcpy(&publicKeyVersionHashD+1,&HashD2,20);
        for(int j=1;j<21;j++)
            publicKeyVersionHashD[j] = HashD2[j-1];

        printf("\npublicKeyVersionHashD = ");
        for(int j=0;j<21;j++)
            printf("%02x",publicKeyVersionHashD[j]);
        printf("\n");
        
        sha256_Raw(publicKeyVersionHashD,21, HashD3);

        printf("\nHashD3 = ");
        for(int j=0;j<32;j++)
            printf("%02x",HashD3[j]);
        printf("\n");
        
        
        sha256_Raw(HashD3,32,HashD4);

        printf("\nHashD4 = ");
        for(int j=0;j<32;j++)
            printf("%02x",HashD4[j]);
        printf("\n");

        //memcpy(&addr,&publicKeyVersionHashD,21);
        for(int j=0;j<21;j++)
            addr[j]=publicKeyVersionHashD[j];
        for(int j=21;j<25;j++)
            addr[j] = HashD4[j-21];
        printf("\nhex Address: ");
        for(int j=0;j<25;j++)
            printf("%02x",addr[j]);
        printf("\n");
        int temp = base58_encode_check(addr,21,HASHER_SHA2D,strn,53);
        printf("\nbase58 Address: ");
        for(int j=0;j<temp;j++)
            printf("%c",strn[j]);
        printf("\n");

