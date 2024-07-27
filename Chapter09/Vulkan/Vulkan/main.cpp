#include "mywindow.h"

#include <QGuiApplication>
#include <vulkan/vulkan.h>
#include <QVulkanInstance>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QVulkanInstance vulkan;
    if(!vulkan.create()) {
        qFatal("Failed to create Vulkan instance: %d", vulkan.errorCode());
    }
    MyWindow window;
    window.resize(1024, 768);
    window.setVulkanInstance(&vulkan);
    window.show();
    return app.exec();
}
