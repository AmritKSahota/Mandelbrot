#include "ComplexPlane.h"
using namespace std;
using namespace sf;
ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
  m_pixel_size = {pixelWidth, pixelHeight};
  m_aspectRatio = (float)pixelHeight / pixelWidth;
  m_plane_center = {0,0};
  //the curly braces are nice
  m_plane_size = {BASE_WIDTH, BASE_HEIGHT * m_aspectRatio};
  m_zoomCount = 0;
  m_state = State::CALCULATING;
  //parameter values

  //initialize array
  m_vArray.setPrimitiveType(Points);
  m_vArray.resize(pixelWidth * pixelHeight);
}
void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
  target.draw(m_vArray);
}

void complexPlane::updateRender()
{
  if (m_State == State::CALCULATING)
  {
    for (int i = 0; i < m_pixel_size.y; i++)//rows
      {
        for(int j = 0; j < m_pixel_size.x; j++)//columns
          {
            vArray[j + i * pixelWidth].position = { (float)j,(float)i };
            //shouldn't this part match above? or did I do the above wrong? -- AS
          Vector2f coord = mapPixelToCoords({j,i});
          size_t iterations = countIterations(coord);

            Uint8 r,g,b;
            iterationsToRGB (iterations, r, g, b);

            vArray[j + i * pixelWidth].color = { r,g,b };
          }
      }
    m_Stat = State::DISPLAYING;
    //array
  }
}

void ComplexPlane::zoomIn()
{
  m_zoomCount++;
  float sizex = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
  float sizey = BASE_HEIGHT * m_aspectRatio *  pow(BASE_ZOOM, m_zoomCount);
  m_plane_size = {sizex,sizey};
  m_State = State::CALCULATING;
}
void ComplexPlane::zoomOut()
{
  m_zoomCount--;
  float sizex = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
  float sizey = BASE_HEIGHT * m_aspectRatio *  pow(BASE_ZOOM, m_zoomCount);
  m_plane_size = {sizex,sizey};
  m_State = State::CALCULATING; 
}
void ComplexPlane::setCenter(Vector2i mousePixel)
{
 m_plane_center = mapPixelToCoords(mousePixel);
  m_State = State::CALCULATING;
}
void ComplexPlane::setMouseLocation(Vector2i mousPixel)
{
  m_mouseLocation = mapPixelToCoords(mousePixel);
}
void ComplexPlane::loadText(Text& text)
{
 stringstream ss;
    ss << "Mandelbrot \n" << "Center: (" << m_plane_center.x << ", " << m_plane_center.y << ")\n" << "Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")\n" << "Left-Click: Zoom In\nRight-Click: Zoom Out";
    text.setString(ss.str());
  
}
//this should show up in the corner -- AS
size_t ComplexPlane::countIterations(Vector2f coord)
{
  //mandelbrot algo - refer to page if needed -- AS
Vector2f z = coord;
  for (size_t i = 0; i < MAX_INTER; i++)
    {
    float x = z.x * z.x - z.y * z.y + coord.x;
        float y = 2.0 * z.x * z.y + coord.y;
        z.x = x;
        z.y = y;
        if ((z.x * z.x + z.y * z.y) > 4.0) return i;
    }
  return MAX_INTER;
}
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
 if() { r = g = b = 0; }
  else 
 {
    r = (count * 7) % 256;
        g = (count * 3) % 256;
        b = (count * 11) % 256;
  }
  //you can change the color if you'd like, I left it grayscale like the page suggests -- AS
}
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
float x = ((mousePixel.x - 0.0f) / (m_pixel_size.x - 0.0f)) * m_plane_size.x + (m_plane_center.x - m_plane_size.x / 2.0f);
    float y = ((mousePixel.y - (float)m_pixel_size.y) / (0.0f - m_pixel_size.y)) * m_plane_size.y + (m_plane_center.y - m_plane_size.y / 2.0f);
    return {x, y};
}
