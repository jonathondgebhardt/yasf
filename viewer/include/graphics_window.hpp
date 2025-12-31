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
        std::size_t window_height{};
        std::size_t window_width{};
        std::size_t frame_limit{};
    };

    static auto init(const Config& config) -> void
    {
        const auto lock = std::lock_guard{m_mutex};
        if (m_instance != nullptr) {
            throw std::runtime_error("GraphicsWindow already initialized");
        }

        m_instance = std::make_unique<GraphicsWindow>(config);
    }

    static auto instance() -> GraphicsWindow*
    {
        const auto lock = std::lock_guard{m_mutex};
        if (m_instance == nullptr) {
            throw std::runtime_error("GraphicsWindow not initialized");
        }

        return m_instance.get();
    }

    explicit GraphicsWindow(const Config& config);

    auto handle() const -> sf::RenderWindow* { return m_window.get(); }

private:
    std::unique_ptr<sf::RenderWindow> m_window;

    inline static std::unique_ptr<GraphicsWindow> m_instance;
    inline static std::mutex m_mutex;
};

}  // namespace yasf::viewer
