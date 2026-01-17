#include "yasf/event_processor_service.hpp"

#include "yasf/clock.hpp"
#include "yasf/ensure.hpp"
#include "yasf/event.hpp"
#include "yasf/event_processor.hpp"
#include "yasf/event_simulation.hpp"
#include "yasf/logger.hpp"
#include "yasf/object.hpp"
#include "yasf/visitor.hpp"

namespace
{

struct ProcessorVisitor : yasf::ObjectVisitor
{
    explicit ProcessorVisitor(yasf::Event* evt)
        : event{evt}
    {
    }

    void apply(yasf::Object& obj) override
    {
        if (auto* proc = dynamic_cast<yasf::EventProcessor*>(&obj);
            proc != nullptr)
        {
            yasf::log::info("updating {}", proc->name());
            proc->on_event(event);
        }

        traverse(obj);
    }

    yasf::Event* event{};
};

}  // namespace

namespace yasf
{

auto EventProcessorService::on_event(Event* evt) -> void
{
    auto visitor = ProcessorVisitor{evt};
    accept(visitor);
}

auto EventProcessorService::get_simulation() const -> EventSimulation*
{
    return dynamic_cast<EventSimulation*>(parent());
}

auto EventProcessorService::get_clock() const -> Clock*
{
    auto const* sim = get_simulation();
    Ensure(sim != nullptr, "failed to get simulation");
    return sim->get_clock();
}

}  // namespace yasf
