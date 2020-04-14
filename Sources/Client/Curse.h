// Curse.h: interface for the CCurse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURSE_H__2B4366FB_979F_4E8C_83AA_F7B3C002E4E7__INCLUDED_)
#define AFX_CURSE_H__2B4366FB_979F_4E8C_83AA_F7B3C002E4E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCurse  
{
public:
	CCurse();
	virtual ~CCurse();
	void LoadCurse(const char *filename);
	bool IsCurse(const char *str);
	char *ConvertString(char *str, int max_len);
	void filterChar(const char *src, char *dst, const char *chars);
	char* getField(const char *buf, int delim, char *field);
};

#endif // !defined(AFX_CURSE_H__2B4366FB_979F_4E8C_83AA_F7B3C002E4E7__INCLUDED_)
