
#include "MFC.h"

class CMyFrameWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CMyFrameWnd)
public:
	CMyFrameWnd::CMyFrameWnd() {std::cout<<"CMyFrameWnd Constructor"<<std::endl;Create();}
	CMyFrameWnd::~CMyFrameWnd() {std::cout<<"CMyFrameWnd Destructor"<<std::endl;}
};

class CMyWinApp : public CWinApp
{
	DECLARE_DYNCREATE(CMyWinApp)
public:
	CMyWinApp::CMyWinApp() {std::cout<<"CMyWinApp Constructor"<<std::endl;}
	CMyWinApp::~CMyWinApp() {std::cout<<"CMyWinApp Destructor"<<std::endl;}
	virtual BOOL InitInstance() {std::cout<<"CMyWinApp InitInistance"<<std::endl;
									m_pMainWnd = new CMyFrameWnd;
									return TRUE;}
};

void PrintAllClasses();