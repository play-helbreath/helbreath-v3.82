

#if !defined(AFX_SECURITYINT_H__21765369_AE5A_4801_9422_A18537972861__INCLUDED_)
#define AFX_SECURITYINT_H__21765369_AE5A_4801_9422_A18537972861__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include <iostream>
#include <windows.h>
#include <Winbase.h>

class CInt ;

class CInt 
{
public:
	CInt() ;
	~CInt() ;
	int Get() ;
	void Set(const int & iValue) ;
	CInt & operator=(const int &iValue) ;
	operator int() ;
//	bool operator==(const int &iValue) ;
//	bool operator!=(const int &iValue) ;

protected :
	int * m_pValue ;
	int m_iKeyValue ;
	unsigned long old ;

};

#endif //#define AFX_SECURITYINT_H__21765369_AE5A_4801_9422_A18537972861__INCLUDED_