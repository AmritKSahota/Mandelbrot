#ifndef COMPLEX_PLANE_H
#define COMPLEX_PLANE_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <sstream>

using namespace sf;

//inheriting from sf::Drawable -- AS

//constants
cnst unsigned int MAX_INTER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_Height = 4.0;
const float BASE_ZOOM = 0.5;

enum class State {CALCULATING< DISPLAYING };

class ComplexPlane : public Drawable
{
public: 
  ComplexPlane(int pixelWidth, int PixelHeight);
  void updateRender();
  void zoomIn();
  void zoomOut();
  void setCenter (mousePixel: Vector2i);
  void setMouseLocation (mousePixel: Vector2i);
  void loadText (text: Text& );
  void updateRender();

//because we're using sf::Drawable this is mandatory
virtual void draw (RenderTarget& target, RenderStates states) const;

private:
  VertexArray m_vArray;
  State m_State;
  Vector2f m_mouseLocation;
  Vector2f m_plane_center;
  Vector2f m_plane_size;
  Vector2i m_pixel_size;
  int m_zoomCount;
  float m_aspectRatio;
// these I think go here, but the image was a little confusing tbh -- AS
size_t countIteration(Vector2f coord);
void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);
Vector2f mapPixeltoCoords (Vector2i mousePixel)

};

#endif
