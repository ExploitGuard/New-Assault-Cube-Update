// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <cstdint>
#include <cstdio>
#include <Windows.h>
#include <iostream>
#include <string>

// Created with ReClass.NET 1.2 by KN4CK3R


DWORD localPlayer = 0x17B0B8;

class Entity
{
public:
	char pad_0000[ 236 ]; //0x0000
	int32_t Health; //0x00EC
	int32_t Armor; //0x00F0
	char pad_00F4[ 56 ]; //0x00F4
	int32_t PistolAmmo; //0x012C
	char pad_0130[ 16 ]; //0x0130
	int32_t RifleAmmo; //0x0140
	int32_t GrenadeAmmo; //0x0144
	char pad_0148[ 4 ]; //0x0148
	int32_t KnifeTime; //0x014C
	int32_t PistolTime; //0x0150
	char pad_0154[ 16 ]; //0x0154
	int32_t RifleTime; //0x0164
	int32_t GrenadeTime; //0x0168
	char pad_016C[ 152 ]; //0x016C
	char Namee[ 16 ]; //0x0204
	char pad_0214[ 3644 ]; //0x0214
}; //Size: 0x1050

Entity* ent = nullptr;

DWORD WINAPI MainThread ( HMODULE hModule )
{
	AllocConsole ( );
	FILE* f;
	freopen_s ( &f , "CONIN$" , "r" , stdin );
	freopen_s ( &f , "CONOUT$" , "w" , stdout );
	freopen_s ( &f , "CONOUT$" , "w" , stderr );

	uintptr_t gameBase = ( uintptr_t ) GetModuleHandleA ( "ac_client.exe" );

	ent = *( Entity** ) (gameBase + localPlayer);

	std::string nameInput = ".";

	std::cout << "Pick a Name: ";

	std::cin >> nameInput;

	const char* newname = nameInput.c_str ( );

	while ( true )
	{
		ent->Health = 999;
		ent->Armor = 999;
		ent->GrenadeAmmo = 999;
		ent->GrenadeTime = 0;
		ent->RifleAmmo = 999;
		ent->RifleTime = 0;
		ent->KnifeTime = 0;
		ent->PistolAmmo = 999;
		ent->PistolTime = 0;


		if ( GetAsyncKeyState ( VK_INSERT ) & 1 )
		{
			for ( int i = 0; i < 16; i++ ) {
				ent->Namee[ i ] = newname[ i ];
			}
		}
		if ( GetAsyncKeyState ( VK_END ) & 1 )
		{
			fclose ( f );
			FreeLibraryAndExitThread ( hModule , 69 );
			exit ( 0 );
		}
	}

	return 0;
}

BOOL APIENTRY DllMain ( HMODULE hModule ,
    DWORD  ul_reason_for_call ,
    LPVOID lpReserved
)
{
    switch ( ul_reason_for_call )
    {
    case DLL_PROCESS_ATTACH:
        CreateThread ( NULL , NULL , ( LPTHREAD_START_ROUTINE ) MainThread , hModule , NULL , NULL );
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

