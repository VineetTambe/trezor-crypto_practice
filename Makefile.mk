m2e: main.o bip39.o memzero.o sha2.o hmac.o pbkdf2.o rand.o
	gcc main.o bip39.o memzero.o sha2.o hmac.o pbkdf2.o rand.o -o m2e -lm

main.o: main.c bip39.h
	gcc -c main.c

bip39.o: bip39.c bip39_english.h options.h
	gcc -c bip39.c

memzero.o: memzero.c
	gcc -c memzero.c

sha2.o: sha2.c
	gcc -c sha2.c

hmac.o: hmac.c
	gcc -c hmac.c

pbkdf2.o: pbkdf2.c
	gcc -c pbkdf2.c

rand.o: rand.c
	gcc -c rand.c

clean:
	rm -f *.o m2e
