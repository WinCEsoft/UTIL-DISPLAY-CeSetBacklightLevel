/*
*   Copyright (C) 2013 by Justus Wögerbauer
*   E-mail: jwoegerbauer@gmail.com
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
 
*
*   You should have received a copy of the GNU General Public License

*   along with this program; if not, see:
 
*
*               <http://www.gnu.org/licenses/>.                            
*/

//  NOTE: The registry settings for backlight are device/manufacturer dependent.

#include <Windows.h>

int IsNumeric(TCHAR *str);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, TCHAR * lpCmdLine, int nCmdShow)
{
 	TCHAR * lpCmdLineUpper;
	int retVal;
   	retVal=0;
	lpCmdLineUpper=_wcsupr(lpCmdLine);

	if(IsNumeric(lpCmdLineUpper))
	{
		DWORD dwBklLevel=(DWORD) atoi((const char *)lpCmdLineUpper);
		HKEY hKey;
		if(ERROR_SUCCESS==RegOpenKeyEx(HKEY_CURRENT_USER,TEXT("ControlPanel\\Backlight"),0,0,&hKey))
	    {
	       		 RegSetValueEx(hKey,TEXT("Brightness"),0,REG_DWORD,(BYTE*)&dwBklLevel,sizeof(DWORD));
			RegCloseKey(hKey);
			HANDLE hBL=CreateEvent(NULL,FALSE,FALSE,L"BackLightChangeEvent");
			if(hBL)
			{
				SetEvent(hBL);
				CloseHandle(hBL);
				retVal=1;
			}
 	   }
	}
	return retVal;
 }

int IsNumeric(TCHAR * str)
{
	while(*str)
	{
		if(!isdigit(*str))
			return 0;
		str++;
	}
	return 1;
}
