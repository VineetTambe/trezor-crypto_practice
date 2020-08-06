main: main.o ECDSA_sign_verify.o ecdsa.o bignum256.o endian.o hmac_drbg.o sha256.o hash.o
	gcc main.o ECDSA_sign_verify.o ecdsa.o bignum256.o endian.o hmac_drbg.o sha256.o hash.o -o main -lm

main.o: main.c ECDSA_sign_verify.h
	gcc -c main.c

ECDSA_sign_verify.o: ECDSA_sign_verify.c ecdsa.h
	gcc -c ECDSA_sign_verify.c

ecdsa.o: ecdsa.c common.h bignum256.h endian.h hmac_drbg.h
	gcc -c ecdsa.c

bignum256.o: bignum256.c common.h 
	gcc -c bignum256.c

endian.o: endian.c common.h
	gcc -c endian.c

hmac_drbg.o: hmac_drbg.c common.h sha256.h
	gcc -c hmac_drbg.c

sha256.o: sha256.c common.h hash.h
	gcc -c sha256.c

hash.o: hash.c common.h endian.h
	gcc -c hash.c  

clean:
	rm -f *.o main