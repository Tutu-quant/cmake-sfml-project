#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>

void drawLine(sf::RenderWindow &window, const sf::Vector2f &start, const sf::Vector2f &end)
{
    sf::VertexArray line(sf::PrimitiveType::Lines);
    line.append(sf::Vertex{start, sf::Color::Red});
    line.append(sf::Vertex{end, sf::Color::Red});
    window.draw(line);
}
void drawAxes(sf::RenderWindow &window)
{
    const float width = 800.f;
    const float height = 600.f;

    // Find the center of the window
    const float centerX = width / 2.f;
    const float centerY = height / 2.f;

    sf::VertexArray axes(sf::PrimitiveType::Lines);

    // X axis - horizontal line (green)
    axes.append(sf::Vertex{
        sf::Vector2f(0.f, centerY),
        sf::Color::Green});

    axes.append(sf::Vertex{
        sf::Vector2f(width, centerY),
        sf::Color::Green});

    // Y axis - vertical line (blue)
    axes.append(sf::Vertex{
        sf::Vector2f(centerX, 0.f),
        sf::Color::Blue});

    axes.append(sf::Vertex{
        sf::Vector2f(centerX, height),
        sf::Color::Blue});

    window.draw(axes);
}

bool isDrawing = false;
bool hasLine = false;

sf::Vector2f startPoint;
sf::Vector2f endPoint;
void drawGrid(sf::RenderWindow &window)
{
    const int width = 800;
    const int height = 600;
    const int spacing = 25;

    sf::VertexArray grid(sf::PrimitiveType::Lines);

    // Draw vertical lines
    for (int x = 0; x <= width; x += spacing)
    {
        grid.append(sf::Vertex{
            sf::Vector2f(static_cast<float>(x), 0.f),
            sf::Color(55, 55, 55)});

        grid.append(sf::Vertex{
            sf::Vector2f(static_cast<float>(x), static_cast<float>(height)),
            sf::Color(55, 55, 55)});
    }

    // Draw horizontal lines
    for (int y = 0; y <= height; y += spacing)
    {
        grid.append(sf::Vertex{
            sf::Vector2f(0.f, static_cast<float>(y)),
            sf::Color(55, 55, 55)});

        grid.append(sf::Vertex{
            sf::Vector2f(static_cast<float>(width), static_cast<float>(y)),
            sf::Color(55, 55, 55)});
    }

    // Draw the entire grid once
    window.draw(grid);
}

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "MiniCAD - Computer Graphics");

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto *mouse =
                    event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouse->button == sf::Mouse::Button::Left)
                {
                    if (!isDrawing)
                    {
                        startPoint = sf::Vector2f(
                            static_cast<float>(mouse->position.x),
                            static_cast<float>(mouse->position.y));

                        isDrawing = true;
                        hasLine = false;
                    }
                    else
                    {
                        endPoint = sf::Vector2f(
                            static_cast<float>(mouse->position.x),
                            static_cast<float>(mouse->position.y));

                        isDrawing = false;
                        hasLine = true;
                    }
                }
            }
            if (const auto *mouse =
                    event->getIf<sf::Event::MouseMoved>())
            {
                std::string title = "MiniCad - Mouse:" +
                                    std::to_string(mouse->position.x) + "," +
                                    std::to_string(mouse->position.y);
                window.setTitle(title);
            }
        }

        window.clear(sf::Color(30, 30, 30));
        drawGrid(window);
        drawAxes(window);
        if (hasLine)
        {
            drawLine(window, startPoint, endPoint);
        }
        window.display();
    }

    return 0;
}
