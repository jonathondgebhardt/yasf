#pragma once

namespace yasf::viewer
{

/**
 * @brief The drawable item.
 */
class Drawable
{
public:
    /**
     * @enum RenderBin
     * @brief Indicates the draw order.
     * @detail Lower RenderBins will be drawn first.
     */
    enum class RenderBin : std::uint8_t
    {
        BACKGROUND = 0,
        FOREGROUND,
        OVERLAY
    };

    virtual ~Drawable() = default;

    virtual auto update() -> void {}

    virtual auto draw() -> void {}

    auto render_bin() const -> RenderBin { return m_render_bin; }

protected:
    RenderBin m_render_bin = RenderBin::FOREGROUND;
};

}  // namespace yasf::viewer
