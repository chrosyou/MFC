
#include <iostream>
#define BOOL int
#define TRUE 1
#define FALSE 0

class CObject
{
public:
	CObject::CObject() {std::cout<<"CObject Constructor"<<std::endl;}
	CObject::~CObject() {std::cout<<"CObject Destructor"<<std::endl;}
};

class CCmdTarget : public CObject
{
public:
	CCmdTarget::CCmdTarget() {std::cout<<"CCmdTarget Constructor"<<std::endl;}
	CCmdTarget::~CCmdTarget() {std::cout<<"CCmdTarget Destructor"<<std::endl;}
};

class CWinThread : public CCmdTarget
{
public:
	CWinThread::CWinThread() {std::cout<<"CWinThread Constructor"<<std::endl;}
	CWinThread::~CWinThread() {std::cout<<"CWinThread Destructor"<<std::endl;}

	virtual BOOL InitInstance() {
									std::cout<<"CWinThread::InitInstance"<<std::endl;
									return TRUE;}

	virtual int Run() { std::cout<<"CWinThread::Run"<<std::endl;
						return true;}
};

class CWnd : public CCmdTarget
{
public:
	CWnd::CWnd() {std::cout<<"CWnd Constructor"<<std::endl;}
	CWnd::~CWnd() {std::cout<<"CWnd Destructor"<<std::endl;}

	virtual BOOL Create() {std::cout<<"CWnd::Create"<<std::endl; return TRUE;}
	BOOL CreateEx() {std::cout<<"CWnd::CreateEx"<<std::endl;return TRUE;}
	virtual BOOL PreCreateWindow() {std::cout<<"CWnd::PreCreateWindow"<<std::endl;return TRUE;};
};

class CWinApp : public CWinThread
{
public:
	CWinApp* m_pCurrentWinApp;
	CWnd* m_pMainWnd;

public:
	CWinApp::CWinApp() {	m_pCurrentWinApp = this;
							std::cout<<"CWinApp Constructor"<<std::endl;}
	CWinApp::~CWinApp() {std::cout<<"CWinApp Destructor"<<std::endl;}

	virtual BOOL InitInstance() {   std::cout<<"CWinApp::InitInstance"<<std::endl;
									return TRUE;}
	virtual BOOL Run() {std::cout<<"CWinApp::Run"<<std::endl;
						return TRUE;}
};

class CDocument : public CCmdTarget
{
public:
	CDocument::CDocument() {std::cout<<"CDocument Constructor"<<std::endl;}
	CDocument::~CDocument() {std::cout<<"CDocument Destructor"<<std::endl;}
};

class CFrameWnd : public CWnd
{
public:
	CFrameWnd::CFrameWnd() {std::cout<<"CFrameWnd Constructor"<<std::endl;}
	CFrameWnd::~CFrameWnd() {std::cout<<"CFrameWnd Destructor"<<std::endl;}

	virtual BOOL Create() {return TRUE;}
	virtual BOOL PreCreateWindow() {return TRUE;}
};

class CView : public CWnd
{
public:
	CView::CView() {std::cout<<"CView Constructor"<<std::endl;}
	CView::~CView() {std::cout<<"CView Destructor"<<std::endl;}
};

//global function
CWinApp* AfxGetApp();