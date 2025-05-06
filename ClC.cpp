#include "erlog.h"
#include <ClC.h>
#include <string>

int iListDirn(std::string& , std::multimap<std::string, uint64_t>&);


int ClC::iReadAptList(std::string astrJobFile, std::multimap<std::string, std::string>& mmStrStr){ 

    dmess3(1, "Parse %s...", astrJobFile.c_str());

    std::ifstream file(astrJobFile);
      if(!file.is_open()){
        dmess3(1, "error open file - %s", astrJobFile.c_str());
        return EXIT_FAILURE;
      } 

    std::string strBuff, strNamePkg, strVersionPkg;
    while(!std::getline(file, strBuff).eof()){// chitaem fail postrochno poka ne vstretim eof

    // +++ Parsim stroku "apt list" izvlekaem ima i versiy paketa 
    //0ad-data-common/stable,stable 0.0.26-1 all
      size_t it1 = 0;
      size_t it2 = 0;

      if(strBuff == "Listing...")
        continue;

      {
        //dmess3(1, strBuff);
        for(; it2<strBuff.size(); ++it2){ // poluchaem ima paketa
          if(strBuff[it2] == '/'){
            strNamePkg = strBuff.substr(it1 , it2-it1);
            it1 = it2;
            //dmess3(0, "PkgName =%s|||", strNamePkg.c_str());
            break;
          }
        }

        for(; it2<strBuff.size(); ++it2) //propuskaem vse do probela
          if(strBuff[it2] == ' '){
            it1 = ++it2;
            break;
          }

        for(; it2<strBuff.size(); ++it2){ // poluchaem versiy paketa
          if(strBuff[it2] == ' '){
            strVersionPkg = strBuff.substr(it1 , it2-it1);
            //dmess3(1, "PkgVersion =%s|%d|%d|", strVersionPkg.c_str(), it1, it2);
            break;
          }
        }

        mmStrStr.insert( std::pair<std::string, std::string>
            (strNamePkg, strVersionPkg));
      }
    // --- Parsim stroku "apt list" izvlekaem ima i versiy paketa 
    }

    /*for (const std::pair<const std::string, std::string>& item : mmStrStr)
            dmess3(1, " Package =%s,\tVersion =%s|", item.first.c_str(), item.second.c_str());*/

    if(file.is_open())
        file.close();

    return EXIT_SUCCESS;
};

int ClC::iReadDpkgList(std::string astrJobFile, std::multimap<std::string, std::string>& mmStrStr){ 

    std::ifstream file(astrJobFile);
      if(!file.is_open()){
        dmess3(1, "error open file - %s", astrJobFile.c_str());
        return EXIT_FAILURE;
      } 

    std::string strBuff, strNamePkg, strVersionPkg;
    while(!std::getline(file, strBuff).eof()){// chitaem fail postrochno poka ne vstretim eof

    // +++ Parsim stroku "dpkg -l" izvlekaem ima i versiy paketa 
      //ii  accountsservice                                  22.08.8-6                                 amd64        query and manipulate user account information
      size_t it1 = 4;
      size_t it2 = 4;
      if(strBuff.substr(0, it1) == "ii  ")
      {
        //dmess3(1, strBuff);
        // poluchaem ima paketa
        for(; it2<strBuff.size(); ++it2){
          if(strBuff[it2] == ' '){
            strNamePkg = strBuff.substr(it1 , it2-it1);
            it1 = it2;
            //dmess3(0, "PkgName =%s|||", strNamePkg.c_str());
            break;
          }
        }

        //propuskaem probeli
        for(; it2<strBuff.size(); ++it2)
          if(strBuff[it2] != ' '){
            it1 = it2;
            break;
          }

        // poluchaem versiy paketa
        for(; it2<strBuff.size(); ++it2){
          if(strBuff[it2] == ' '){
            strVersionPkg = strBuff.substr(it1 , it2-it1);
            //dmess3(1, "PkgVersion =%s|%d|%d|", strVersionPkg.c_str(), it1, it2);
            break;
          }
        }

        mmStrStr.insert( std::pair<std::string, std::string>
            (strNamePkg, strVersionPkg));
    // --- Parsim stroku "dpkg -l" izvlekaem ima i versiy paketa 
      }
    }

    /*for (const std::pair<const std::string, std::string>& item : mmStrStr)
            dmess3(1, " Package =%s,\tVersion =%s|", item.first.c_str(), item.second.c_str());*/

    if(file.is_open())
        file.close();

    return EXIT_SUCCESS;
};


void vTreadSravnenieList(std::multimap<std::string, uint64_t>& msCache,  std::multimap<std::string, std::string>& mmStrStr){
      dmess3(1, "Sravnenie spiscov");
      std::string strBuff;
      for(auto itAte = msCache.begin(); itAte != msCache.end(); ++itAte)
        for (auto itAssz = mmStrStr.begin(); itAssz != mmStrStr.end(); ++itAssz ){
          //dmess3(1, " Package =%s,\tVersion =%s|", item.first.c_str(), item.second.c_str());
          strBuff = (*itAssz).first; // sobiraem ima paketa + versiya paketa
          strBuff += "_"; // sobiraem ima paketa + versiya paketa
          strBuff += (*itAssz).second; // sobiraem ima paketa + versiya paketa

          //dmess3(1, "Cache =%s, list=%s", itAte->first.c_str(), strBuff.c_str());
          if(strBuff.npos != (*itAte).first.rfind((*itAssz).first)) // proveraem po imeni paketa
            if(strBuff.npos != (*itAte).first.rfind((*itAssz).second)){ // proveraem po versii paketa
              msCache.erase(itAte);
              itAte = msCache.begin();
              itAssz = mmStrStr.begin();
              if(itAte  == msCache.end()) break;
              continue;
            }
        }

}

void ClC::ClearCacheDebian(std::string strObrazec, std::string strCache){

  namespace fs = std::filesystem;

  if(fs::exists(strCache))
    if(fs::exists(strObrazec)){
      // poluchaem spisiki failov v directoriyah
      std::multimap<std::string, uint64_t> msCache;
      std::multimap<std::string, std::string> mmStrStr;
      iReadAptList(strObrazec, mmStrStr);
      iListDirn(strCache, msCache);

      /*for (const std::pair<const std::string, std::string>& item : mmStrStr)
        dmess3(1, " Package =%s,\tVersion =%s|", item.first.c_str(), item.second.c_str());*/

      // +++ perebor failov-spiskov

      dmess3(1, "Sravnenie spiscov");
      
      vTreadSravnenieList(msCache, mmStrStr);

      /*std::string strBuff;
      for(auto itAte = msCache.begin(); itAte != msCache.end(); ++itAte)
        for (auto itAssz = mmStrStr.begin(); itAssz != mmStrStr.end(); ++itAssz ){
          //dmess3(1, " Package =%s,\tVersion =%s|", item.first.c_str(), item.second.c_str());
          strBuff = (*itAssz).first; // sobiraem ima paketa + versiya paketa
          strBuff += "_"; // sobiraem ima paketa + versiya paketa
          strBuff += (*itAssz).second; // sobiraem ima paketa + versiya paketa

          //dmess3(1, "Cache =%s, list=%s", itAte->first.c_str(), strBuff.c_str());
          if(strBuff.npos != (*itAte).first.rfind((*itAssz).first)) // proveraem po imeni paketa
            if(strBuff.npos != (*itAte).first.rfind((*itAssz).second)){ // proveraem po versii paketa
              msCache.erase(itAte);
              itAte = msCache.begin();
              itAssz = mmStrStr.begin();
              if(itAte  == msCache.end()) break;
              continue;
            }
        }*/
      // --- perebor failov-spiskov

      this->Delete_files(msCache);
    }
};

void ClC::Delete_files(std::multimap<std::string, uint64_t>& msCache){ // Zdes udalaem nesovpavshie faili
  if(msCache.size()){
    unsigned int uisize  = 0;
    unsigned int uicount = 0;
    for (const std::pair<const std::string, uint64_t>& item : msCache){
      dmess3(1,"Budut udalen: File - %s, size file = %d", item.first.c_str(), item.second);
      uisize += item.second;
      ++uicount;
    }

    std::string strOtvet;
    std::cout<<"Budet udaleno - "<< uicount<<" falov obshim razmerom - "<< uisize<<" bait"<<std::endl;
    std::cout<<"Delete file`s ? Eneter Yes"<<std::endl;
    std::cin>>strOtvet;
    if(strOtvet == "Yes"){
      for (const std::pair<const std::string, uint64_t>& item : msCache) {
        dmess3(1,"Delete file - %s, size file = %d", item.first.c_str(), item.second);
        std::filesystem::remove(item.first);
      }
    }
  }
};

void ClC::SravnenieSpiscov(std::multimap<std::string, uint64_t> msObrazec, std::multimap<std::string, uint64_t> msCache){ // Zdes proizvodim sravnenie directorii
    for (const std::pair<const std::string, uint64_t>& item : msObrazec) {
        //dmess3(1,"File - %s, size file = %d", item.first.c_str(), item.second);

        for (auto itAte = msCache.begin(); itAte!=msCache.end(); ++itAte) {
            //dmess3(1,"Cache  File - %s, size file = %d", (*itAte).first.c_str(), (*itAte).second);

            if(item.second == (*itAte).second){// esli razmeri failov sovpodaut to proveraem imena
                static std::string strBuff;
                static std::size_t sz;

                sz = (*itAte).first.rfind('/'); // tak kak puti failov mogut ne sovpat, to v strBuff kopiruem tolko ima faila
                if((*itAte).first.npos != sz){
                    strBuff = (*itAte).first.substr(sz+1);
                };
                        //dmess3(1,"File - %s, size file = %d", strBuff.c_str(), (*itAte).second);
                    if(strBuff.npos != item.first.rfind(strBuff)) // esli imena failov sovpali to udalem punkt faila(itAte) iz msCache
                    {
                            /*dmess3(1,"Obrazec Erase item File - %s, size file = %d", (*itAte).first.c_str(), (*itAte).second);
                            dmess3(1,"Cache Erase item  File - %s, size file = %d", strBuff.c_str(), (*itAte).second);*/
                        msCache.erase(itAte);
                        itAte = msCache.begin();
                            //if(!msCache.size())  break; // kostil TODO pri opredelenih usloviyah moget bit itAte>itEnd 
                            if(itAte == msCache.end())  break; // kostil TODO pri opredelenih usloviyah moget bit itAte>itEnd 
                            //if(msCache.begin() == msCache.end()) break; // kostil TODO pri opredelenih usloviyah moget bit itAte>itEnd 
                        continue;
                    }

            }
        }


    }
    this->Delete_files(msCache);
};

void ClC::ClearCacheFromObrazDirOrImageFile(std::string strObrazec, std::string strCache){

  namespace fs = std::filesystem;

  if(fs::exists(strCache))
    if(fs::exists(strObrazec)){
      // poluchaem spisiki failov v directoriyah
      std::multimap<std::string, uint64_t> msObrazec, msCache;

      if(fs::is_regular_file(strObrazec))
        iReadImageFile(strObrazec, msObrazec);
      else if(fs::is_directory(strObrazec))
        iListDirn(strObrazec, msObrazec);;

        iListDirn(strCache, msCache);

      this->SravnenieSpiscov(msObrazec, msCache);
    }
};

int ClC::iReadImageFile(std::string astrJobFile, std::multimap<std::string, uint64_t>& mmStrSize){ // Chitaem sodergimoe directorii obrazca iz faila formata ImageDir
    std::ifstream file(astrJobFile);

    if(!file.is_open()){
        dmess3(1, "error open file - %s", astrJobFile.c_str());
        return EXIT_FAILURE;
    } 

    // +++
    std::string strBuff;
    while(!std::getline(file, strBuff).eof()){// chitaem fail postrochno poka ne vstretim eof
        std::string::size_type strsz;
        strsz = strBuff.rfind("  ");
        if(strBuff.npos != strsz){
            uint64_t uiSize;

                try{
            uiSize = std::stoull(strBuff.substr(strsz+2));
                }
                catch(std::invalid_argument const& ex)
                {
                    dmess3(2, "std::invalid_argument::what(): %s",  ex.what());
                }
                catch(std::out_of_range const& ex)
                {
                    dmess3(2, "std::out_of_range::what(): %s, string to unsigned long long - %s", ex.what(), strBuff.c_str());
                }

             mmStrSize.insert( std::pair<std::string, uint64_t>
                     (strBuff.substr(0, strsz), uiSize));

        }

    }
        /*for (const std::pair<const std::string, uint64_t>& item : mmStrSize)
                dmess3(1, " File = %s,\tSize = %d", item.first.c_str(), static_cast<int>(item.second));*/
    // ---

    if(file.is_open())
        file.close();

    return EXIT_SUCCESS;
};

int iListDirn(std::string& astrPath, std::multimap<std::string, uint64_t>& a_map_strSZ){
         namespace fs = std::filesystem;
    //pEl->WriteMessage3(1, astrPath);
    std::vector<std::string> avs_dirs;
        int ierrorfun = 0;
        uint64_t SizeFile;

        /*namespace fs = std::filesystem;*/
        fs::path p {astrPath};
        std::string myPathParent = p.parent_path().string();

        try{
                for (const auto& dirEntry : fs::recursive_directory_iterator(astrPath))
                {
                    if(fs::is_directory(dirEntry))
                         avs_dirs.push_back(dirEntry.path().string());
                    else{
                         avs_dirs.push_back(dirEntry.path().string());
                         SizeFile =  fs::file_size(dirEntry.path());
                         a_map_strSZ.insert( std::pair<std::string, uint64_t>
                                 ( dirEntry.path().string(), SizeFile) );
                    }
                }
        }
        catch(fs::filesystem_error &ex)
        {
          dmess3( 2, "%s",  ex.what() );
              FSerrorMessages(ex);
        }

    return ierrorfun;
};

