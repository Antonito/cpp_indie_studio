#ifndef OSX_PORT_H_
#define OSX_PORT_H_

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang system_header
#endif

#include "OgrePlatform.h"

#if OGRE_PLATFORM != OGRE_PLATFORM_APPLE
#error This header is for use with Mac OS X only
#endif

#ifdef __OBJC__

#define USE_DISPLAYLINK 0

#import "OgreOSXCocoaWindow.h"
#import <QuartzCore/CVDisplayLink.h>

// All this does is suppress some messages in the run log.  NSApplication does
// not
// implement buttonPressed and apps without a NIB have no target for the action.
@implementation NSApplication (_suppressUnimplementedActionWarning)
- (void)buttonPressed:(id)sender {
  // Do nothing
}
@end

#if defined(MAC_OS_X_VERSION_10_6) &&                                          \
    MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_X_VERSION_10_6
@interface AppDelegate : NSObject <NSApplicationDelegate>
#else
@interface AppDelegate : NSObject
#endif
{
  NSTimer *mTimer;

  NSDate *mDate;
  NSTimeInterval mLastFrameTime;
  CVDisplayLinkRef mDisplayLink; // display link for managing rendering thread
}

- (void)go;
- (void)renderOneFrame:(id)sender;
- (void)shutdown;

@property(retain, atomic) NSTimer *mTimer;
@property(nonatomic) NSTimeInterval mLastFrameTime;

@end

// Actual code

#if __LP64__
static id mAppDelegate;

// DisplayLink callback
#if USE_DISPLAYLINK
static CVReturn
MyDisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp *now,
                      const CVTimeStamp *outputTime, CVOptionFlags flagsIn,
                      CVOptionFlags *flagsOut, void *displayLinkContext) {
  return kCVReturnSuccess;
}
#endif
#endif

@implementation AppDelegate

@synthesize mTimer;
@dynamic mLastFrameTime;

- (NSTimeInterval)mLastFrameTime {
  return mLastFrameTime;
}

- (void)setLastFrameTime:(NSTimeInterval)frameInterval {
  // Frame interval defines how many display frames must pass between each time
  // the
  // display link fires. The display link will only fire 30 times a second when
  // the
  // frame internal is two on a display that refreshes 60 times a second. The
  // default
  // frame interval setting of one will fire 60 times a second when the display
  // refreshes
  // at 60 times a second. A frame interval setting of less than one results in
  // undefined
  // behavior.
  if (frameInterval >= 1) {
    mLastFrameTime = frameInterval;
  }
}

- (void)go {

  NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
  mLastFrameTime = 1;
  mTimer = nil;

  try {
    std::cout << "BIIIITE" << std::endl;
    Ogre::Root::getSingleton().getRenderSystem()->_initRenderTargets();

    // Clear event times
    Ogre::Root::getSingleton().clearEventTimes();
  } catch (Ogre::Exception &e) {
    std::cerr << "An exception has occurred: " << e.getFullDescription().c_str()
              << std::endl;
  }
#if __LP64__ && USE_DISPLAYLINK
  CVReturn ret = kCVReturnSuccess;

  // Create a display link capable of being used with all active displays
  ret = CVDisplayLinkCreateWithActiveCGDisplays(&mDisplayLink);

  // Set the renderer output callback function
  ret = CVDisplayLinkSetOutputCallback(mDisplayLink, &MyDisplayLinkCallback,
                                       self);

  // Set the display link for the current renderer
  CGLContextObj cglContext = (CGLContextObj)[ctx CGLContextObj];
  CGLPixelFormatObj cglPixelFormat = (CGLPixelFormatObj)[fmt CGLPixelFormatObj];
  ret = CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(
      mDisplayLink, cglContext, cglPixelFormat);

  // Activate the display link
  ret = CVDisplayLinkStart(mDisplayLink);
#else
  mTimer = [[NSTimer timerWithTimeInterval:0.001
                                    target:self
                                  selector:@selector(renderOneFrame:)
                                  userInfo:self
                                   repeats:true] retain];
  [[NSRunLoop currentRunLoop] addTimer:mTimer forMode:NSDefaultRunLoopMode];
  [[NSRunLoop currentRunLoop]
      addTimer:mTimer
       forMode:NSEventTrackingRunLoopMode]; // Ensure timer fires during resize
#endif
  [pool release];
}

- (void)applicationDidFinishLaunching:(NSNotification *)application {

  mLastFrameTime = 1;
  mTimer = nil;
  std::cout << "Application Did Finish Launching" << std::endl;
  [self go];
}

- (void)shutdown {
  // TODO
  [NSApp terminate:nil];
}

- (void)renderOneFrame:(id)sender {
  // TODO
  std::cout << "RENDERING ONE FRAME" << std::endl;
}

@end

#endif

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif
