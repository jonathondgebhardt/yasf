#include <memory>

#include "graphics_window.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace yasf::viewer
{

GraphicsWindow::GraphicsWindowImpl::GraphicsWindowImpl(const Config& config)
    : window{std::make_unique<sf::RenderWindow>(
          sf::VideoMode({static_cast<unsigned int>(config.window_width),
                         static_cast<unsigned int>(config.window_height)}),
          config.name)}
{
    window->setFramerateLimit(static_cast<unsigned int>(config.frame_limit));
}

}  // namespace yasf::viewer
