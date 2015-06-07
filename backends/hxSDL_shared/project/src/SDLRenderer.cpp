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

#include "SDLWindow.h"
#include "SDLRenderer.h"
#include "../../graphics/opengl/OpenGLBindings.h"


namespace lime {


	SDLRenderer::SDLRenderer (Window* window) {

		currentWindow = window;
		sdlWindow = ((SDLWindow*)window)->sdlWindow;
		sdlTexture = 0;

		width = 0;
		height = 0;

		int sdlFlags = 0;

		if (window->flags & WINDOW_FLAG_HARDWARE) {

			sdlFlags |= SDL_RENDERER_ACCELERATED;

		} else {

			sdlFlags |= SDL_RENDERER_SOFTWARE;

		}

		if (window->flags & WINDOW_FLAG_VSYNC) sdlFlags |= SDL_RENDERER_PRESENTVSYNC;

		sdlRenderer = SDL_CreateRenderer (sdlWindow, -1, sdlFlags);

		if (!sdlRenderer) {

			printf ("Could not create SDL renderer: %s.\n", SDL_GetError ());

		}

		OpenGLBindings::Init ();

	}


	SDLRenderer::~SDLRenderer () {

		if (sdlRenderer) {

			SDL_DestroyRenderer (sdlRenderer);

		}

	}


	void SDLRenderer::Flip () {

		SDL_RenderPresent (sdlRenderer);

	}


	value SDLRenderer::Lock () {

		int width;
		int height;

		SDL_GetRendererOutputSize (sdlRenderer, &width, &height);

		if ( width != this->width || height != this->height) {

			if( sdlTexture )
				SDL_DestroyTexture( sdlTexture );

			sdlTexture = SDL_CreateTexture (sdlRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);

		}

		value result = alloc_empty_object ();

		void *pixels;
		int pitch;

		if (SDL_LockTexture (sdlTexture, NULL, &pixels, &pitch) == 0) {

			alloc_field (result, val_id ("width"), alloc_int (width));
			alloc_field (result, val_id ("height"), alloc_int (height));
			alloc_field (result, val_id ("pixels"), alloc_float ((intptr_t)pixels));
			alloc_field (result, val_id ("pitch"), alloc_int (pitch));

		}

		return result;

	}


	void SDLRenderer::Unlock () {

		if (sdlTexture) {

			SDL_UnlockTexture (sdlTexture);
			SDL_RenderClear (sdlRenderer);
			SDL_RenderCopy (sdlRenderer, sdlTexture, NULL, NULL);

		}

	}


	Renderer* CreateRenderer (Window* window) {

		return new SDLRenderer (window);

	}


}
