#pragma once

#ifndef __COMMON_H
#define __COMMON_H

#define CLIENT_DESCRIPTION "Slice & Slice"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include <tchar.h>
#endif

#include <Ogre.h>
#include <OIS/OIS.h>
#include <Overlay/OgreOverlay.h>
#include <Overlay/OgreOverlaySystem.h>
#include <Overlay/OgreOverlayManager.h>
#include <Overlay/OgreOverlayElement.h>
#include <Overlay/OgreTextAreaOverlayElement.h>
#include <Overlay/OgreFontManager.h>

#include <iostream>
#include <map>
#include <vector>

using namespace Ogre;
using namespace std;

#endif