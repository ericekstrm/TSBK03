cc = g++ -std=c++17 -Wall -g
include_directory = -I ./ -I lib -I lib/glad -I lib/glfw -I lib/glfw/include -I src/state -I src/model -I src/shader -I src/camera -I src/light -I src/util
libs = -lopengl32 -L lib/glfw/lib-mingw-w64 -lglfw3 -lgdi32

main: main.cc obj/*.o
	$(cc) -o tsbk main.cc obj/*.o $(include_directory) $(libs)

# State

obj/Game.o: src/state/Game.cc src/state/Game.h
	$(cc) -c -o $@ $< $(include_directory) $(libs)

obj/Game_State.o: src/state/Game_State.cc src/state/Game_State.h
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

# Camera

obj/Camera.o: src/camera/Camera.cc src/camera/Camera.h
	$(cc) -c -o $@ $< $(include_directory) $(libs)

obj/Flying_Camera.o: src/camera/Flying_Camera.cc src/camera/Flying_Camera.h
	$(cc) -c -o $@ $< $(include_directory) $(libs)

obj/Third_Person_Camera.o: src/camera/Third_Person_Camera.cc src/camera/Third_Person_Camera.h
	$(cc) -c -o $@ $< $(include_directory) $(libs)

# Light

obj/Light.o: src/light/Light.cc src/light/Light.h
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