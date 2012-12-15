
#include "Window.h"
#include <tchar.h>
bool Window::CreateDisplay(unsigned int _width, unsigned int _height)
{
	WNDCLASSEX m_windowClass;
	m_windowClass.cbSize          = sizeof(WNDCLASSEX);
	m_windowClass.style           = CS_HREDRAW | CS_VREDRAW;
	m_windowClass.lpfnWndProc     = Window::StaticWndProc; //We set our static method as the event handler
	m_windowClass.cbClsExtra      = 0;
	m_windowClass.cbWndExtra      = 0;
	m_windowClass.hInstance       = m_hInstance;
	m_windowClass.hIcon           = LoadIcon(NULL, IDI_APPLICATION);  // default icon
	m_windowClass.hCursor         = LoadCursor(NULL, IDC_ARROW);      // default arrow
	m_windowClass.hbrBackground   = NULL;                             // don't need background
	m_windowClass.lpszMenuName    = NULL;                             // no menu
	m_windowClass.lpszClassName   = "GLClass";
	m_windowClass.hIconSm         = LoadIcon(NULL, IDI_WINLOGO);      // windows logo small icon

	// register the windows class
	if (!RegisterClassEx(&m_windowClass))
	{
		MessageBox(NULL, _T("Class Register Failed"),_T("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	RECT rc;
	SetRect(&rc, 0,0,_width, _height);
	DWORD  dwExStyle;       // Window Extended Style
	DWORD  dwStyle;         // Window Style
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;   // Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;                    // Windows Style
	

	//AdjustWindowRectEx(&rc, dwStyle, false, dwExStyle);     // Adjust Window To True Requested Size

	// cretate the window.
	m_hwnd = CreateWindowEx(NULL,                                 // extended style
		"GLClass",                          // class name
		"GLClass",      // app name
		dwStyle | WS_CLIPCHILDREN |	WS_CLIPSIBLINGS,0, 0,_width, _height,NULL,NULL,	m_hInstance,this); 
	if(!m_hwnd)
	{
		MessageBox(NULL, _T("Window Creation Failed"),_T("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	EGLNativeWindowType eglWnd = m_hwnd;
	m_hdc = GetDC(m_hwnd);
	
	eglDisplay = eglGetDisplay(m_hdc);
	if(eglDisplay == EGL_NO_DISPLAY)
	{
		// get the default display
		eglDisplay = eglGetDisplay((EGLNativeDisplayType)EGL_DEFAULT_DISPLAY);
	}// end if no display

	// initiliased the egl
	EGLint iMjrVersion, iMinrVer;
	if(!eglInitialize(eglDisplay, &iMjrVersion,&iMinrVer))
	{
		MessageBox(NULL, _T("EGL Initilisation Failed"),_T("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	// set GLES as te current API
	eglBindAPI(EGL_OPENGL_ES_API);
	// validate

	///choose the right configuration.
	const EGLint config32attrib[] = {EGL_LEVEL,0,
									EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
									EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
									EGL_NATIVE_RENDERABLE, EGL_FALSE,
									EGL_DEPTH_SIZE, EGL_DONT_CARE,
									EGL_NONE};
	EGLint iconfig;
	EGLConfig eglConfig;
	if(!eglChooseConfig(eglDisplay, config32attrib, &eglConfig,1, &iconfig))
	{
		MessageBox(NULL, _T("eglChooseConfigfailed"),_T("ERROR"),MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	
	m_eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, eglWnd, NULL);
	if(m_eglSurface == EGL_NO_SURFACE)
	{
		//clear the error
		eglGetError();
		m_eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, NULL, NULL);
	}// end if no surface created.
	// create the context.
	EGLint contxt32Attrib[] = {EGL_CONTEXT_CLIENT_VERSION,2,EGL_NONE};
	m_eglContext = eglCreateContext(eglDisplay, eglConfig, NULL, contxt32Attrib);
	if(m_eglContext == EGL_NO_CONTEXT)return false;
	if(!eglMakeCurrent(eglDisplay, m_eglSurface, m_eglSurface, m_eglContext))
		return false;
	ShowWindow(m_hwnd,TRUE);
	m_isRunning = true;
	return true;
}

Window::Window(HINSTANCE _hInstance) : m_hwnd(NULL), m_hdc(0), m_hInstance(_hInstance),m_eglContext(0),eglDisplay(0),m_eglSurface(0), m_isRunning(false)
{

}

Window::~Window()
{
	ShutDown();
}

void Window::ShutDown(void)
{
	eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE,EGL_NO_CONTEXT);
	eglTerminate(eglDisplay);
	if(m_hdc)ReleaseDC(m_hwnd,m_hdc);
	m_hwnd = 0; m_hdc = 0;
}

LRESULT CALLBACK Window::StaticWndProc(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lparam)
{
	// handle the window create mesgae
	Window *pWnd  = NULL;
	if(_msg == WM_CREATE)
	{
		pWnd = (Window*)((LPCREATESTRUCT)_lparam)->lpCreateParams;
		SetWindowLongPtr(_hwnd, GWL_USERDATA, (LONG_PTR)pWnd);
	}
	else
	{
		pWnd = (Window*)GetWindowLongPtr(_hwnd, GWL_USERDATA);
	}
	// pass it to the window to process the message, or to the OS if window not found
	return (pWnd) ? pWnd->WndProc(_hwnd, _msg, _wParam, _lparam) : DefWindowProc(_hwnd, _msg, _wParam, _lparam);
}

LRESULT Window::WndProc(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{
	switch(_msg){// handle the messaegs
	case WM_CREATE:
		//CreateDisplay(800,640);
		break;
	case WM_CLOSE: 
	case WM_DESTROY:
		m_isRunning  = false;
		//ShutDown();
		return 0;
		break;
	default :DefWindowProc(_hwnd, _msg, _wParam, _lParam);
	}
	return 0;
	
}

bool Window::InitWindow(unsigned int _width, unsigned int _height)
{
	return CreateDisplay(_width, _height);
}

void Window::ProcessMsg(void)
{
	MSG _msg; 
	while(PeekMessage(&_msg,m_hwnd,0,0,PM_REMOVE))
	{
		TranslateMessage(&_msg);
		DispatchMessage(&_msg);
	}
}