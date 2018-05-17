#include <vart/cone.h>
#include <vart/scene.h>
#include <vart/contrib/mousecontrol.h>
#include <vart/contrib/viewerglutogl.h>

using namespace std;

// Define the click handler
class ClickHandlerClass : public VART::MouseControl::ClickHandler
{
public:
    ClickHandlerClass() {
    }
    virtual ~ClickHandlerClass() {};
    virtual void OnClick() {
        if (mouseCtrlPtr->LastClickIsDown()) {
        }
    }
};

int main (int argc, char* argv[]){

    VART::ViewerGlutOGL::Init(&argc, argv);
    static VART::Scene scene;
    static VART::ViewerGlutOGL viewer;
    VART::Camera camera(VART::Point4D(0,0,6), VART::Point4D::ORIGIN(), VART::Point4D::Y());


    VART::Cone piramide;




    return 0;
}