cc = g++ -std=c++17 -Wall -g
include_directory = -I ./ -I lib -I lib/glad -I lib/glfw -I lib/glfw/include -I src/state -I src/model -I src/shader -I src/camera -I src/light -I src/util
libs = -lopengl32 -L lib/glfw/lib-mingw-w64 -lglfw3 -lgdi32

state  = src/state/Game.cc src/state/Game_State.cc
model  = src/model/Model.cc src/model/Skybox.cc src/model/Terrain.cc
shader = src/shader/Shader.cc
camera = src/camera/Camera.cc src/camera/Flying_Camera.cc src/camera/Third_Person_Camera.cc
light  = src/light/Light.cc
util   = src/util/Matrix.cc src/util/Vector.cc
ccfiles =  $(state)  $(model) $(shader) $(camera) $(light) $(util)

main: main.cc $(ccfiles)
	$(cc) -o tsbk main.cc lib/glad/glad.c lib/stb_image.cc $(ccfiles) $(include_directory) $(libs)

clean :
	del tsbk.exe
	del *.o