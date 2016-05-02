#pragma once

#define CLIENT_DESCRIPTION "Slice & Slice"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#include <Ogre.h>
#include <OIS/OIS.h>
#include <iostream>
#include <map>

using namespace Ogre;
using namespace std;