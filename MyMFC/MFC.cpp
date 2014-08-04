
#include "my.h"

extern CMyWinApp theApp;

CRuntimeClass* CRuntimeClass::pFirstClass = NULL;

static char szCObject[] = "CObject";
struct CRuntimeClass CObject::classCObject =
{ szCObject, sizeof(CObject), 0xffff, NULL, NULL };

static AFX_CLASSINIT _init_CObject(&CObject::classCObject);
AFX_CLASSINIT::AFX_CLASSINIT(CRuntimeClass* pNewClass)
{
	pNewClass->m_pNextClass = CRuntimeClass::pFirstClass;
	CRuntimeClass::pFirstClass = pNewClass;
}

CObject* CRuntimeClass::CreateObject()
{
	if (m_pfnCreateObject == NULL)
	{
		TRACE1("Error: Trying to create object which is not "
			"DECLARE_DYNCREATE \nor DECLARE_SERIAL: %hs.\n",
			m_lpszClassName);
		return NULL;
	}

	CObject* pObject = NULL;
	pObject = (*m_pfnCreateObject)();

	return pObject;
}

CRuntimeClass* PASCAL CRuntimeClass::Load()
{
	char szClassName[64];
	CRuntimeClass* pClass;

	// JJHOU : instead of Load from file, we Load from cin.
	std::cout << "enter a class name...  ";
	std::cin >> szClassName;

	for (pClass = pFirstClass; pClass != NULL; pClass = pClass->m_pNextClass)
	{
		if (strcmp(szClassName, pClass->m_lpszClassName) == 0)
			return pClass;
	}

	TRACE1("Error: Class not found: %s \n", szClassName);
	return NULL; // not found
}

CRuntimeClass* CObject::GetRuntimeClass() const
{
	return &CObject::classCObject;
}

BOOL CObject::IsKindOf(const CRuntimeClass* pClass) const
{
	CRuntimeClass* pClassThis = GetRuntimeClass();
	while (pClassThis != NULL)
	{
		if (pClassThis == pClass)
			return TRUE;
		pClassThis = pClassThis->m_pBaseClass;
	}
	return FALSE;       // walked to the top, no match
}

CWinApp* AfxGetApp()
{
	return theApp.m_pCurrentWinApp;
}

IMPLEMENT_DYNAMIC(CCmdTarget, CObject)
IMPLEMENT_DYNAMIC(CWinThread, CCmdTarget)
IMPLEMENT_DYNCREATE(CWnd, CWinThread)
IMPLEMENT_DYNCREATE(CFrameWnd, CWnd)
IMPLEMENT_DYNAMIC(CView, CWnd)
IMPLEMENT_DYNAMIC(CWinApp, CWinThread)
IMPLEMENT_DYNAMIC(CDocument, CWinThread)

IMPLEMENT_DYNCREATE(CMyWinApp, CWinApp)
IMPLEMENT_DYNCREATE(CMyFrameWnd, CFrameWnd)