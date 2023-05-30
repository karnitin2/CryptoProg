all: encryption decryption

encryption: encryption.cpp
 g++ -g -O2 -Wall -Wextra -o encryption encryption.cpp -lcryptopp

decryption: decryption.cpp
 g++ -g -O2 -Wall -Wextra -o decryption decryption.cpp -lcryptopp

clean:
 rm -f encryption decryption
