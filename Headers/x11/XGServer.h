/* <title>XGServer</title>

   <abstract>Backend server using the X11.</abstract>

   Copyright (C) 2002 Free Software Foundation, Inc.

   Author: Adam Fedor <fedor@gnu.org>
   Date: Mar 2002
   
   This file is part of the GNUstep Backend.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; see the file COPYING.LIB.
   If not, see <http://www.gnu.org/licenses/> or write to the 
   Free Software Foundation, 51 Franklin Street, Fifth Floor, 
   Boston, MA 02110-1301, USA.
*/

#ifndef _XGServer_h_INCLUDE
#define _XGServer_h_INCLUDE

#include "config.h"

#include <GNUstepGUI/GSDisplayServer.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "x11/XGGeneric.h"
#ifdef HAVE_LIBXEXT
#include <X11/extensions/sync.h>
#endif
/*
 * Enumerated type to say how we should draw pixels to the X display - used
 * to select different drawing mechanisms to try to optimise.
 */
typedef enum {
  XGDM_FAST15,
  XGDM_FAST16,
  XGDM_FAST32,
  XGDM_FAST32_BGR,
  XGDM_FAST8,
  XGDM_PORTABLE
} XGDrawMechanism;

@interface XGServer : GSDisplayServer
{
  Display           *dpy;
  NSInteger         defScreen;
  NSMapTable        *screenList;
  Window	    grabWindow;
  struct XGGeneric  generic;
  id                inputServer;
}

+ (Display*) currentXDisplay;
- (Display*) xDisplay;
- (Window) xAppRootWindow;

- (void *) xrContextForScreen: (NSInteger)screenNumber;
- (Visual *) visualForScreen: (NSInteger)screenNumber;
- (int) depthForScreen: (NSInteger)screenNumber;

- (XGDrawMechanism) drawMechanismForScreen: (NSInteger)screenNumber;
- (void) getForScreen: (NSInteger)screenNumber pixelFormat: (NSInteger *)bitsPerPixel
                masks: (NSUInteger *)red_mask : (NSUInteger *)green_mask : (NSUInteger *)blue_mask;
- (Window) xDisplayRootWindowForScreen: (NSInteger)screenNumber;
- (XColor) xColorFromColor: (XColor)color forScreen: (NSInteger)screenNumber;

+ (void) waitAllContexts;
@end

/*
 * Synchronize with X event queue - soak up events.
 * Waits for up to 1 second for event.
 */
@interface XGServer (XSync)
- (BOOL) xSyncMap: (void*)window;
@end

@interface XGServer (XGGeneric)
- (NSRect) _OSFrameToXFrame: (NSRect)o for: (void*)window;
- (NSRect) _OSFrameToXHints: (NSRect)o for: (void*)window;
- (NSRect) _XFrameToOSFrame: (NSRect)x for: (void*)window;
- (NSRect) _XFrameToXHints: (NSRect)o for: (void*)window;
@end

// Public interface for the input methods.  
@interface XGServer (InputMethod)
- (NSString *) inputMethodStyle;
- (NSString *) fontSize: (int *)size;
- (BOOL) clientWindowRect: (NSRect *)rect;

- (BOOL) statusArea: (NSRect *)rect;
- (BOOL) preeditArea: (NSRect *)rect;
- (BOOL) preeditSpot: (NSPoint *)p;

- (BOOL) setStatusArea: (NSRect *)rect;
- (BOOL) setPreeditArea: (NSRect *)rect;
- (BOOL) setPreeditSpot: (NSPoint *)p;
@end

@interface XGServer (TimeKeeping)
- (void) setLastTime: (Time)last;
- (Time) lastTime;
@end

#endif /* _XGServer_h_INCLUDE */
