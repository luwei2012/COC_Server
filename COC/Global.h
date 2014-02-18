/*
*Global.h
*
*2011-08
*
*/
#pragma once
#ifndef _GLOBAL_H_
#define _GLOBAL_H_


/**************************************************************/
static const char	g_simSeps[] = ",\n";

#define		INI_AUTO_START				0 
#define		INI_USR_PATH				1
#define		INI_POP_UP_NOTIFY			2 
#define		INI_SKIN_PATH				3
#define		INI_AUTO_TYPE				4

static const char* g_INI[] =
{
	"auto start", 
	"user path",
	"pop up notify", 
	"skin path",
	"auto type"
};

static const char appName[]= "clash of clans client";

#endif