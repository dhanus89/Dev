#ifndef WINDOW_H
#define WINDOW_H
#include<stdio.h>
#include <windows.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
class Window
{
public:
	// App entry point for creating the window
	static LRESULT CALLBACK StaticWndProc(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lparam);
	LRESULT WndProc(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

	/*!***********************************************************************************************
	 * @fn	Window::Window();
	 *
	 * @brief	Default constructor.
	 *************************************************************************************************/
	Window(HINSTANCE _hInstance);

	/*!***********************************************************************************************
	 * @fn	Window::~Window();
	 *
	 * @brief	Destructor.
	 *************************************************************************************************/
	~Window();

	/*!***********************************************************************************************
	 * @fn	bool Window::InitWindow(unsigned int _width, unsigned int _height);
	 *
	 * @brief	Initialises the window.
	 *
	 * @param	_width 	The width.
	 * @param	_height	The height.
	 *
	 * @return	true if it succeeds, false if it fails.
	 *************************************************************************************************/
	bool InitWindow(unsigned int _width, unsigned int _height);

	void SwapBuffers(void);

	void ShutDown(void);

	bool IsRunning(void)const{return m_isRunning;}

	void ProcessMsg(void);

	EGLDisplay* GetEGLDisplay(void) {return &eglDisplay;}
	EGLContext* GetEGLContext(void){return &m_eglContext;}
	EGLSurface* GetEGLSurface(void){return &m_eglSurface;}
private:

	/*!***********************************************************************************************
	 * @fn	bool Window::CreateDisplay(unsigned _width, unsigned int _height);
	 *
	 * @brief	Creates a display.
	 *
	 * @param	_width 	The width.
	 * @param	_height	The height.
	 *
	 * @return	The new display.
	 *************************************************************************************************/
	bool CreateDisplay(unsigned _width, unsigned int _height);


	HWND m_hwnd;// window
	HDC m_hdc;// device context
	HINSTANCE m_hInstance;
	EGLContext m_eglContext;
	EGLDisplay eglDisplay;
	EGLSurface m_eglSurface;
	bool m_isRunning;
};




#endif