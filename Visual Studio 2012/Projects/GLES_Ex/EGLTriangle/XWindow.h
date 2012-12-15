#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include "esUtil.h"

static Display *gDisplay;

bool CreateDisplay(Display *pDisplay)
{
	pDisplay = NULL;
	pDisplay = XOpenDisplay(NULL);
	if(!display)
	{
		printf("XOpenDisplay Failed\n");
	}
	return true;
}

EGLBoolean CreateEGLContext(EGLNativeWindowType hWnd, EGLDisplay* eglDisplay, EGLContext* _context,
							EGLSurface *eglSurface,EGLint attribList[])
{
	EGLDisplay display = eglGetDisplay((EGLNativeWindowType)gDisplay);
	if(display == EGL_NO_DISPLAY)
	{
		printf("No Display found\n");
		return EGL_FALSE;
	}
	// initialize the egl
	EGLint major, minor;
	if(!eglInitialize(display,&major, &minor))
	{
		printf("eglInitialise Failed\n");
		return EGL_FALSE;
	}

	// get the configurations
	EGLint numConfig;
	if(!eglGetConfigs(display, NULL, 0,&numConfig))
	{
		printf("eglGetConfig Failed\n");
		return EGL_FALSE;
	}
	EGLConfig config;
	if(!eglChooseConfig(display,attribList,&config,1,&numConfig))
	{
		return EGL_FALSE;
	}

	// create the surface
	EGLSurface surface = eglCreateWindowSurface(display,config, (EGLNativeWindowType)hWnd, NULL)
	{
		printf("EGLCreateWindowSurface Failed\n");
		return EGL_FALSE;
	}
	EGLint contextAttrib[] = {EGL_CONTEXT_CLIENT_VERSION, 2,EGL_NONE};
	EGLContext contxt = eglCreateContext(display,config,EGL_NO_CONTEXT, contextAttrib);
	if(contxt == EGL_NO_CONTEXT)
	{
		printf("EGLCreateContextFailed \n");
		return EGL_FALSE;
	}


	*eglDisplay = display;
	*eglSurface = surface;
	*EGLContext = contxt;

	if(!eglMakeCurrent(display, surface, surface,contxt))
	{
		printf("EglMakeCurrent Failed \n");
		return EGL_FALSE;
	}

	return EGL_TRUE;
}

bool CreateWindow(Display *pDisplay)
{
	XVisualInfo *vInfo = NULL;

}



