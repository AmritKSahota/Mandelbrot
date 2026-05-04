#include "ComplexPlane.h"

int main()
{
    // Get desktop resolution and divide by 2
    int width = VideoMode::getDesktopMode().width / 2;
    int height = VideoMode::getDesktopMode().height / 2;

    RenderWindow window(VideoMode(width, height), "Mandelbrot Visualizer");
    ComplexPlane cp(width, height);

    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        // Handle font error if necessary
    }

    Text text;
    text.setFont(font);
    text.setCharacterSize(16);
    text.setFillColor(Color::White);
    text.setPosition(10, 10);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed)
            {
                Vector2i mousePos = Mouse::getPosition(window);
                if (event.mouseButton.button == Mouse::Left)
                {
                    cp.zoomIn();
                    cp.setCenter(mousePos);
                }
                else if (event.mouseButton.button == Mouse::Right)
                {
                    cp.zoomOut();
                    cp.setCenter(mousePos);
                }
            }

            if (event.type == Event::MouseMoved)
            {
                cp.setMouseLocation(Mouse::getPosition(window));
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Update
        cp.updateRender();
        cp.loadText(text);

        // Draw
        window.clear();
        window.draw(cp);
        window.draw(text);
        window.display();
    }
    return 0;
}
