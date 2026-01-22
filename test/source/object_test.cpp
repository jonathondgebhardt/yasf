#include <cstddef>
#include <memory>
#include <string>

#include "yasf/object.hpp"

#include <catch2/catch_test_macros.hpp>

#include "yasf/component.hpp"

TEST_CASE("object: name", "[library]")
{
    auto const obj = yasf::Object{};
    REQUIRE(obj.name() == std::string("object"));
}

TEST_CASE("object: uuid", "[library]")
{
    auto const obj = yasf::Object{};
    CHECK_FALSE(obj.uuid().empty());
}

TEST_CASE("object: add_child", "[library]")
{
    auto obj = yasf::Object{};

    SECTION("name")
    {
        REQUIRE(obj.add_child(std::make_unique<yasf::Object>()));
    }

    SECTION("null child")
    {
        REQUIRE_FALSE(obj.add_child(nullptr));
    }

    SECTION("templated")
    {
        REQUIRE(obj.add_child<yasf::Object>());
    }
}

TEST_CASE("object: get_child", "[library]")
{
    auto obj = yasf::Object{};

    SECTION("no children")
    {
        SECTION("valid name")
        {
            CHECK(obj.get_child("object") == nullptr);
        }

        SECTION("invalid name")
        {
            CHECK(obj.get_child("foo") == nullptr);
        }

        SECTION("templated")
        {
            CHECK(obj.get_child<yasf::Object>() == nullptr);
        }

        SECTION("invalid index")
        {
            CHECK(obj.get_child(std::size_t{0}) == nullptr);
        }
    }

    REQUIRE(obj.add_child(std::make_unique<yasf::Object>()));

    SECTION("one child")
    {
        SECTION("valid name")
        {
            auto* const child = obj.get_child("object");
            REQUIRE(child != nullptr);
            CHECK(child->parent() != nullptr);
        }

        SECTION("wrong name")
        {
            CHECK(obj.get_child("foo") == nullptr);
        }

        SECTION("valid templated")
        {
            auto* const child = obj.get_child<yasf::Object>();
            REQUIRE(child != nullptr);
            CHECK(child->parent() != nullptr);
        }

        // todo: wrong type

        SECTION("valid index")
        {
            auto* const child = obj.get_child(std::size_t{0});
            REQUIRE(child != nullptr);
            CHECK(child->parent() != nullptr);
        }

        SECTION("invalid index")
        {
            CHECK(obj.get_child(std::size_t{1}) == nullptr);
        }
    }
}

TEST_CASE("object: parent", "[library]")
{
    auto obj = yasf::Object{};

    SECTION("take by value")
    {
        REQUIRE(obj.add_child(std::make_unique<yasf::Object>()));
        auto const* child = obj.get_child("object");
        REQUIRE(child != nullptr);
        REQUIRE(child->parent() != nullptr);
    }

    SECTION("templated")
    {
        REQUIRE(obj.add_child<yasf::Object>());
        auto const* child = obj.get_child("object");
        REQUIRE(child != nullptr);
        REQUIRE(child->parent() != nullptr);
    }
}

TEST_CASE("object: remove_child", "[library]")
{
    auto obj = yasf::Object{};
    REQUIRE(obj.add_child<yasf::Object>());

    SECTION("name")
    {
        REQUIRE(obj.remove_child("object"));
    }

    SECTION("templated")
    {
        REQUIRE(obj.remove_child<yasf::Object>());
    }
}

TEST_CASE("object: num_children", "[library]")
{
    auto obj = yasf::Object{};
    CHECK(obj.num_children() == std::size_t{0});

    REQUIRE(obj.add_child<yasf::Object>());
    CHECK(obj.num_children() == std::size_t{1});

    REQUIRE(obj.remove_child("object"));
    CHECK(obj.num_children() == std::size_t{0});
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST_CASE("object: child iterator", "[library]")
{
    auto root = yasf::Object{};

    const auto iterate_and_count_children =
        [](const yasf::Object& obj) -> std::size_t
    {
        auto count = std::size_t{};

        for (auto it = obj.children_begin(); it != obj.children_end(); ++it) {
            ++count;
        }

        return count;
    };

    CHECK(iterate_and_count_children(root) == std::size_t{0});

    REQUIRE(root.add_child<yasf::Object>());
    CHECK(iterate_and_count_children(root) == std::size_t{1});

    SECTION("nested")
    {
        auto* const child = root.get_child(std::size_t{0});
        REQUIRE(child != nullptr);
        REQUIRE(child->add_child<yasf::Object>());

        CHECK(iterate_and_count_children(root) == std::size_t{1});
        CHECK(iterate_and_count_children(*child) == std::size_t{1});
    }

    root.remove_child("object");
    CHECK(iterate_and_count_children(root) == std::size_t{0});
}

// NOLINTEND(readability-function-cognitive-complexity)

TEST_CASE("object: add_component", "[library]")
{
    auto obj = yasf::Object{};

    SECTION("name")
    {
        REQUIRE(obj.add_component(std::make_unique<yasf::Component>()));
    }

    SECTION("null component")
    {
        REQUIRE_FALSE(obj.add_component(nullptr));
    }

    SECTION("templated")
    {
        REQUIRE(obj.add_component<yasf::Component>());
    }
}

TEST_CASE("object: get_component", "[library]")
{
    auto obj = yasf::Object{};
    REQUIRE(obj.add_component(std::make_unique<yasf::Component>()));

    SECTION("name")
    {
        REQUIRE(obj.get_component("component") != nullptr);
    }

    SECTION("valid component")
    {
        REQUIRE(obj.get_component<yasf::Component>() != nullptr);
    }
}

TEST_CASE("object: remove_component", "[library]")
{
    auto obj = yasf::Object{};
    REQUIRE(obj.add_component<yasf::Component>());

    SECTION("name")
    {
        REQUIRE(obj.remove_component("component"));
    }

    SECTION("templated")
    {
        REQUIRE(obj.remove_component<yasf::Component>());
    }
}

TEST_CASE("object: meta_data", "[library]")
{
    auto obj = yasf::Object{};

    SECTION("no data")
    {
        auto meta_data = obj.meta_data<int>("foo");
        REQUIRE(!meta_data.has_value());
    }

    SECTION("set and get")
    {
        obj.set_meta_data("int", 1337);  // NOLINT
        auto meta_data = obj.meta_data<int>("int");
        REQUIRE(meta_data.has_value());
    }

    SECTION("wrong data type")
    {
        obj.set_meta_data("int", 1337);  // NOLINT
        REQUIRE_NOTHROW(obj.meta_data<float>("int"));
    }

    SECTION("overwrite with different data type")
    {
        obj.set_meta_data("int", 1337);  // NOLINT
        REQUIRE_NOTHROW(obj.set_meta_data("int", 1337.0f));  // NOLINT
    }
}
