#include "graphics_window.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

namespace yasf::viewer
{

GraphicsWindow::GraphicsWindow(const Config& config)
    : m_window{std::make_unique<sf::RenderWindow>(
          sf::VideoMode({static_cast<unsigned int>(config.window_width),
                         static_cast<unsigned int>(config.window_height)}),
          config.name)}
{
    m_window->setFramerateLimit(static_cast<unsigned int>(config.frame_limit));
}

}  // namespace yasf::viewer
