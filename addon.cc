#ifndef UNICODE
#define UNICODE
#endif
#pragma comment(lib, "netapi32.lib")
#include <stdio.h>
#include <windows.h>
#include <lm.h>
#include <locale.h>
#include <iostream>
#include <napi.h>
#include <windows.h>
#include <stdio.h>
#include <wchar.h>
#include <lm.h>
#include <clocale>
#include <string>
using namespace std;
using namespace Napi;


Napi::String CreateObject(const Napi::CallbackInfo& info) {

  setlocale(LC_ALL, "Russian");
 
  Napi::Env env = info.Env();

  Napi::String input = Napi::String::String(env, info[0].ToString());
  
  Napi::String no = Napi::String::New(env, "NO");
  Napi::String yes = Napi::String::New(env, "YES");

  DWORD dwlevel = 0;
  DWORD dwfilter = 0;
  USER_INFO_0* theEntries = new USER_INFO_0[20];
  DWORD dwprefmaxlen = 512;
  DWORD dwentriesread;
  DWORD dwtotalentries;
  NET_API_STATUS result;

  
  result = NetUserEnum(NULL, dwlevel, dwfilter, (LPBYTE*)&theEntries, dwprefmaxlen, &dwentriesread, &dwtotalentries, NULL);
  for (int i = 0; i < dwentriesread; i++)
  {
      //LPWSTR to wstring
      std::wstring userw(theEntries[i].usri0_name);

      //wstring to string
      std::string user(userw.begin(), userw.end());

      //string to Napi::String
      Napi::String User = Napi::String::New(env, user);

      //"YES"
      if (input == User) {
          return yes;
      }
  }
  NetApiBufferFree(theEntries);

  //"NO"
  return no;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  
  return Napi::Function::New(env, CreateObject, "createObject");
}

NODE_API_MODULE(server, Init)
