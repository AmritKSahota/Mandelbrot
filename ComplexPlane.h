#define COMPLEX_PLANE_H
#endif
#ifndef COMPLEX_PLANE_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <sstream>
// Global constants
ComplexPlane(int pixelWidth, int pixelHeight);
State m_State;
Vector2f m_mouseLocation;
Vector2f m_plane_center;
Vector2f m_plane_size;
Vector2f mapPixelToCoords(Vector2i mousePixel);
Vector2i m_pixel_size;
VertexArray m_vArray;
class ComplexPlane : public Drawable
const float BASE_HEIGHT = 4.0;
const float BASE_WIDTH = 4.0;
const float BASE_ZOOM = 0.5;
const unsigned int MAX_ITER = 64;
enum class State { CALCULATING, DISPLAYING };
float m_aspectRatio;
int m_zoomCount;
private:
public:
size_t countIterations(Vector2f coord);
using namespace sf;
virtual void draw(RenderTarget& target, RenderStates states) const;
void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);
void loadText(Text& text);
void setCenter(Vector2i mousePixel);
void setMouseLocation(Vector2i mousePixel);
void updateRender();
void zoomIn();
void zoomOut();
{
};
