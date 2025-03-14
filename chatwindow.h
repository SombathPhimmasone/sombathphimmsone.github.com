#pragma once

#define MAX_MESSAGE_LENGTH	144
#define MAX_LINE_LENGTH		MAX_MESSAGE_LENGTH / 2

enum eChatMessageType
{
    CHAT_TYPE_NONE = 0,
    CHAT_TYPE_CHAT,
    CHAT_TYPE_INFO,
    CHAT_TYPE_DEBUG
};

typedef struct
{
    eChatMessageType	eType;
    char 				utf8Message[MAX_MESSAGE_LENGTH * 3 + 1];
    char 				time[12];
    char 				szNick[MAX_PLAYER_NAME + 1];
    uint32_t			dwTextColor;
    uint32_t 			dwNickColor;
} CHAT_WINDOW_ENTRY;

class CChatWindow
{
    friend class CGUI;
public:
    CChatWindow();
    ~CChatWindow();

    void OnExitFromInput();
    bool CheckScrollBar(int x, int y);

    void AddChatMessage(char* szNick, uint32_t dwNickColor, char* szMessage);
    void AddInfoMessage(const char* szFormat, ...);
    void AddDebugMessage(char* szFormat, ...);
    void AddClientMessage(uint32_t dwColor, char* szStr);

public:
    void Render();
    bool OnTouchEvent(int type, bool multi, int x, int y);

public:
    void RenderText(const char* u8Str, float posX, float posY, uint32_t dwColor, int FirstMessage);
    void ToggleState();
private:
    void FilterInvalidChars(char* szString);
    void AddToChatWindowBuffer(eChatMessageType eType, char* szString, char* szNick,
                               uint32_t dwTextColor, uint32_t dwNickColor);
    void PushBack(CHAT_WINDOW_ENTRY& entry);

    void ResetHiding();

private:

    bool m_bIsOpened;
    bool m_bIsShow;
    bool bSwipeScroll;
	bool m_FirstLine;
	bool m_NeedOpen;
	bool b_NeedYScale;

    float m_fChatPosX, m_fChatPosY;
    float m_fChatSizeX, m_fChatSizeY;

    int m_iMaxMessages;
    int m_iOffsetY;
    int m_iLastPosY;

    //std::vector
    std::list<CHAT_WINDOW_ENTRY> m_ChatWindowEntries;

    uint32_t m_dwTextColor;
    uint32_t m_dwInfoColor;
    uint32_t m_dwDebugColor;
};



//#pragma once
//
//#include "gui/gui.h"
//
//#define MAX_MESSAGE_LENGTH	144
//#define MAX_LINE_LENGTH		MAX_MESSAGE_LENGTH / 2
//
//enum eChatMessageType
//{
//    CHAT_TYPE_NONE = 0,
//    CHAT_TYPE_CHAT,
//    CHAT_TYPE_INFO,
//    CHAT_TYPE_DEBUG
//};
//
//typedef struct
//{
//    eChatMessageType	eType;
//    char 				utf8Message[MAX_MESSAGE_LENGTH * 3 + 1];
//    char 				szNick[MAX_PLAYER_NAME + 1];
//    uint32_t			dwTextColor;
//    uint32_t 			dwNickColor;
//} CHAT_WINDOW_ENTRY;
//
//class CChatWindow
//{
//    friend class CGUI;
//public:
//    CChatWindow();
//    ~CChatWindow();
//
//    void OnExitFromInput();
//    bool CheckScrollBar(int x, int y);
//
//    void AddChatMessage(char* szNick, uint32_t dwNickColor, char* szMessage);
//    void AddInfoMessage(const char* szFormat, ...);
//    void AddDebugMessage(char* szFormat, ...);
//    void AddClientMessage(uint32_t dwColor, char* szStr);
//
//protected:
//    void Render();
//    bool OnTouchEvent(int type, bool multi, int x, int y);
//
//public:
//    void RenderText(const char* u8Str, float posX, float posY, uint32_t dwColor);
//    void ResetHiding();
//
//    char* TimeInMessage(char* szMessage);
//
//    bool timeStamp;
//
//    ImVec2 pos;
//
//    float m_fChatPosX, m_fChatPosY;
//    float m_fChatSizeX, m_fChatSizeY;
//
//    float size;
//
//    bool show;
//
//    int NodeDouble;
//private:
//    void FilterInvalidChars(char* szString);
//    void AddToChatWindowBuffer(eChatMessageType eType, char* szString, char* szNick,
//                               uint32_t dwTextColor, uint32_t dwNickColor);
//    void PushBack(CHAT_WINDOW_ENTRY &entry);
//
//private:
//
//    bool m_bIsOpened;
//    bool bSwipeScroll;
//
//    int m_iMaxMessages;
//    int m_iOffsetY;
//    int m_iLastPosY;
//
//    int m_iTime;
//
//    //std::vector
//    std::list<CHAT_WINDOW_ENTRY> m_ChatWindowEntries;
//
//    uint32_t m_dwTextColor;
//    uint32_t m_dwInfoColor;
//    uint32_t m_dwDebugColor;
//};