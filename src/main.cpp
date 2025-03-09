#include "../src/Core/Window.h"
#include <iostream>

int main(void)
{
    std::unique_ptr<JKYJ::Window> window = JKYJ::Window::Create();
    window->SetEventCallback([](JKYJ::Event& e)
	{
		std::cout << e.ToString();
	});
	window->OnUpdate();
}