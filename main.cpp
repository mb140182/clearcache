/* =====================================================================================
 *       Filename:  main.cpp
 *    Description:  ______________
 *        Version:  1.13a
 *        Created:  2012.06.08  /  18:01:52
 *       Revision:  2025.04.11/13:03:32
 *       Compiler:  gcc 12.2.0
 *         Author:  mb14 
 *        Company:  
 * =====================================================================================
*/
#include <filesystem>
#include <string>
#include <utility>
#ifdef __WIN32__
#include <winsock2.h>
#include <windows.h>
#endif

#include <iostream>
#include <cstdlib>
#include <string.h>
#include <vector>
#include <map>

#include <erlog.h>
#include <my_threads.h>
#include <semaphorem.h>

#include <ClC.h>

//using namespace std;

int iReadDebFile(std::string astrJobFile, std::multimap<std::string, std::string>& mmStrStr){ 

    std::ifstream file(astrJobFile);
      if(!file.is_open()){
        dmess3(1, "error open file - %s", astrJobFile.c_str());
        return EXIT_FAILURE;
      } 

    // +++
    //unsigned ui = 0;
    std::string strBuff, strNamePkg, strVersionPkg;
    while(!std::getline(file, strBuff).eof()){// chitaem fail postrochno poka ne vstretim eof
      //++ui;
      size_t it1 = 4;
      size_t it2 = 4;
      if(strBuff.substr(0, it1) == "ii  ")
      {
        //dmess3(1, strBuff);
        for(; it2<strBuff.size(); ++it2){
          if(strBuff[it2] == ' '){
            strNamePkg = strBuff.substr(it1 , it2-it1);
            it1 = it2;
                //dmess3(0, "PkgName =%s|||", strNamePkg.c_str());
            break;
          }
        }

        for(; it2<strBuff.size(); ++it2)
          if(strBuff[it2] != ' '){
            it1 = it2;
            break;
          }

        for(; it2<strBuff.size(); ++it2){
          if(strBuff[it2] == ' '){
            strVersionPkg = strBuff.substr(it1 , it2-it1);
                //dmess3(1, "PkgVersion =%s|%d|%d|", strVersionPkg.c_str(), it1, it2);
            break;
          }
        }

        mmStrStr.insert( std::pair<std::string, std::string>
            (strNamePkg, strVersionPkg));

      }
      //if(ui == 10) break;
    }
        for (const std::pair<const std::string, std::string>& item : mmStrStr)
                dmess3(1, " Package =%s,\tVersion =%s|", item.first.c_str(), item.second.c_str());
    // ---

    if(file.is_open())
        file.close();

    return EXIT_SUCCESS;
};


int main (int argc, char **argv)
{
  // 1 staraja figna, 2 error file, 3 log file, 4 pechat vremeni
  //pEl=new erlog( 0, "[error].log", "[messages].log", 1);
  erlog erg( 0, "[error].log", "[messages].log", 1);
  pEl = &erg; pEl->vClean(); pEl->vPrintConsole(2);

  if(argc < 2){
    dmess3(2, "malo parametrov");
    std::cout<<"Enter path cache -dcpath_to_cache"<<std::endl;
    std::cout<<"Enter path to obrazec directoty -dopath_to_obrazec_directory or -hopath_to_file_image_dir"<<std::endl;
    return 0;
  }
  std::string strPatternDirectoryObrazec = "-do";
  std::string strPatternDirectoryCache   = "-dc";
  std::string strPatternDPKG             = "-dp";

  std::string strCache;
  std::string strObrazec;
  std::string strDPKG_obrazec;
  std::string strBuff;

  // +++ vhodnaya gruppa ustanovka failov - spiskov
  for(auto i=0; i<argc; ++i){
    strBuff = argv[i];
    //dmess3(1, strBuff);

    if(strBuff.substr(0, 3) == strPatternDirectoryCache){
      //dmess3(1, "-dc = %s", strBuff.c_str());
      strCache = strBuff.substr(3);
    }

    if(strBuff.substr(0, 3) == strPatternDirectoryObrazec){
      //dmess3(1, "-do = %s", strBuff.c_str());
      strObrazec = strBuff.substr(3);
    }

    if(strBuff.substr(0, 3) == strPatternDPKG){
      //dmess3(1, "-dp = %s", strBuff.c_str());
      strDPKG_obrazec = strBuff.substr(3);
    }
  };
  // --- vhodnaya gruppa ustanovka failov - spiskov

  // Proveraem kaie faili bili zagrugeni, i sootvetstvenno im zapuskatem ochistku cache
  if(strCache.size()>3)
  {
    if(strObrazec.size()>3)
    {
      ClC clc;
      clc.ClearCacheFromObrazDirOrImageFile(strObrazec, strCache);
      dmess3(1, "Obrazec");
    }
    else if(strDPKG_obrazec.size() > 3){
      ClC clcd;
      clcd.ClearCacheDebian(strDPKG_obrazec, strCache);

      dmess3(1, "DPKG");
    }
    else
      dmess3(2, "No set path to file imagedir or obrazec_dir");
  }
  else
    dmess3(2, "No set path to cache");


  /*std::string strDpkgListFile = "./deb.list";
  //std::multimap<std::string, std::string> mmStrStr;
  //iReadDebFile( strDpkgListFile, mmStrStr);
  ClC clcd;
  //clcd.iReadDpkgList(strDpkgListFile, mmStrStr);
  std::string strDebCache = "/home/m/Documents/src/clearcache/sandbox/apt_cache";
  clcd.ClearCacheDebian(strDpkgListFile, strDebCache);*/


  return EXIT_SUCCESS;
}
