#include <cstdint>

#include "yasf/visitor.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/object.hpp"

namespace
{

struct ObjectCountingVisitor : yasf::ObjectVisitor
{
    explicit ObjectCountingVisitor(const TraversalMode traversal_mode)
        : ObjectVisitor{traversal_mode}
    {
    }

    void apply(yasf::Object& obj) override
    {
        ++count;

        // if maximum_depth is not set, continue traversing.
        // this is kind of sneaky and probably should be in its own class, but
        // i'm lazy.
        if (count < maximum_depth.value_or(count + 1)) {
            traverse(obj);
        }
    }

    std::size_t count{};
    std::optional<std::size_t> maximum_depth;
};

}  // namespace

TEST_CASE("object_visitor: traverse children", "[visitor]")
{
    auto obj = yasf::Object{};
    auto visitor =
        ObjectCountingVisitor{yasf::ObjectVisitor::TraversalMode::CHILDREN};

    SECTION("single object")
    {
        // object
        obj.accept(visitor);
        CHECK(visitor.count == 1);
    }

    REQUIRE(obj.add_child<yasf::Object>());

    SECTION("nested object")
    {
        // object
        // - object
        obj.accept(visitor);
        CHECK(visitor.count == 2);
    }

    REQUIRE(obj.add_child<yasf::Object>());

    SECTION("nested siblings")
    {
        // object
        // - object
        // - object

        obj.accept(visitor);
        CHECK(visitor.count == 3);
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
        CHECK(visitor.count == 4);
    }

    SECTION("deeply nested, stop early")
    {
        // object
        // - object
        //	  - object
        // - object
        visitor.maximum_depth = 2;

        obj.accept(visitor);
        CHECK(visitor.count == 2);
    }

    SECTION("visit child of root")
    {
        // object
        // - object
        child->accept(visitor);
        CHECK(visitor.count == 2);
    }
}

TEST_CASE("object_visitor: traverse parents", "[visitor]")
{
    auto obj = yasf::Object{};
    auto visitor =
        ObjectCountingVisitor{yasf::ObjectVisitor::TraversalMode::PARENTS};

    SECTION("single object")
    {
        // object
        obj.accept(visitor);
        CHECK(visitor.count == 1);
    }

    REQUIRE(obj.add_child<yasf::Object>());

    SECTION("nested object, traverse from root")
    {
        // object
        // - object
        obj.accept(visitor);
        CHECK(visitor.count == 1);
    }

    SECTION("nested object, traverse from leaf")
    {
        // object
        // - object
        obj.get_child<yasf::Object>()->accept(visitor);
        CHECK(visitor.count == 2);
    }

    REQUIRE(obj.add_child<yasf::Object>());

    SECTION("nested siblings")
    {
        // object
        // - object
        // - object

        for (const auto& child : obj.get_children()) {
            child->accept(visitor);
            CHECK(visitor.count == 2);

            visitor.count = 0;
        }
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

        child->get_child<yasf::Object>()->accept(visitor);
        CHECK(visitor.count == 3);
    }

    SECTION("deeply nested, stop early")
    {
        // object
        // - object
        //	  - object
        // - object
        visitor.maximum_depth = 2;

        child->get_child<yasf::Object>()->accept(visitor);
        CHECK(visitor.count == 2);
    }
}
