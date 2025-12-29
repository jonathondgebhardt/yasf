#include "yasf/processor_service.hpp"

#include "yasf/clock.hpp"
#include "yasf/ensure.hpp"
#include "yasf/object.hpp"
#include "yasf/processor.hpp"
#include "yasf/simulation.hpp"
#include "yasf/visitor.hpp"

namespace
{

struct ProcessorVisitor : public yasf::ObjectVisitor
{
    void visit(yasf::Object* obj) override
    {
        if (auto* proc = dynamic_cast<yasf::Processor*>(obj)) {
            proc->update();
        }
    }
};

}  // namespace

namespace yasf
{

auto ProcessorService::update() -> void
{
    auto visitor = ProcessorVisitor{};
    accept(visitor);
}

auto ProcessorService::get_simulation() const -> Simulation*
{
    return dynamic_cast<Simulation*>(parent());
}

auto ProcessorService::get_clock() const -> Clock*
{
    auto const* sim = get_simulation();
    Ensure(sim != nullptr, "failed to get simulation");
    return sim->get_clock();
}

}  // namespace yasf
