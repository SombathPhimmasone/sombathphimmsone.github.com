#pragma once

#include <jni.h>
#include <typeinfo>
#include <android/log.h>
#include <ucontext.h>
#include <pthread.h>
#include <thread>
#include <malloc.h>
#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <thread>
#include <chrono>
#include <cstdarg>
#include <iterator>
#include <set>
#include <cstdint>
#include <algorithm>
#include <random>
#include <iomanip>
#include <memory>
#include <functional>
#include <map>
#include <array>
#include <sys/mman.h>
#include <unistd.h>
#include <unordered_map>
#include <dlfcn.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define CLIENT_VER	    "1.4.0"
#define SAMP_VERSION	"0.3.7"
#define MAX_PLAYERS		1004
#define MAX_VEHICLES	2000
#define MAX_PLAYER_NAME	24

#define RAKSAMP_CLIENT
#define NETCODE_CONNCOOKIELULZ 0x6969

#include "vendor/raknet/SAMP/samp_netencr.h"
#include "vendor/raknet/SAMP/SAMPRPC.h"
#include "util/str_obfuscator.hpp"
#include "util/util.h"
#include "libbass.h"

#define Flame

#if defined Flame
	#define col_all 0x9932CC
	#define col_all1 0x99
	#define col_all2 0x32
	#define col_all3 0xCC
#endif

extern uintptr_t g_libGTASA;
extern uintptr_t g_libSTUFF;
extern char* g_pszStorage;
extern bool g_bVoiceInited;
class CMain
{
public:
    static JavaVM* javaVM;
    static char* BaseStorage;
    static char* RootStorage;

public:
    CMain(/* args */);

    static void InitStuff();
    static void InitSAMP();
    static void InitInMenu();
    static void InitInGame();

    static JavaVM* GetVM() { return javaVM; }
    static void SetVM( JavaVM* vm) { javaVM = vm; }

    static void SetBaseStorage(char* storage) { BaseStorage = storage; }
    static void SetRootStorage(char* storage) { RootStorage = storage; }
    static char* GetBaseStorage() { return BaseStorage; }
    static char* GetRootStorage() { return RootStorage; }
};
