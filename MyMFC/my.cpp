
#include "my.h"
using namespace std;
CMyWinApp theApp;

int main()
{
	CWinApp* pMyDoc = AfxGetApp();
	
	
	cout << "pMyDoc->IsKindOf(RUNTIME_CLASS(CDocument))  " << pMyDoc->IsKindOf(RUNTIME_CLASS(CDocument))    << "\n";
	cout << "pMyDoc->IsKindOf(RUNTIME_CLASS(CCmdTarget)) " << pMyDoc->IsKindOf(RUNTIME_CLASS(CCmdTarget))   << "\n";
	cout << "pMyDoc->IsKindOf(RUNTIME_CLASS(CObject))    " << pMyDoc->IsKindOf(RUNTIME_CLASS(CObject))      << "\n";
	cout << "pMyDoc->IsKindOf(RUNTIME_CLASS(CWinApp))    " << pMyDoc->IsKindOf(RUNTIME_CLASS(CWinApp))      << "\n";
	cout << "pMyDoc->IsKindOf(RUNTIME_CLASS(CView))      " << pMyDoc->IsKindOf(RUNTIME_CLASS(CView))        << "\n";
	return 0;
}

void PrintAllClasses()
{
	CRuntimeClass* cPrint = NULL;
	cPrint = CRuntimeClass::pFirstClass;
	while (cPrint != NULL)
	{
		if (cPrint->m_pBaseClass != NULL)
		{
			std::cout<<cPrint->m_lpszClassName<<"	"<<cPrint->m_nObjectSize<<"	"<<cPrint->m_pBaseClass->m_lpszClassName<<std::endl;
		}
		else std::cout<<cPrint->m_lpszClassName<<"	"<<cPrint->m_nObjectSize<<"	NULL"<<std::endl;
		
		cPrint = cPrint->m_pNextClass;
	}
}