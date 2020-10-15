cc = g++ -std=c++17 -Wall -g -D GLFW_INCLUDE_NONE 
include_directory = -I ./ -I lib -I lib/glad -I lib/glfw -I lib/glfw/include -I src/state -I src/gui -I src/tree -I src/model -I src/shader -I src/camera -I src/light -I src/util
libs = -lopengl32 -L lib/glfw/lib-mingw-w64 -lglfw3 -lgdi32

camera_o = obj/Camera.o obj/Flying_Camera.o obj/Third_Person_Camera.o
gui_o = obj/Font.o obj/Text.o obj/Word.o
model_o = obj/Model.o obj/Skybox.o obj/Terrain.o obj/Tree.o
state_o = obj/Game.o obj/Game_State.o obj/Menu_State.o
ofiles = $(camera_o) $(gui_o) $(model_o) $(state_o) obj/Shader.o obj/Light.o obj/Matrix.o obj/Vector.o obj/glad.o obj/stb_image.o

main: main.cc $(ofiles)
	$(cc) -o tsbk main.cc $(ofiles) $(include_directory) $(libs)

# Camera

obj/Camera.o: src/camera/Camera.cc src/camera/Camera.h
	$(cc) -c -o $@ $< $(include_directory) $(libs)

obj/Flying_Camera.o: src/camera/Flying_Camera.cc src/camera/Flying_Camera.h
	$(cc) -c -o $@ $< $(include_directory) $(libs)

obj/Third_Person_Camera.o: src/camera/Third_Person_Camera.cc src/camera/Third_Person_Camera.h
	$(cc) -c -o $@ $< $(include_directory) $(libs)

# Gui

obj/Font.o: src/gui/Font.cc src/gui/Font.h
	$(cc) -c -o $@ $< $(include_directory) $(libs)

obj/Text.o: src/gui/Text.cc src/gui/Text.h
	$(cc) -c -o $@ $< $(include_directory) $(libs)

obj/Word.o: src/gui/Word.cc src/gui/Word.h
	$(cc) -c -o $@ $< $(include_directory) $(libs)

# Light

obj/Light.o: src/light/Light.cc src/light/Light.h
	$(cc) -c -o $@ $< $(include_directory) $(libs)

# Model

obj/Model.o: src/model/Model.cc src/model/Model.h
	$(cc) -c -o $@ $< $(include_directory) $(libs)

obj/Skybox.o: src/model/Skybox.cc src/model/Skybox.h
	$(cc) -c -o $@ $< $(include_directory) $(libs)

obj/Terrain.o: src/model/Terrain.cc src/model/Terrain.h
	$(cc) -c -o $@ $< $(include_directory) $(libs)

# Shader

obj/Shader.o: src/shader/Shader.cc src/shader/Shader.h
	$(cc) -c -o $@ $< $(include_directory) $(libs)

# State

obj/Game.o: src/state/Game.cc src/state/Game.h
	$(cc) -c -o $@ $< $(include_directory) $(libs)

obj/Game_State.o: src/state/Game_State.cc src/state/Game_State.h
	$(cc) -c -o $@ $< $(include_directory) $(libs)

obj/Menu_State.o: src/state/Menu_State.cc src/state/Menu_State.h
	$(cc) -c -o $@ $< $(include_directory) $(libs)

# Tree

obj/Tree.o: src/tree/Tree.cc src/tree/Tree.h
	$(cc) -c -o $@ $< $(include_directory) $(libs)

# Util

obj/Matrix.o: src/util/Matrix.cc src/util/Matrix.h
	$(cc) -c -o $@ $< $(include_directory) $(libs)

obj/Vector.o: src/util/Vector.cc src/util/Vector.h
	$(cc) -c -o $@ $< $(include_directory) $(libs)

# Libs

obj/glad.o: lib/glad/glad.c lib/glad/glad.h
	$(cc) -c -o $@ $< $(include_directory) $(libs)

obj/stb_image.o: lib/stb_image.cc lib/stb_image.h
	$(cc) -c -o $@ $< $(include_directory) $(libs)

# Clean

clean :
	del obj\*.o
	del tsbk.exe