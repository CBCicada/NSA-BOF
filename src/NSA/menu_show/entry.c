#include <windows.h>
#include "bofdefs.h"
#include "base.c"

#ifdef BOF
VOID go( 
	IN PCHAR Buffer, 
	IN ULONG Length 
) 
{

	datap parser = {};
	BeaconDataParse(&parser, Buffer, Length);
	int new_size;
	char * new_value = BeaconDataExtract(&parser, &new_size);
	// It is a string because the registry value is a string

	if(!bofstart())
	{
		return;
	}
	
	HKEY hKey;
	LSTATUS result = ADVAPI32$RegOpenKeyExA(HKEY_CURRENT_USER, "Control Panel\\Desktop", 0, KEY_QUERY_VALUE | KEY_SET_VALUE, &hKey);

	if(result != ERROR_SUCCESS){
		BeaconPrintf(CALLBACK_ERROR, "Failed to open key\n");
		return;
	}

	DWORD type;
	BYTE * data;
	DWORD size;

	result = ADVAPI32$RegQueryValueExA(hKey, "MenuShowDelay", NULL, &type, NULL, &size);

	if(result == ERROR_FILE_NOT_FOUND){
		BeaconPrintf(CALLBACK_OUTPUT, "Key doesn't exist\n");
		goto SETKEY;
	}

	if(result != ERROR_SUCCESS){
		BeaconPrintf(CALLBACK_ERROR, "Failed to query key\n");
		return;
	}

	data = intAlloc(size + 2);// this ensures it is null terminated
	
	if(data == NULL){
		BeaconPrintf(CALLBACK_ERROR, "Failed to allocate\n");
		return;
	}

	result = ADVAPI32$RegQueryValueExA(hKey, "MenuShowDelay", NULL, &type, data, &size);

	if(result != ERROR_SUCCESS){
		BeaconPrintf(CALLBACK_ERROR, "Failed to query key\n");
		return;
	}

	BeaconPrintf(CALLBACK_OUTPUT, "Original Value: %s\n", data);

	SETKEY:

	result = ADVAPI32$RegSetValueExA(hKey, "MenuShowDelay", 0, REG_SZ, new_value, (DWORD)new_size);
	if(result != ERROR_SUCCESS){
		BeaconPrintf(CALLBACK_ERROR, "Failed to set key value\n");
	} else {
		BeaconPrintf(CALLBACK_OUTPUT, "Successfully set key value\n");
	}


};

#else

int main()
{
//code for standalone exe for scanbuild / leak checks
}

#endif
