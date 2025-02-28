#pragma once

#include <glad/glad.h>

class Window;
struct GLFWwindow;

// Class that represent the device where we run OpenGL
// Implemented as a Singleton pattern, as there can only be one
class DeviceGL
{
public:
    DeviceGL();
    ~DeviceGL();

    // Singleton method to get a reference to the instance. Will crash if there is none
    inline static DeviceGL& GetInstance() { return *m_instance; }

    // Singleton method to get a pointer to the instance
    inline static DeviceGL* GetInstancePointer() { return m_instance; }

    // Check if device is initialized
    inline bool IsReady() const { return m_contextLoaded; }

    // Set the window that OpenGL will use for rendering
    void SetCurrentWindow(Window &window);

    // Set the dimensions of the viewport
    void SetViewport(GLint x, GLint y, GLsizei width, GLsizei height);

    // Poll the events in the window event queue
    void PollEvents();

    // Clear the framebuffer with the specified color
    void Clear(float r, float g, float b, float a);

private:
    // Has a context been loaded? We use the context of the current window
    bool m_contextLoaded;

private:
    // Singleton instance
    static DeviceGL* m_instance;

    // Callback called when the framebuffer changes size
    static void FrameBufferResized(GLFWwindow* window, GLsizei width, GLsizei height);
};
