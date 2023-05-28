#pragma once

#include "OpenGLWindow.h"
#include <ShaderProgram.h>
#include <memory>
#include <AssetManager.h>
#include "../SceneElements/Transform.h"

class Scene
{
public:
	Scene(OpenGLWindow* window);
	~Scene();

	bool init();
	void shutdown();
	void render(float dt);
	void update(float dt);
	OpenGLWindow* getWindow();

	void onKey(Key key, Action action, Modifier modifier);
	void onMouseMove(MousePosition mouseposition);
	void onMouseButton(MouseButton button, Action action, Modifier modifier);
	void onMouseScroll(double xscroll, double yscroll);
	void onFrameBufferResize(int width, int height);





private:
	OpenGLWindow* m_window;
	AssetManager m_assets;
    ShaderProgram* m_shader;
    int cubeIndSize;
    GLuint vaoID, vboID,iboID;
    Transform* T1, *T2, *T3;
    Transform* BODY, *HEAD, *SHOULDERLEFT, *SHOULDERRIGHT, *HANDLEFT, *HANDRIGHT, *LEGLEFT, *LEGRIGHT;
    //view matrix
    glm::mat4 viewMatrix;
    //projection matrix
    glm::mat4 projectionMatrix;

};

