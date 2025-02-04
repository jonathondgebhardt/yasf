#include "yasf/event_processor_service.hpp"

#include "yasf/clock.hpp"
#include "yasf/ensure.hpp"
#include "yasf/event.hpp"
#include "yasf/event_processor.hpp"
#include "yasf/logger.hpp"
#include "yasf/object.hpp"
#include "yasf/simulation.hpp"
#include "yasf/visitor.hpp"

namespace
{

struct processor_visitor : public yasf::object_visitor
{
    explicit processor_visitor(yasf::event* evt)
        : m_event{evt}
    {
    }

    void visit(yasf::object* obj) override
    {
        if (auto* proc = dynamic_cast<yasf::event_processor*>(obj)) {
            yasf::log::info("updating {}", proc->name());
            proc->on_event(m_event);
        }
    }

    yasf::event* m_event{};
};

}  // namespace

namespace yasf
{

auto event_processor_service::on_event(event* evt) -> void
{
    auto visitor = processor_visitor{evt};
    accept(visitor);
}

auto event_processor_service::get_simulation() const -> simulation*
{
    return dynamic_cast<simulation*>(parent());
}

auto event_processor_service::get_clock() const -> clock*
{
    auto const* sim = get_simulation();
    ensure(sim != nullptr, "failed to get simulation");
    return sim->get_clock();
}

}  // namespace yasf
