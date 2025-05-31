#include <windows.h>
#include "bofdefs.h"
#include "base.c"

#ifdef BOF

HINSTANCE SHELL32$ShellExecuteA(HWND   hwnd,LPCSTR lpOperation,LPCSTR lpFile, LPCSTR lpParameters, LPCSTR lpDirectory, INT    nShowCmd );

VOID go( 
	IN PCHAR Buffer, 
	IN ULONG Length 
) 
{

	datap parser = {};
	BeaconDataParse(&parser, Buffer, Length);
	int link_size;
	char * link_value = BeaconDataExtract(&parser, &link_size);
	// It is a string because the registry value is a string

	if(!bofstart())
	{
		return;
	}
	
	HINSTANCE result = SHELL32$ShellExecuteA(NULL,"open", link_value,NULL,NULL,SW_SHOWNORMAL);


	if((INT_PTR)result > 32){
		BeaconPrintf(0,"Success");
	} else {
		BeaconPrintf(CALLBACK_ERROR,"Failed to open with HINSTANCE %d", result);
	}

};

#else

int main()
{
//code for standalone exe for scanbuild / leak checks
}

#endif
