include_directory = -I ./ -I lib -I lib/glad -I lib/glfw -I lib/glfw/include -I src/state -I src/model -I src/shader -I src/camera -I src/light -I src/util

state = src/state/Game.cpp src/state/RunState.cpp
model = src/model/Loader.cpp src/model/Model.cpp src/model/OBJ_Loader.cpp src/model/Skybox.cpp src/model/Terrain.cpp
shader = src/shader/Shader.cpp
camera = src/camera/Camera.cpp src/camera/Flying_Camera.cpp src/camera/Third_Person_Camera.cpp
util = src/util/Matrix.cpp src/util/Vector.cpp
ccfiles =  $(state)  $(model) $(shader) $(camera) $(util)

main: main.cpp $(ccfiles)
	g++ -Wall -g -o cdio main.cpp lib/glad/glad.c lib/stb_image.cpp $(ccfiles) $(include_directory) -lopengl32 -L lib/glfw/lib-mingw-w64 -lglfw3 -lgdi32

clean :
	rm cdio
