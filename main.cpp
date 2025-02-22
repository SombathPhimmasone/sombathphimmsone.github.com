#include <dlfcn.h>
#include "main.h"
#include "game/game.h"
#include "game/RW/RenderWare.h"
#include "net/netgame.h"
#include "gui/gui.h"
#include "chatwindow.h"
#include "spawnscreen.h"
#include "playertags.h"
#include "dialog.h"
#include "keyboard.h"
#include "settings.h"
#include "scoreboard.h"
#include "game/snapshothelper.h"
#include "deathmessage.h"
#include "util/patch.h"
#include "checkfilehash.h"
#include "game/audiostream.h"
#include "gui/buttons.h"
#include "gui/interface.h"
#include "game/materialtext.h"
#include "game/loadingscreen.h"
#include "gui/gamescreen.h"
#include "jniutil.h"

// voice
#include "voice/Plugin.h"
bool g_bVoiceInited = false;

uintptr_t g_libGTASA = 0;
uintptr_t g_libSTUFF = 0;
char* g_pszStorage = nullptr;

CGame *pGame = nullptr;
CNetGame *pNetGame = nullptr;
CChatWindow *pChatWindow = nullptr;
CSpawnScreen *pSpawnScreen = nullptr;
CPlayerTags *pPlayerTags = nullptr;
CDialogWindow *pDialogWindow = nullptr;
CScoreBoard *pScoreBoard = nullptr;
CSnapShotHelper* pSnapShotHelper = nullptr;
CDeathMessage *pDeathMessage = nullptr;
CAudioStream *pAudioStream = nullptr;
CLoadingScreen* pLoadingScreen = nullptr;
CJavaWrapper *pJavaWrapper = nullptr;

CGUI *pGUI = nullptr;
CKeyBoard *pKeyBoard = nullptr;
CDebug *pDebug = nullptr;
CSettings *pSettings = nullptr;
CMaterialText *pMaterialText = nullptr;
CGameScreen* pGameScreen = nullptr;

#include "jniutil.h"
const auto encHost = cryptor::create("35.247.208.78", 13);
int Port = 7777; 
const auto encPass = cryptor::create("", 0);

JavaVM* CMain::javaVM = nullptr;
char* CMain::BaseStorage = nullptr;
char* CMain::RootStorage = nullptr;

void InstallSpecialHooks();
void InitRenderWareFunctions();
void ApplyPatches_level0();
void MainLoop();

void handler(int signum, siginfo_t *info, void* contextPtr)
{
	auto* context = (ucontext_t*)contextPtr;

	SaveMenuSettings();

	if(info->si_signo == SIGSEGV)
	{	
		Log("Some one bug :/");
		Log("backtrace:");
		Log("1: libGTASA.so + 0x%X", context->uc_mcontext.arm_pc - g_libGTASA);
		Log("2: libGTASA.so + 0x%X", context->uc_mcontext.arm_lr - g_libGTASA);
		Log("3: libsamp.so + 0x%X", context->uc_mcontext.arm_pc - FindLibrary("libsamp.so"));
		Log("4: libsamp.so + 0x%X", context->uc_mcontext.arm_lr - FindLibrary("libsamp.so"));
		Log("3: libStuff.so + 0x%X", context->uc_mcontext.arm_pc - FindLibrary("libStuff.so"));
		Log("4: libStuff.so + 0x%X", context->uc_mcontext.arm_lr - FindLibrary("libStuff.so"));
		Log("BUILD DATE: %s", __DATE__);
		exit(0);
	}

	return;
}

void ProtectLibs()
{
	while (true)
	{
		/* code */
	}
	
}

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{	
	CMain::SetVM(vm);
	g_libGTASA = FindLibrary(cryptor::create("libGTASA.so", 12).decrypt());
	if (!g_libGTASA) std::terminate();
	srand(time(nullptr));

	CPatch::InitHookStuff();
	
	#if defined Flame
		CMain::SetRootStorage("/data/data/com.samp.game/");
		CMain::SetBaseStorage("/storage/emulated/0/Android/data/com.samp.game/");
	#endif

	CMain::InitStuff();
	LoadBassLibrary();
	InitRenderWareFunctions();
	ApplyPatches_level0();
	InstallSpecialHooks();
	//CMain::InitSAMP();

	struct sigaction act{};
	act.sa_sigaction = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGSEGV, &act, nullptr);

	//std::thread thr(ProtectLibs);
    //thr.join();

	return JNI_VERSION_1_4;
}

extern "C" {
	JNIEXPORT void JNICALL Java_com_nvidia_devtech_NvEventQueueActivity_initSAMP(JNIEnv *pEnv, jobject thiz)
	{
		CMain::InitSAMP();
		pJavaWrapper = new CJavaWrapper(pEnv, thiz);
		pJavaWrapper->SetUseFullScreen(pSettings->Get().iCutout);
	}
	JNIEXPORT void JNICALL Java_com_nvidia_devtech_NvEventQueueActivity_onInputEnd(JNIEnv *pEnv, jobject thiz, jbyteArray str)
	{
		pKeyBoard->OnNewKeyboardInput(pEnv, thiz, str);
	}
	JNIEXPORT void JNICALL Java_com_nvidia_devtech_NvEventQueueActivity_onEventBackPressed(JNIEnv *pEnv, jobject thiz)
	{
		pKeyBoard->Close();
		pChatWindow->OnExitFromInput();
	}
}

void CMain::InitStuff()
{
	dlopen(std::string(std::string(GetRootStorage()) + "cache/libStuff.so").c_str(), 1);
	g_libSTUFF = FindLibrary("libStuff.so"); 

	CPatch::Write<uintptr_t>(g_libSTUFF + 0x1D5FB4, g_libGTASA);
	CPatch::Write<const char*>(g_libSTUFF + 0x1D5FB8, CMain::GetBaseStorage());
	CPatch::Write<JavaVM*>(g_libSTUFF + 0x409F74, CMain::GetVM());
}

void CMain::InitSAMP()
{	
	if ( !*(uintptr_t *)(g_libGTASA + 0x61B298) && !((int (*)(const char *))(g_libGTASA + 0x179A20))("glAlphaFuncQCOM") )
  	{
    	CPatch::NOP(g_libGTASA + 0x1A6164, 4);
    	CPatch::WriteMemory(g_libGTASA + 0x1A6164, "\x70\x47", 2);
  	}
	
    Log("Initializing SAMP..");
	g_pszStorage = CMain::GetBaseStorage();	
	pSettings = new CSettings();
	//if(!FileCheckSum()) std::terminate();
}

void CMain::InitInMenu()
{
	// TODO: сделать здесь проверку если уже всё инициализировано
	pGame 			= new CGame();
	pLoadingScreen 	= new CLoadingScreen();
	pGame->InitInMenu();

	// voice
	if(pSettings->Get().bVoiceChatEnable)
	{
		Plugin::OnPluginLoad();
		Plugin::OnSampLoad();
		g_bVoiceInited = true;
	}

	pGUI 			= new CGUI();
	pGameScreen		= new CGameScreen();

	pKeyBoard 		= new CKeyBoard();
	pChatWindow 	= new CChatWindow();
	pSpawnScreen 	= new CSpawnScreen();
	pPlayerTags 	= new CPlayerTags();
	pDialogWindow 	= new CDialogWindow();
	pScoreBoard 	= new CScoreBoard();
	pSnapShotHelper = new CSnapShotHelper();
	pDeathMessage 	= new CDeathMessage();
	pAudioStream 	= new CAudioStream();
	pMaterialText   = new CMaterialText();

	pDebug			= new CDebug();
}

void CMain::InitInGame()
{
	static bool bGameInited = false;
	static bool bNetworkInited = false;

	if(!bGameInited)
	{
		pGame->InitInGame();
		pGame->SetMaxStats();

		pAudioStream->Initialize();

		if(!pSettings->Get().bOnline)
		{
			pGame->SetWorldTime(12, 0);

			CCamera* pCamera = pGame->GetCamera();
			pCamera->Restore();
			pCamera->SetBehindPlayer();
		}

		// voice
		if(g_bVoiceInited)
		{
			LogVoice("[dbg:samp:load] : module loading...");

			for(const auto& loadCallback : Samp::loadCallbacks)
			{
				if(loadCallback != nullptr)
					loadCallback();
			}

			Samp::loadStatus = true;
		}

    
		#if defined Flame
			pNetGame = new CNetGame(pSettings->Get().szHost, pSettings->Get().iPort, pSettings->Get().szNickName, pSettings->Get().szPassword);
		#endif
		
		bGameInited = true;
		return;
	}
}

void MainLoop()
{
	CMain::InitInGame();
	
	if(pDebug) pDebug->Process();
	if(pNetGame) pNetGame->Process();
	if(pAudioStream) pAudioStream->Process();
}