#include <SFML/Graphics.hpp>
#include <optional>

void drawGrid(sf::RenderWindow& window)
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
            sf::Color(55, 55, 55)
        });

        grid.append(sf::Vertex{
            sf::Vector2f(static_cast<float>(x), static_cast<float>(height)),
            sf::Color(55, 55, 55)
        });
    }

    // Draw horizontal lines
    for (int y = 0; y <= height; y += spacing)
    {
        grid.append(sf::Vertex{
            sf::Vector2f(0.f, static_cast<float>(y)),
            sf::Color(55, 55, 55)
        });

        grid.append(sf::Vertex{
            sf::Vector2f(static_cast<float>(width), static_cast<float>(y)),
            sf::Color(55, 55, 55)
        });
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
        }

        window.clear(sf::Color(30, 30, 30));
        drawGrid(window);
        window.display();
    }

    return 0;
}
