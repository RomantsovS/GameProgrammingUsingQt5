#include "myrenderer.h"
#include "mywindow.h"

MyWindow::MyWindow()
{

}

QVulkanWindowRenderer *MyWindow::createRenderer()
{
    return new MyRenderer(this);
}
