incSDL2=-ISDL2\SDL2-2.0.14\x86_64-w64-mingw32\include\SDL2
incSDL2_image=-ISDL2\SDL2_image-2.0.5\x86_64-w64-mingw32\include\SDL2
incSDL2_mixer=-ISDL2\SDL2_mixer-2.0.4\x86_64-w64-mingw32\include\SDL2
incSDL2_ttf=-ISDL2\SDL2_ttf-2.0.15\x86_64-w64-mingw32\include\SDL2

libSDL2W32=-LSDL2\SDL2-2.0.14\i686-w64-mingw32\lib
libSDL2_imageW32=-LSDL2\SDL2_image-2.0.5\i686-w64-mingw32\lib
libSDL2_mixerW32=-LSDL2\SDL2_mixer-2.0.4\i686-w64-mingw32\lib
libSDL2_ttfW32=-LSDL2\SDL2_ttf-2.0.15\i686-w64-mingw32\lib


libSDL2W64=-LSDL2\SDL2-2.0.14\x86_64-w64-mingw32\lib
libSDL2_imageW64=-LSDL2\SDL2_image-2.0.5\x86_64-w64-mingw32\lib
libSDL2_mixerW64=-LSDL2\SDL2_mixer-2.0.4\x86_64-w64-mingw32\lib
libSDL2_ttfW64=-LSDL2\SDL2_ttf-2.0.15\x86_64-w64-mingw32\lib

libW=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -s -mwindows

Winx32: main.cpp Game_Data.cpp Input_Data.cpp SDL_lib.cpp SDL_ImageObject.cpp SDL_TextObject.cpp
	g++ -m32 -o Outfile\Winx32\Tetris $? $(incSDL2) $(incSDL2_image) $(incSDL2_ttf) $(incSDL2_mixer) $(libSDL2W32) $(libSDL2_imageW32) $(libSDL2_mixerW32) $(libSDL2_ttfW32) $(libW)

Winx64: main.cpp Game_Data.cpp Input_Data.cpp SDL_lib.cpp SDL_ImageObject.cpp SDL_TextObject.cpp
	g++ -m64 -o Outfile\Winx64\Tetris $? $(incSDL2) $(incSDL2_image) $(incSDL2_ttf) $(incSDL2_mixer) $(libSDL2W64) $(libSDL2_imageW64) $(libSDL2_mixerW64) $(libSDL2_ttfW64) $(libW)

Linux: main.cpp Game_Data.cpp Input_Data.cpp SDL_lib.cpp SDL_ImageObject.cpp SDL_TextObject.cpp
	g++ -o Outfile/Linux/Tetris $? -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

