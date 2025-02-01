#include "yasf/processor_service.hpp"

#include "yasf/clock.hpp"
#include "yasf/ensure.hpp"
#include "yasf/logger.hpp"
#include "yasf/object.hpp"
#include "yasf/processor.hpp"
#include "yasf/simulation.hpp"
#include "yasf/visitor.hpp"

namespace
{

struct processor_visitor : public yasf::object_visitor
{
    void visit(yasf::object* obj) override
    {
        if (auto* proc = dynamic_cast<yasf::processor*>(obj)) {
            yasf::log::info("updating {}", proc->name());
            proc->update();
        }
    }
};

}  // namespace

namespace yasf
{

auto processor_service::update() -> void
{
    auto visitor = processor_visitor{};
    accept(visitor);
}

auto processor_service::get_simulation() const -> simulation*
{
    return dynamic_cast<simulation*>(parent());
}

auto processor_service::get_clock() const -> clock*
{
    auto const* sim = get_simulation();
    ensure(sim != nullptr, "failed to get simulation");
    return sim->get_clock();
}

}  // namespace yasf
