// CRCdemo.h


#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

class  CRCdemo;

class CRCdemo
{
public:
	CRCdemo();
	virtual ~CRCdemo();
    void Init_CRC32_Table(void);						// Builds lookup table array
	int Get_CRC(char* text, int len);					// Creates a CRC from a text string

protected:
	unsigned long crc32_table[256];						// Lookup table array
    unsigned long Reflect(unsigned long ref, char ch);  // Reflects CRC bits in the lookup table
    //int Get_CRC(CString& text);						// Creates a CRC from a text string

};