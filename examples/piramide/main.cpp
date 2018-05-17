// main.cpp - keyboard handling example

// V-ART example: Keyboard handling

// This application controls the position of a sphere using keyboard (the four arrow keys).
// It shows a portable way to handle multiple keys pressed at the same time.

// Note: ViewerGlutOGL is part of "V-ART contrib".

// Changelog
// Oct 17, 2012 - Bruno de Oliveira Schneider
// - Application created.

#include <vart/scene.h>
#include <vart/light.h>
#include <vart/point4d.h>
#include <vart/contrib/viewerglutogl.h>
#include <vart/meshobject.h>


#include <iostream>

using namespace std;
using namespace VART;

const unsigned int MAX_KEYS = 10; // max number of keys to keep control
enum Key { UP, DOWN, RIGHT, LEFT };
bool keyPressed[MAX_KEYS];

// Define the keyboard handler
class KeyboardHandler : public ViewerGlutOGL::KbHandler
{
    public:
        KeyboardHandler() {
            for (unsigned int i = 0; i < MAX_KEYS; ++i)
                keyPressed[i] = false;
        }
        virtual void OnKeyDown(int key) {
            switch (key) {
                case KEY_LEFT:
                    keyPressed[LEFT] = true;
                    break;
                case KEY_RIGHT:
                    keyPressed[RIGHT] = true;
                    break;
                case KEY_UP:
                    keyPressed[UP] = true;
                    break;
                case KEY_DOWN:
                    keyPressed[DOWN] = true;
                    break;
            }
        }
        virtual void OnKeyUp(int key) {
            switch (key) {
                case KEY_LEFT:
                    keyPressed[LEFT] = false;
                    break;
                case KEY_RIGHT:
                    keyPressed[RIGHT] = false;
                    break;
                case KEY_UP:
                    keyPressed[UP] = false;
                    break;
                case KEY_DOWN:
                    keyPressed[DOWN] = false;
                    break;
            }
        }
    private:
};

class MyIHClass : public VART::ViewerGlutOGL::IdleHandler
{
    public:
        MyIHClass() : translPtr(NULL) {
        }
        virtual ~MyIHClass() {}
        virtual void OnIdle() {
            bool someKeyIsPressed = false;
            if (keyPressed[UP]) {
                translPtr->GetTranslation(&spherePos);
                if (spherePos.GetY() < 3)
                    translPtr->MakeTranslation(spherePos + Point4D(0, 0.01, 0, 0));
                someKeyIsPressed = true;
            }
            if (keyPressed[DOWN]) {
                translPtr->GetTranslation(&spherePos);
                if (spherePos.GetY() > -3)
                    translPtr->MakeTranslation(spherePos + Point4D(0, -0.01, 0, 0));
                someKeyIsPressed = true;
            }
            if (keyPressed[LEFT]) {
                translPtr->GetTranslation(&spherePos);
                if (spherePos.GetX() > -4)
                    translPtr->MakeTranslation(spherePos + Point4D(-0.01, 0, 0, 0));
                someKeyIsPressed = true;
            }
            if (keyPressed[RIGHT]) {
                translPtr->GetTranslation(&spherePos);
                if (spherePos.GetX() < 4)
                    translPtr->MakeTranslation(spherePos + Point4D(0.01, 0, 0, 0));
                someKeyIsPressed = true;
            }
            if (someKeyIsPressed)
                viewerPtr->PostRedisplay();
        }
        Transform* translPtr;
    protected:
    private:
        Point4D spherePos;
};



// The application itself:
int main(int argc, char* argv[])
{
    ViewerGlutOGL::Init(&argc, argv); // Initialize GLUT
    static Scene scene; // create a scene
    static ViewerGlutOGL viewer; // create a viewer (application window)
    viewer.SetSize(854,480);
    // create a camera (scene observer)
    Camera camera(Point4D(0,0,5,1), Point4D(0,0,0,1), Point4D(0,1,0,0));

    VART::MeshObject piramide;
    
						  // Vértices
						 // 0      1      2       3      4           
    piramide.SetVertices("0 0 2, 2 0 0, 0 2 0, -2 0 0, 0 -2 0");
    
    // Faces
    piramide.AddFace("0 1 2");
    piramide.AddFace("0 2 3");
    piramide.AddFace("0 3 4");
    piramide.AddFace("0 4 1");
    piramide.AddFace("4 3 2 1"); //base
    
    piramide.SetMaterial(VART::Material::PLASTIC_BLUE());
	//scene.AddObject(&piramide);

    // Build up the scene
    Transform piramideTrans; // controls the position of the sphere
    piramideTrans.MakeIdentity();
    piramideTrans.AddChild(piramide);
    scene.AddObject(&piramideTrans);
    scene.AddLight(Light::BRIGHT_AMBIENT());
    scene.AddCamera(&camera);

    // Set up the viewer
    viewer.SetTitle("Lista de exercicio - Piramide");
    viewer.SetScene(scene); // attach the scene
    
    KeyboardHandler kbh; // create a keyboard handler
    viewer.SetKbHandler(&kbh); // attach the keyboard handler
    MyIHClass idh;
    idh.translPtr = &piramideTrans;
    viewer.SetIdleHandler(&idh);

    // Run application
    scene.DrawLightsOGL(); // Set OpenGL's lights' state
    ViewerGlutOGL::MainLoop(); // Enter main loop (event loop)
    return 0;
}
