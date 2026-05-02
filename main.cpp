#include "ComplexPlane.h"

int main ()
{
  int width = VideoMode::getDesktopMode().width/2;
  int height = VideoMode :: getDesktopMode().height/2;
  //divided it by 2 to make it smaller, set up desktop res. it should run now -- AS
  //you can change it at the end if you want but please change it back if so  : ) -- AS

  RenderWindow window(VideoMode(width, height), "Mandelbrot Visualz");
  ComplexPlane cp(width, height);

  //font stuff unforch goes here ; come back to do that once you upload the ttf

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
