#pragma once

#include <iostream>
#include <cstdlib>
#include <string.h>
#include <vector>
#include <map>
#include <fstream>
#include <erlog.h>
class ClC
{
    private:
    protected:
        int iReadImageFile(std::string, std::multimap<std::string, uint64_t>&); // Chitaem sodergimoe directorii obrazca iz faila formata ImageDir
        void SravnenieSpiscov(std::multimap<std::string, uint64_t>, std::multimap<std::string, uint64_t>); // Zdes proizvodim sravnenie directorii
        void Delete_files(std::multimap<std::string, uint64_t>&); // Zdes udalaem nesovpavshie faili
    public:

        ClC() = default;
        ClC(const ClC &arhs){*this = arhs;}; 
        virtual ClC& operator=(const ClC &arhs){if(&arhs == this) return *this; return *this;};
        virtual ~ClC(){};
        void ClearCacheFromObrazDirOrImageFile(std::string, std::string);

        void ClearCacheDebian(std::string, std::string );
        int iReadDpkgList(std::string , std::multimap<std::string, std::string>&); 
        int iReadAptList(std::string , std::multimap<std::string, std::string>&); 
};

