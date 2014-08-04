
#include <iostream>
#define BOOL int
#define TRUE 1
#define FALSE 0
typedef char*   LPSTR;
#define LPCSTR  LPSTR
#define UINT int
#define PASCAL _stdcall
#define TRACE1 printf

#include "stdio.h"

class CObject;

struct CRuntimeClass 
{
	//Attributes12345
	LPCSTR	m_lpszClassName;
	int		m_nObjectSize;
	UINT	m_wSchema;
	CObject* (PASCAL* m_pfnCreateObject)();
	CRuntimeClass* m_pBaseClass;

	CObject* CreateObject();
	static CRuntimeClass* PASCAL Load();

	static CRuntimeClass* pFirstClass;
	CRuntimeClass* m_pNextClass;
};

#define DECLARE_DYNAMIC(class_name) \
public: \
	static CRuntimeClass class##class_name; \
	virtual CRuntimeClass* GetRuntimeClass() const;

#define DECLARE_DYNCREATE(class_name) \
	DECLARE_DYNAMIC(class_name) \
	static CObject* PASCAL CreateObject();

#define RUNTIME_CLASS(class_name) \
	(&class_name::class##class_name)

#define _IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, wSchema, pfnNew) \
	static char _lpsz##class_name[] = #class_name; \
	CRuntimeClass class_name::class##class_name = { \
	_lpsz##class_name, sizeof(class_name), wSchema, pfnNew, \
	RUNTIME_CLASS(base_class_name), NULL }; \
	static AFX_CLASSINIT _init_##class_name(&class_name::class##class_name); \
	CRuntimeClass* class_name::GetRuntimeClass() const \
		{ return &class_name::class##class_name; } \

#define IMPLEMENT_DYNAMIC(class_name, base_class_name) \
	_IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, NULL)

//添加到指针队列
struct AFX_CLASSINIT
{ AFX_CLASSINIT(CRuntimeClass* pNewClass); };

#define IMPLEMENT_DYNCREATE(class_name, base_class_name) \
	CObject* PASCAL class_name::CreateObject() \
{ return new class_name; } \
	_IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, \
	class_name::CreateObject)

class CObject
{
public:
	CObject::CObject() {std::cout<<"CObject Constructor"<<std::endl;}
	CObject::~CObject() {std::cout<<"CObject Destructor"<<std::endl;}

	BOOL IsKindOf(const CRuntimeClass* pClass) const;
	virtual CRuntimeClass* GetRuntimeClass() const;
	static CRuntimeClass classCObject;
};

class CCmdTarget : public CObject
{
	DECLARE_DYNAMIC(CCmdTarget)
public:
	CCmdTarget::CCmdTarget() {std::cout<<"CCmdTarget Constructor"<<std::endl;}
	CCmdTarget::~CCmdTarget() {std::cout<<"CCmdTarget Destructor"<<std::endl;}
};

class CWinThread : public CCmdTarget
{
	DECLARE_DYNAMIC(CWinThread)
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
	DECLARE_DYNCREATE(CWnd)
public:
	CWnd::CWnd() {std::cout<<"CWnd Constructor"<<std::endl;}
	CWnd::~CWnd() {std::cout<<"CWnd Destructor"<<std::endl;}

	virtual BOOL Create() {std::cout<<"CWnd::Create"<<std::endl; return TRUE;}
	virtual BOOL PreCreateWindow() {std::cout<<"CWnd::PreCreateWindow"<<std::endl;return TRUE;}
	BOOL CreateEx() {std::cout<<"CWnd::CreateEx"<<std::endl;
					PreCreateWindow();
					return TRUE;}
};

class CWinApp : public CWinThread
{
	DECLARE_DYNAMIC(CWinApp)
public:
	CWinApp* m_pCurrentWinApp; //main object
	CWnd* m_pMainWnd; //

public:
	CWinApp::CWinApp() {	m_pCurrentWinApp = this;
							std::cout<<"CWinApp Constructor"<<std::endl;}
	CWinApp::~CWinApp() {std::cout<<"CWinApp Destructor"<<std::endl;}

	virtual BOOL InitApplication() {std::cout<<"CWinApp::InitApplication"<<std::endl;
									return TRUE;}
	virtual BOOL InitInstance() {   std::cout<<"CWinApp::InitInstance"<<std::endl;
									return TRUE;}
	virtual BOOL Run() {std::cout<<"CWinApp::Run"<<std::endl;
						return TRUE;}
};

class CDocument : public CCmdTarget
{
	DECLARE_DYNAMIC(CDocument)
public:
	CDocument::CDocument() {std::cout<<"CDocument Constructor"<<std::endl;}
	CDocument::~CDocument() {std::cout<<"CDocument Destructor"<<std::endl;}
};

class CFrameWnd : public CWnd
{
	DECLARE_DYNCREATE(CFrameWnd)
public:
	CFrameWnd::CFrameWnd() {std::cout<<"CFrameWnd Constructor"<<std::endl;}
	CFrameWnd::~CFrameWnd() {std::cout<<"CFrameWnd Destructor"<<std::endl;}

	virtual BOOL Create() {std::cout<<"CFrameWnd Create"<<std::endl;
							CreateEx();
							return TRUE;}
	virtual BOOL PreCreateWindow() {std::cout<<"CFrameWnd PreCreateWindow"<<std::endl;return TRUE;}
};

class CView : public CWnd
{
	DECLARE_DYNAMIC(CView)
public:
	CView::CView() {std::cout<<"CView Constructor"<<std::endl;}
	CView::~CView() {std::cout<<"CView Destructor"<<std::endl;}
};

//global function
CWinApp* AfxGetApp();