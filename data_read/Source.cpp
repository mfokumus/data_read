#include <iostream>
#include <fstream>
#include <cstdint>

int main()
{
    // Dosya ad�
    std::string filename = "ornek.dosya";

    // Dosyay� a�
    std::ifstream file(filename, std::ios::binary);

    // Dosyan�n a��lmad���n� kontrol et
    if (!file)
    {
        std::cerr << "Dosya acilamadi" << std::endl;
        return 1;
    }

    // Dosya boyutunu al
    file.seekg(0, std::ios::end);
    std::streampos filesize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Dosyan�n tamam�n� okumak i�in bellek tahsis et
    char* buffer = new char[filesize];

    // Dosyay� belle�e oku
    file.read(buffer, filesize);

    // Dosya okuma hatas� kontrol�
    if (!file)
    {
        std::cerr << "Dosya okunamadi" << std::endl;
        return 1;
    }

    // Bellekteki verileri 64 bitlik par�alara b�lmek i�in
    // char dizisini uint64_t t�r�nden bir diziye d�n��t�r
    uint64_t* data = reinterpret_cast<uint64_t*>(buffer);

    // Verileri 64 bitlik par�alara b�lmek i�in
    // bellekteki her 8 byte'l�k blo�u yazd�r
    for (int i = 0; i < filesize / 8; i++)
    {
        std::cout << "Parca " << i + 1 << ": " << data[i] << std::endl;
    }

    // Bellek tahsisini serbest b�rak
    delete[] buffer;

    return 0;
}