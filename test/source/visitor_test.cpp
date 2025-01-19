#include <cstdint>

#include "yasf/visitor.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/component.hpp"
#include "yasf/object.hpp"

struct object_counting_visitor : public yasf::object_visitor
{
    void visit([[maybe_unused]] yasf::object* obj) override { ++m_count; }

    std::uint64_t m_count{};
};

TEST_CASE("object_visitor", "[visitor]")
{
    auto obj = yasf::object{};
    auto visitor = object_counting_visitor{};

    SECTION("single object")
    {
        // object
        obj.accept(visitor);
        CHECK(visitor.m_count == 1);
    }

    REQUIRE(obj.add_child<yasf::object>());

    SECTION("nested object")
    {
        // object
        // - object
        obj.accept(visitor);
        CHECK(visitor.m_count == 2);
    }

    REQUIRE(obj.add_child<yasf::object>());

    SECTION("nested siblings")
    {
        // object
        // - object
        // - object

        obj.accept(visitor);
        CHECK(visitor.m_count == 3);
    }

    auto* child = obj.get_child<yasf::object>();
    REQUIRE(child != nullptr);
    REQUIRE(child->add_child<yasf::object>());

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
