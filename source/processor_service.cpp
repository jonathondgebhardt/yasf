#include "yasf/processor_service.hpp"

#include "yasf/clock.hpp"
#include "yasf/ensure.hpp"
#include "yasf/object.hpp"
#include "yasf/processor.hpp"
#include "yasf/simulation.hpp"
#include "yasf/visitor.hpp"

namespace
{

struct ProcessorVisitor : yasf::ObjectVisitor
{
    void apply(yasf::Object& obj) override
    {
        if (auto* proc = dynamic_cast<yasf::Processor*>(&obj); proc != nullptr)
        {
            proc->update();
        }

        traverse(obj);
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
