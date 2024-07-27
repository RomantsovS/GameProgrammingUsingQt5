#include <QVulkanWindow>

class MyRenderer : public QVulkanWindowRenderer
{
public:
    MyRenderer(QVulkanWindow *w);
    void initResources() override;
    void startNextFrame() override;

protected:
    QVulkanWindow *m_window;
    QVulkanDeviceFunctions *m_devFuncs;
    float m_hue = 0;

};
