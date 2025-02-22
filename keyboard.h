#pragma once

#include "game/RW/RenderWare.h"

#define LAYOUT_ENG			0
#define LAYOUT_RUS			1	
#define LAYOUT_NUM			2

#define LOWER_CASE			0
#define UPPER_CASE			1

#define KEY_DEFAULT			0
#define KEY_SHIFT			1
#define KEY_BACKSPACE		2
#define KEY_SWITCH			3
#define KEY_SPACE 			4
#define KEY_SEND			5
#define KEY_NUMPAD			6
#define KEY_UP				7
#define KEY_DOWN			8
#define KEY_SPLASH			9

#define MAX_INPUT_LEN		0xBF

struct kbKey
{
	ImVec2 pos;
	ImVec2 symPos;
	float width;
	char code[2];
	char name[2][4];
	int type;
	int id;
	RwTexture* texture;
	int specifitaor;
};

typedef void keyboard_callback(const char* result);

class CKeyBoard
{
	friend class CGUI;
public:
	CKeyBoard();
	~CKeyBoard();

	void Open(keyboard_callback* handler, bool hiden = false);
	void Close();

	bool IsOpen() { return m_bEnable; }

	void OnNewKeyboardInput(JNIEnv *pEnv, jobject thiz, jbyteArray str);
	void EnableNewKeyboard();
	void EnableOldKeyboard();
	bool IsNewKeyboard();

public:
	void Render();
	bool OnTouchEvent(int type, bool multi, int x, int y);

private:
	void InitENG();
	void InitRU();
	void InitNUM();
	kbKey* GetKeyFromPos(int x, int y);

	void HandleInput(kbKey &key);
	void AddCharToInput(char sym);
	void DeleteCharFromInput();
	void Send();
	void addTextToBuffer(std::string msg);
	
	bool m_bEnable;
	bool m_bHidenInput;
	bool m_bInited;
	ImVec2 m_Size;
	ImVec2 m_Pos;
	float m_fKeySizeY;
	float m_fFontSize;

	int m_iLayout;
	int m_OldiLayout;
	int m_iCase;
	int m_iPushedKey;

	bool bKeyboard;

	std::vector<std::string> m_szLastItems;
	int m_iCurrentPosItem;

	std::vector<kbKey> m_Rows[3][5]; // eng, rus, num

	std::string m_sInput;
	char m_utf8Input[MAX_INPUT_LEN*3 + 0xF];
	int m_iInputOffset;

	keyboard_callback *m_pHandler;

    RwTexture* UPTexture = nullptr;
    RwTexture* UPTextureUse = nullptr;
	
    RwTexture* DownTexture = nullptr;
    RwTexture* DownTextureUse = nullptr;
	
    RwTexture* SplashTexture = nullptr;
    RwTexture* SplashTextureUse = nullptr;
	
	RwTexture* ButtonTexture = nullptr;
	RwTexture* ButtonTextureUse = nullptr;
	
	RwTexture* DeleteTexture = nullptr;
	RwTexture* DeleteTextureUse = nullptr;
	
	RwTexture* CapsTexture = nullptr;
	RwTexture* CapsTextureUse = nullptr;
	
	RwTexture* NumpadTexture = nullptr;
	RwTexture* NumpadTextureUse = nullptr;
	
	RwTexture* SucessTexture = nullptr;
	RwTexture* SucessTextureUse = nullptr;
	
	RwTexture* LanguageTexture = nullptr;
	RwTexture* LanguageTextureUse = nullptr;
	
	RwTexture* ButtonTexture1 = nullptr;
	RwTexture* ButtonTextureUse1 = nullptr;
	
	RwTexture* LineTexture = nullptr;
	RwTexture* BackGroundTexture = nullptr;
};