#include <iostream>
#include <fstream>
#include <cstdint>

int main()
{
    // Dosya adý
    std::string filename = "ornek.dosya";

    // Dosyayý aç
    std::ifstream file(filename, std::ios::binary);

    // Dosyanýn açýlmadýðýný kontrol et
    if (!file)
    {
        std::cerr << "Dosya acilamadi" << std::endl;
        return 1;
    }

    // Dosya boyutunu al
    file.seekg(0, std::ios::end);
    std::streampos filesize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Dosyanýn tamamýný okumak için bellek tahsis et
    char* buffer = new char[filesize];

    // Dosyayý belleðe oku
    file.read(buffer, filesize);

    // Dosya okuma hatasý kontrolü
    if (!file)
    {
        std::cerr << "Dosya okunamadi" << std::endl;
        return 1;
    }

    // Bellekteki verileri 64 bitlik parçalara bölmek için
    // char dizisini uint64_t türünden bir diziye dönüþtür
    uint64_t* data = reinterpret_cast<uint64_t*>(buffer);

    // Verileri 64 bitlik parçalara bölmek için
    // bellekteki her 8 byte'lýk bloðu yazdýr
    for (int i = 0; i < filesize / 8; i++)
    {
        std::cout << "Parca " << i + 1 << ": " << data[i] << std::endl;
    }

    // Bellek tahsisini serbest býrak
    delete[] buffer;

    return 0;
}