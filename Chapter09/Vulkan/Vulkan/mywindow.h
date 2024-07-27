#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QVulkanWindow>

class MyWindow : public QVulkanWindow
{
public:
    MyWindow();

    // QVulkanWindow interface
public:
    QVulkanWindowRenderer *createRenderer();
};

#endif // MYWINDOW_H
