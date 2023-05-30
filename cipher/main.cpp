#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cryptopp/cryptlib.h>
#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <cryptopp/files.h>
#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
using namespace CryptoPP;
using namespace std;
int main()
{
    int mode;
    cout << "Введите режим работы (0-зашифрование, 1-расшифрование): ";
    cin >> mode;
    string inputFilename, outputFilename, password;
    cout << "Введите имя файла с исходными данными: ";
    cin >> inputFilename;
    cout << "Введите имя файла для записи результата: ";
    cin >> outputFilename;
    cout << "Введите пароль: ";
    cin >> password;
    byte key[SHA256::DIGESTSIZE];
    SHA256().CalculateDigest(key, (byte*)password.c_str(), password.length());
    byte iv[AES::BLOCKSIZE];
    memset(iv, 0x00, AES::BLOCKSIZE);
    if (mode == 0) {
        cout << "Зашифрование файла " << inputFilename << " в файл " << outputFilename << endl;
        CBC_Mode<AES>::Encryption encryptor(key, sizeof(key), iv);
        FileSource(inputFilename.c_str(), true, new StreamTransformationFilter(encryptor, new FileSink(outputFilename.c_str())));
    } else {
        cout << "Расшифрование файла " << inputFilename << " в файл " << outputFilename << endl;
        CBC_Mode<AES>::Decryption decryptor(key, sizeof(key), iv);
        FileSource(inputFilename.c_str(), true, new StreamTransformationFilter(decryptor, new FileSink(outputFilename.c_str())));
    }
    return 0;
}
