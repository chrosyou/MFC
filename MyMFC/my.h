
#include "MFC.h"

class CMyWinApp : public CWinApp
{
public:
	CMyWinApp::CMyWinApp() {std::cout<<"CMyWinApp Constructor"<<std::endl;}
	CMyWinApp::~CMyWinApp() {std::cout<<"CMyWinApp Destructor"<<std::endl;}
};

class CMyFrameWnd : public CFrameWnd
{
public:
	CMyFrameWnd::CMyFrameWnd() {std::cout<<"CMyFrameWnd Constructor"<<std::endl;}
	CMyFrameWnd::~CMyFrameWnd() {std::cout<<"CMyFrameWnd Destructor"<<std::endl;}
};