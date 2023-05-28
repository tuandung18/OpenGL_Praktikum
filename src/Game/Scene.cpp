#include "Scene.h"
#include <AssetManager.h>
#include "cube.h"

Scene::Scene(OpenGLWindow * window) :
	m_window(window)
{
	assert(window != nullptr);
}

Scene::~Scene()
{}

bool Scene::init()
{
	try
	{

        //Load shader
        m_assets.addShaderProgram("shader", AssetManager::createShaderProgram("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl"));
        m_shader = m_assets.getShaderProgram("shader");
        m_shader->use();

		/*
		 * ************
		 * Place your code here!
		 * ************
		 */


        cubeIndSize = sizeof(cubeInd);
        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);

        // setup VBO //
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVert), &cubeVert, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, false, 24, 0);    // 2D position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, 24, (void*)12); // 3D color
        glEnableVertexAttribArray(1);
        // setup IBO //
        glGenBuffers(1, &iboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof (cubeInd), &cubeInd, GL_STATIC_DRAW);

        /*
         * Backface culling:
         * 1. Enable backface culling
         * 2. Draw front face in counterclockwise direction
         * 3. Ignore back face
         */
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

        // Care: Depth test with GL_GREATER ! Or invert z-values (convert LHS into RHS)
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glClearDepth(1.0);
        // Set Background clear color
        T1 = new Transform();
        T1->rotate(glm::vec3(-0.6 , -0.4, 0.4));
        T2 = new Transform();

        BODY = new Transform();
        BODY->scale(glm::vec3(0.3, 0.8, 0.2));

        HEAD = new Transform();
        HEAD->scale(glm::vec3(0.15, 0.15, 0.15));
        //translate to the top
        HEAD->translate(glm::vec3(0, 0.6, 0));

        SHOULDERLEFT = new Transform();
        SHOULDERLEFT->scale(glm::vec3(0.05, 0.25, 0.05));
        //translate to the left
        SHOULDERLEFT->translate(glm::vec3(-0.2, 0.25, 0));

        SHOULDERRIGHT = new Transform();
        SHOULDERRIGHT->scale(glm::vec3(0.05, 0.25, 0.05));
        //translate to the right
        SHOULDERRIGHT->translate(glm::vec3(0.2, 0.25, 0));

        HANDLEFT = new Transform();
        HANDLEFT->scale(glm::vec3(0.05, 0.3, 0.05));
        //translate to the left
        HANDLEFT->translate(glm::vec3(-0.2, -0.1, 0));

        HANDRIGHT = new Transform();
        HANDRIGHT->scale(glm::vec3(0.05, 0.3, 0.05));
        //translate to the right
        HANDRIGHT->translate(glm::vec3(0.2, -0.1, 0));

        LEGLEFT = new Transform();
        LEGLEFT->scale(glm::vec3(0.05, 0.5, 0.008));
        //translate to the left
        LEGLEFT->translate(glm::vec3(-0.1, -0.7, 0));

        LEGRIGHT = new Transform();
        LEGRIGHT->scale(glm::vec3(0.05, 0.5, 0.008));
        //translate to the right
        LEGRIGHT->translate(glm::vec3(0.1, -0.7, 0));

        // View Matrix in Urspung (0,0,0) und schaut in -z Richtung
        viewMatrix = glm::lookAt(glm::vec3(0, 0, -2), // Camera is at (0,0,-1), in World Space
                                 glm::vec3(0, 0, 0), // and looks at the origin (Because obj is at (0,0,0))
                                 glm::vec3(0, 1, 0)); // Head is up (set to 0,-1,0 to look upside-down)

        // Projection Matrix
        projectionMatrix = glm::perspective(45.0f, // Field of View 45 degrees
                                                      4.0f / 3.0f, // Aspect ratio
                                                      1.0f, // Display range : 0.1 unit <-> 100 units
                                                      100.0f);
        std::cout << "Scene initialization done\n";
        return true;
	}
	catch (std::exception& ex)
	{
	    throw std::logic_error("Scene initialization failed:\n" + std::string(ex.what()) + "\n");
	}
}

void Scene::render(float dt)
{
    static float time = 2;
    static bool rightMove = true;
    time += dt;
    if (time > 3) {
        time = 0;
        rightMove = !rightMove;
    }
    if(rightMove){
        SHOULDERLEFT->rotateAroundPoint(glm::vec3(0, -0.3, 0), glm::vec3(0.2 * dt, 0, 0));
    } else {
        SHOULDERLEFT->rotateAroundPoint(glm::vec3(0, -0.3, 0), glm::vec3(-0.2 * dt, 0, 0));
    }
    if (rightMove) {
        SHOULDERRIGHT->rotateAroundPoint(glm::vec3(0, -0.3, 0), glm::vec3(-0.2 * dt, 0, 0));
    } else {
        SHOULDERRIGHT->rotateAroundPoint(glm::vec3(0, -0.3, 0), glm::vec3(0.2 * dt, 0, 0));
    }
    if (rightMove) {
        HANDLEFT->rotateAroundPoint(glm::vec3(0, -0.3, 0), glm::vec3(0.3 * dt, 0, 0));
    }
    else {
        HANDLEFT->rotateAroundPoint(glm::vec3(0, -0.3, 0), glm::vec3(-0.3 * dt, 0, 0));
    }
    if (rightMove) {
        HANDRIGHT->rotateAroundPoint(glm::vec3(0, -0.3, 0), glm::vec3(-0.3 * dt, 0, 0));
    } else {
        HANDRIGHT->rotateAroundPoint(glm::vec3(0, -0.3, 0), glm::vec3(0.3 * dt, 0, 0));
    }
    if (rightMove) {
        LEGLEFT->rotateAroundPoint(glm::vec3(0, -0.3, 0), glm::vec3(-0.1 * dt, 0, 0));
    } else {
        LEGLEFT->rotateAroundPoint(glm::vec3(0, -0.3, 0), glm::vec3(0.1 * dt, 0, 0));
    }
    if (rightMove) {
        LEGRIGHT->rotateAroundPoint(glm::vec3(0, -0.3, 0), glm::vec3(0.1 * dt, 0, 0));
    } else {
        LEGRIGHT->rotateAroundPoint(glm::vec3(0, -0.3, 0), glm::vec3(-0.1 * dt, 0, 0));
    }


            // Setzt die Hintergrundfarbe für den Farbpuffer.
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Clear background color and depth buffer for depth test
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*
    * ************
    * Place your code here!
    * ************
    */
    // activate VAO //
    glBindVertexArray(vaoID);
    //new view matrix and perspective matrix in shader
    m_shader->setUniform("vm", viewMatrix, false);

    m_shader->setUniform("pm", projectionMatrix, false);


    m_shader->setUniform("mm",
                         T1->getTransformMatrix() * BODY->getTransformMatrix(),
                         false);
    glDrawElements(GL_TRIANGLES,cubeIndSize,GL_UNSIGNED_INT,0);
    m_shader->setUniform("mm",
                         T1->getTransformMatrix() * HEAD->getTransformMatrix(),
                        false);
    glDrawElements(GL_TRIANGLES,cubeIndSize,GL_UNSIGNED_INT,0);

    m_shader->setUniform("mm", T1->getTransformMatrix() * SHOULDERLEFT->getTransformMatrix(), false);
    glDrawElements(GL_TRIANGLES,cubeIndSize,GL_UNSIGNED_INT,0);

    m_shader->setUniform("mm", T1->getTransformMatrix() * SHOULDERRIGHT->getTransformMatrix(), false);
    glDrawElements(GL_TRIANGLES,cubeIndSize,GL_UNSIGNED_INT,0);

    m_shader->setUniform("mm", T1->getTransformMatrix() * HANDLEFT->getTransformMatrix(), false);
    glDrawElements(GL_TRIANGLES,cubeIndSize,GL_UNSIGNED_INT,0);

    m_shader->setUniform("mm", T1->getTransformMatrix() * HANDRIGHT->getTransformMatrix(), false);
    glDrawElements(GL_TRIANGLES,cubeIndSize,GL_UNSIGNED_INT,0);

    m_shader->setUniform("mm", T1->getTransformMatrix() * LEGLEFT->getTransformMatrix() *T2->getTransformMatrix(), false);
    glDrawElements(GL_TRIANGLES,cubeIndSize,GL_UNSIGNED_INT,0);

    m_shader->setUniform("mm", T1->getTransformMatrix() * LEGRIGHT->getTransformMatrix(), false);
    glDrawElements(GL_TRIANGLES,cubeIndSize,GL_UNSIGNED_INT,0);

    // deactivate VAO //
    glBindVertexArray(0);

}

void Scene::update(float dt)
{

}

OpenGLWindow * Scene::getWindow()
{
	return m_window;
}

void Scene::onKey(Key key, Action action, Modifier modifier)
{

}

void Scene::onMouseMove(MousePosition mouseposition)
{

}

void Scene::onMouseButton(MouseButton button, Action action, Modifier modifier)
{

}

void Scene::onMouseScroll(double xscroll, double yscroll)
{

}

void Scene::onFrameBufferResize(int width, int height)
{

}
void Scene::shutdown()
{

}
