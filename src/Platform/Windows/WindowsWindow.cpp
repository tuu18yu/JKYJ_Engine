#include "WindowsWindow.h"
#include "../../Events/KeyEvent.h"
#include "../../Events/MouseEvent.h"

namespace JKYJ {

	WindowsWindow::WindowsWindow(const WindowProps& props) { Init(props); }
	WindowsWindow::~WindowsWindow() { Shutdown(); }

	void WindowsWindow::SetVSync(bool enabled)
	{
		glfwSwapInterval(enabled ? 1 : 0);
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const { return m_Data.VSync; }

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
	
		if (!glfwInit())
		{
			std::cerr << "Failed to initialize GLFW" << std::endl;
			return;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		if (!m_Window)
		{
			std::cerr << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data); // stores m_data

		SetVSync(true);

		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			/* Problem: glewInit failed, something is seriously wrong. */
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		}

		// Set input callbacks
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); // retrieves stored m_data

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(true);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
		std::cout << "Creating window..." << std::endl;
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();

	}

	void WindowsWindow::OnUpdate()
	{
		while (!glfwWindowShouldClose(m_Window))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			/* Swap front and back buffers */
			glfwSwapBuffers(m_Window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
}