uint8_t HashD1[32];
        uint8_t HashD2[20];
        uint8_t publicKeyVersionHashD[21];
        uint8_t HashD3[32];
        uint8_t HashD4[32];
        uint8_t addr[25];
        char strn[53];
        
        sha256_Raw(hdnode.public_key, 33, HashD1);
        ripemd160(HashD1, 32, HashD2);
        switch(txn_metadata_ptr->coin_index[3])
        {
            case 0x00:
                // for bitcoin -
                publicKeyVersionHashD[0] = 0x00;
            break;
            case 0x02:
                //for LITECOIN  
                publicKeyVersionHashD[0] = 0x30;
            break;
            case 0x03:
                // for dogecoin -
                publicKeyVersionHashD[0] = 0x1E;
            break;
            case 0x05:
                // for DASH -
                publicKeyVersionHashD[0] = 0x4C;
            break;
        }
        for(int j=1;j<21;j++)
            publicKeyVersionHashD[j] = HashD2[j-1];
        sha256_Raw(publicKeyVersionHashD,21, HashD3);
        sha256_Raw(HashD3,32,HashD4);
        for(int j=0;j<21;j++)
            addr[j]=publicKeyVersionHashD[j];
        for(int j=21;j<25;j++)
            addr[j] = HashD4[j-21];
        int temp = base58_encode_check(addr,21,HASHER_SHA2D,strn,53);
