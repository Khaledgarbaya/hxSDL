// Copyright (c) 2015, Khaled Garbaya
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H


#include <SDL.h>
#include <graphics/ImageBuffer.h>
#include <ui/Window.h>


namespace lime {


	class SDLWindow : public Window {

		public:

			SDLWindow (Application* application, int width, int height, int flags, const char* title);
			~SDLWindow ();

			virtual void Close ();
			virtual bool GetEnableTextEvents ();
			virtual int GetHeight ();
			virtual int GetWidth ();
			virtual int GetX ();
			virtual int GetY ();
			virtual void Move (int x, int y);
			virtual void Resize (int width, int height);
			virtual void SetEnableTextEvents (bool enabled);
			virtual bool SetFullscreen (bool fullscreen);
			virtual void SetIcon (ImageBuffer *imageBuffer);
			virtual bool SetMinimized (bool minimized);

			SDL_Window* sdlWindow;

	};


}


#endif
