#include "ComplexPlane.h"
#include <iostream>

using namespace std;
using namespace sf;

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
    m_pixel_size = { pixelWidth, pixelHeight };
    // Assignment instruction: height / width (cast to float to avoid integer division)
    m_aspectRatio = (float)pixelHeight / pixelWidth;

    m_plane_center = { 0.0f, 0.0f };
    m_plane_size = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
    m_zoomCount = 0;
    m_State = State::CALCULATING;

    m_vArray.setPrimitiveType(Points);
    m_vArray.resize(pixelWidth * pixelHeight);
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(m_vArray);
}

void ComplexPlane::updateRender()
{
    if (m_State == State::CALCULATING)
    {
        for (int i = 0; i < m_pixel_size.y; i++) // rows (y)
        {
            for (int j = 0; j < m_pixel_size.x; j++) // columns (x)
            {
                // Index formula: j is x, i is y
                int index = j + i * m_pixel_size.x;
                m_vArray[index].position = { (float)j, (float)i };

                Vector2f coord = mapPixelToCoords({ j, i });
                size_t iterations = countIterations(coord);

                Uint8 r, g, b;
                iterationsToRGB(iterations, r, g, b);

                m_vArray[index].color = Color(r, g, b);
            }
        }
        m_State = State::DISPLAYING;
    }
}

void ComplexPlane::zoomIn()
{
    m_zoomCount++;
    float sizeX = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
    float sizeY = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
    m_plane_size = { sizeX, sizeY };
    m_State = State::CALCULATING;
}

void ComplexPlane::zoomOut()
{
    m_zoomCount--;
    float sizeX = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
    float sizeY = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
    m_plane_size = { sizeX, sizeY };
    m_State = State::CALCULATING;
}

void ComplexPlane::setCenter(Vector2i mousePixel)
{
    m_plane_center = mapPixelToCoords(mousePixel);
    m_State = State::CALCULATING;
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
    m_mouseLocation = mapPixelToCoords(mousePixel);
}

void ComplexPlane::loadText(Text& text)
{
    stringstream ss;
    ss << "Mandelbrot\n"
        << "Center: (" << m_plane_center.x << ", " << m_plane_center.y << ")\n"
        << "Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")\n"
        << "Left-Click: Zoom In\nRight-Click: Zoom Out";
    text.setString(ss.str());
}

size_t ComplexPlane::countIterations(Vector2f coord)
{
    Vector2f z = { 0,0 };
    for (size_t i = 0; i < MAX_ITER; i++)
    {
        float tempX = z.x * z.x - z.y * z.y + coord.x;
        z.y = 2.0 * z.x * z.y + coord.y;
        z.x = tempX;
        if ((z.x * z.x + z.y * z.y) > 4.0) return i;
    }
    return MAX_ITER;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
    if (count == MAX_ITER)
    {
        r = g = b = 0; // Black for values that stay in the set
    }
    else
    {
        // Assignment strategy: Regions or Grayscale. This is a nice colorful default:
        r = (count * 5) % 256;
        g = (count * 10) % 256;
        b = (count * 20) % 256;
    }
}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
    // Using the formula: ((n - a) / (b - a)) * (d - c) + c
    float x = ((float)(mousePixel.x - 0) / (m_pixel_size.x - 0)) * m_plane_size.x + (m_plane_center.x - m_plane_size.x / 2.0f);
    float y = ((float)(mousePixel.y - m_pixel_size.y) / (0 - m_pixel_size.y)) * m_plane_size.y + (m_plane_center.y - m_plane_size.y / 2.0f);
    return { x, y };
}
