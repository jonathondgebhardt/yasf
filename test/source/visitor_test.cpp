#include <cstdint>

#include "yasf/visitor.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/component.hpp"
#include "yasf/object.hpp"

namespace
{

struct ObjectCountingVisitor : public yasf::ObjectVisitor
{
    void visit([[maybe_unused]] yasf::Object* obj) override { ++m_count; }

    std::uint64_t m_count{};
};

}  // namespace

TEST_CASE("object_visitor", "[visitor]")
{
    auto obj = yasf::Object{};
    auto visitor = ObjectCountingVisitor{};

    SECTION("single object")
    {
        // object
        obj.accept(visitor);
        CHECK(visitor.m_count == 1);
    }

    REQUIRE(obj.add_child<yasf::Object>());

    SECTION("nested object")
    {
        // object
        // - object
        obj.accept(visitor);
        CHECK(visitor.m_count == 2);
    }

    REQUIRE(obj.add_child<yasf::Object>());

    SECTION("nested siblings")
    {
        // object
        // - object
        // - object

        obj.accept(visitor);
        CHECK(visitor.m_count == 3);
    }

    auto* child = obj.get_child<yasf::Object>();
    REQUIRE(child != nullptr);
    REQUIRE(child->add_child<yasf::Object>());

    SECTION("deeply nested")
    {
        // object
        // - object
        //	  - object
        // - object

        obj.accept(visitor);
        CHECK(visitor.m_count == 4);
    }

    SECTION("visit child of root")
    {
        // object
        // - object
        child->accept(visitor);
        CHECK(visitor.m_count == 2);
    }
}

struct ComponentCountingVisitor : public yasf::ComponentVisitor
{
    void visit([[maybe_unused]] yasf::Component* comp) override { ++m_count; }

    std::uint64_t m_count{};
};

TEST_CASE("component_visitor", "[visitor]")
{
    auto obj = yasf::Object{};
    auto visitor = ComponentCountingVisitor{};

    SECTION("no components")
    {
        obj.accept(visitor);
        CHECK(visitor.m_count == 0);
    }

    REQUIRE(obj.add_component<yasf::Component>());

    SECTION("single component")
    {
        // object
        // - component
        obj.accept(visitor);
        CHECK(visitor.m_count == 1);
    }

    REQUIRE(obj.add_component<yasf::Component>());

    SECTION("two components")
    {
        // object
        // - component
        // - component
        obj.accept(visitor);
        CHECK(visitor.m_count == 2);
    }

    REQUIRE(obj.add_child<yasf::Object>());
    auto* child = obj.get_child<yasf::Object>();
    REQUIRE(child != nullptr);

    SECTION("child with no components")
    {
        // object
        // - component
        // - component
        // - object
        child->accept(visitor);
        CHECK(visitor.m_count == 0);
    }

    REQUIRE(child->add_component<yasf::Component>());

    SECTION("deep components")
    {
        // object
        // - component
        // - component
        // - object
        //	  - component
        obj.accept(visitor);
        CHECK(visitor.m_count == 3);
    }
}
