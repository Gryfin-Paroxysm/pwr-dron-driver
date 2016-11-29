# https://github.com/Gryfin-Paroxysm/pwr-dron-driver
#------------------------------------------------------------

__START__: 	konfiguracja  \
			program       \
			plugin_fly    \
			plugin_rotate \
			plugin_turn   \
			plugin_pause  \
			plugin_scene
	export LD_LIBRARY_PATH="./dynamic_libs"; ./${NAZWA_PROGRAMU}

UZYWANE_FOLDERY = object         \
				  wtyczki/object \
				  dynamic_libs

konfiguracja:
	mkdir -p ${UZYWANE_FOLDERY}

#------------------------------------------------------------

CPP_FLAGS = -Wall -pedantic -std=c++11 -Iinc ${INC}
LD_FLAGS  = -ldl -lrt -lX11 -lGLEW -lGL -lSOIL -lglfw -lassimp -lreadline -lhistory -lxerces-c

OBJ  =	object/main.o                 \
		object/klasa_glowna.o         \
		object/opengl_window.o        \
		object/opengl_framework.o     \
		object/model_loader.o         \
		object/kamera_loader.o        \
		object/shader_loader.o        \
		object/pamiec_wspoldzielona.o \
		object/instrukcje.o           \
		object/wtyczki.o              \
		object/scena.o                \
		object/xmlparser4scene.o      \
		object/dron.o

INC = -I"./biblioteki/include"

NAZWA_PROGRAMU = dron

program: ${OBJ}
	g++ -o ${NAZWA_PROGRAMU} ${OBJ} ${LD_FLAGS} ${INC} 

program_debug: ${OBJ}
	g++ -g -o ${NAZWA_PROGRAMU} ${OBJ} ${LD_FLAGS} ${INC}

#------------------------------------------------------------

object/main.o: src/main.cpp             \
			inc/pamiec_wspoldzielona.hh \
			inc/opengl_window.hh        \
			inc/klasa_glowna.hh
	g++ -c ${CPP_FLAGS} -o object/main.o src/main.cpp

object/klasa_glowna.o: src/klasa_glowna.cpp inc/klasa_glowna.hh \
					inc/instrukcje.hh                           \
					inc/wtyczki.hh                              \
					inc/dron.hh
	g++ -c ${CPP_FLAGS} -o object/klasa_glowna.o src/klasa_glowna.cpp

object/opengl_window.o: src/opengl_window.cpp inc/opengl_window.hh \
					inc/opengl_framework.hh                        \
					inc/model_loader.hh                            \
					inc/shader_loader.hh                           \
					inc/zasoby.hh
	g++ -c ${CPP_FLAGS} -o object/opengl_window.o src/opengl_window.cpp

object/opengl_framework.o: src/opengl_framework.cpp inc/opengl_framework.hh \
						inc/kamera_loader.hh
	g++ -c ${CPP_FLAGS} -o object/opengl_framework.o src/opengl_framework.cpp

object/model_loader.o: src/model_loader.cpp inc/model_loader.hh \
					inc/shader_loader.hh                        \
					inc/kamera_loader.hh
	g++ -c ${CPP_FLAGS} -o object/model_loader.o src/model_loader.cpp

object/kamera_loader.o: src/kamera_loader.cpp inc/kamera_loader.hh
	g++ -c ${CPP_FLAGS} -o object/kamera_loader.o src/kamera_loader.cpp

object/shader_loader.o: src/shader_loader.cpp inc/shader_loader.hh
	g++ -c ${CPP_FLAGS} -o object/shader_loader.o src/shader_loader.cpp

object/pamiec_wspoldzielona.o: src/pamiec_wspoldzielona.cpp inc/pamiec_wspoldzielona.hh
	g++ -c ${CPP_FLAGS} -o object/pamiec_wspoldzielona.o src/pamiec_wspoldzielona.cpp

object/instrukcje.o: src/instrukcje.cpp inc/instrukcje.hh
	g++ -c ${CPP_FLAGS} -o object/instrukcje.o src/instrukcje.cpp

object/wtyczki.o: src/wtyczki.cpp inc/wtyczki.hh \
			  inc/wtyczka_loader.hh
	g++ -c ${CPP_FLAGS} -o object/wtyczki.o src/wtyczki.cpp

object/scena.o: src/scena.cpp inc/scena.hh \
			  inc/prostopadloscian.hh      \
			  inc/punkt.hh
	g++ -c ${CPP_FLAGS} -fPIC -o object/scena.o src/scena.cpp

object/xmlparser4scene.o: src/xmlparser4scene.cpp inc/xmlparser4scene.hh
	g++ -c ${CPP_FLAGS} -fPIC -o object/xmlparser4scene.o src/xmlparser4scene.cpp

object/dron.o: src/dron.cpp inc/dron.hh
	g++ -c ${CPP_FLAGS} -fPIC -o object/dron.o src/dron.cpp

#------------------------------------------------------------

CPP_DYNAMIC_FLAGS = -Wall -pedantic -std=c++11 -Iinc -I"./wtyczki/inc" -fPIC
LD_DYNAMIC_FLAGS = -Wall -shared

plugin_fly: plugin_fly.o
	g++ ${LD_DYNAMIC_FLAGS} -o dynamic_libs/Fly.so wtyczki/object/plugin_fly.o object/dron.o

plugin_fly.o: wtyczki/src/plugin_fly.cpp wtyczki/inc/plugin_fly.hh inc/plugin.hh inc/pamiec_wspoldzielona.hh
	g++ -c ${CPP_DYNAMIC_FLAGS} \
		-o wtyczki/object/plugin_fly.o wtyczki/src/plugin_fly.cpp

plugin_rotate: plugin_rotate.o
	g++ ${LD_DYNAMIC_FLAGS} -o dynamic_libs/Rotate.so wtyczki/object/plugin_rotate.o object/dron.o

plugin_rotate.o: wtyczki/src/plugin_rotate.cpp wtyczki/inc/plugin_rotate.hh inc/plugin.hh
	g++ -c ${CPP_DYNAMIC_FLAGS} \
		-o wtyczki/object/plugin_rotate.o wtyczki/src/plugin_rotate.cpp

plugin_turn: plugin_turn.o
	g++ ${LD_DYNAMIC_FLAGS} -o dynamic_libs/Turn.so wtyczki/object/plugin_turn.o object/dron.o

plugin_turn.o: wtyczki/src/plugin_turn.cpp wtyczki/inc/plugin_turn.hh inc/plugin.hh
	g++ -c ${CPP_DYNAMIC_FLAGS} \
		-o wtyczki/object/plugin_turn.o wtyczki/src/plugin_turn.cpp

plugin_pause: plugin_pause.o
	g++ ${LD_DYNAMIC_FLAGS} -o dynamic_libs/Pause.so wtyczki/object/plugin_pause.o object/dron.o

plugin_pause.o: wtyczki/src/plugin_pause.cpp wtyczki/inc/plugin_pause.hh inc/plugin.hh
	g++ -c ${CPP_DYNAMIC_FLAGS} \
		-o wtyczki/object/plugin_pause.o wtyczki/src/plugin_pause.cpp

plugin_scene: plugin_scene.o
	g++ ${LD_DYNAMIC_FLAGS} -o dynamic_libs/Scene.so wtyczki/object/plugin_scene.o object/dron.o object/xmlparser4scene.o object/scena.o

plugin_scene.o: wtyczki/src/plugin_scene.cpp wtyczki/inc/plugin_scene.hh inc/plugin.hh
	g++ -c ${CPP_DYNAMIC_FLAGS} \
		-o wtyczki/object/plugin_scene.o wtyczki/src/plugin_scene.cpp

#------------------------------------------------------------

clean:
	rm -rf core* ${UZYWANE_FOLDERY} ${NAZWA_PROGRAMU}

debug_wewnetrzny:
	make clean    \
	konfiguracja  \
	program_debug \
	plugin_fly    \
	plugin_rotate \
	plugin_turn   \
	plugin_pause  \
	plugin_scene
	export LD_LIBRARY_PATH="./dynamic_libs"; gdb ./${NAZWA_PROGRAMU}

valgrind_wewnetrzny:
	export LD_LIBRARY_PATH="./dynamic_libs"; \
	valgrind -v                              \
			 --leak-check=full               \
			 --show-leak-kinds=all           \
			 --track-origins=yes             \
	./${NAZWA_PROGRAMU}

doxygen_:
	cd dox;	make

doxygen_clean:
	cd dox; make clean

clean_all:
	make clean; make doxygen_clean

#------------------------------------------------------------
