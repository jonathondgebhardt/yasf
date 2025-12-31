#pragma once

#include <mutex>

#include <SFML/Graphics/RenderWindow.hpp>

namespace yasf::viewer
{

/**
 * @brief
 */
class GraphicsWindow
{
public:
    struct Config
    {
        std::string name{"yasf Viewer"};
        std::size_t window_width{};
        std::size_t window_height{};
        std::size_t frame_limit{};
    };

    struct GraphicsWindowImpl
    {
        explicit GraphicsWindowImpl(const Config& config);
        std::unique_ptr<sf::RenderWindow> window;
    };

    static auto init(const Config& config) -> void
    {
        const auto lock = std::lock_guard{m_mutex};
        if (m_instance != nullptr) {
            throw std::runtime_error("GraphicsWindow already initialized");
        }

        m_instance = std::make_unique<GraphicsWindowImpl>(config);
    }

    static auto instance() -> sf::RenderWindow*
    {
        const auto lock = std::lock_guard{m_mutex};
        if (m_instance == nullptr) {
            throw std::runtime_error("GraphicsWindow not initialized");
        }

        return m_instance->window.get();
    }

private:
    inline static std::unique_ptr<GraphicsWindowImpl> m_instance;
    inline static std::mutex m_mutex;
};

}  // namespace yasf::viewer
