#include "list.h"

#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>

void FillList(List & list, size_t element_count) {
    for (int i = 0 ; i < element_count; ++i) {
        list.PushBack(i);
    }
}

void FillListByPushBack(List & list, const std::vector<int>& elements) {
    for (int i = 0 ; i < elements.size(); ++i) {
        list.PushBack(elements[i]);
    }
}

void FillListByPushFront(List & list, const std::vector<int>& elements) {
    for (int i = 0 ; i < elements.size(); ++i) {
        list.PushFront(elements[i]);
    }
}

TEST_CASE("Test Empty", "[empty test]") {
    SECTION("Created list is empty") {
        List list_empty;
        CHECK(list_empty.Empty() == true);
    }

    SECTION("List with 1 element") {
        List list;
        list.PushBack(5);
        CHECK(list.Empty() == false);
        list.PopBack();
        CHECK(list.Empty() == true);
    }
}

TEST_CASE("Test Size", "[size test]") {
    SECTION("Created list has size == 0") {
        List list_empty;
        CHECK(list_empty.Size() == 0);
    }

    SECTION("Increasing size after push") {
        List list;
        list.PushBack(5);
        CHECK(list.Size() == 1);

        list.PushBack(5);
        CHECK(list.Size() == 2);

        list.PushFront(5);
        CHECK(list.Size() == 3);

        list.PushBack(5);
        CHECK(list.Size() == 4);
    }

    SECTION("Decreasing size after pop") {
        List list;
        size_t expected_size = 5;
        FillList(list, expected_size);
        CHECK(list.Size() == expected_size);

        list.PopFront();
        --expected_size;
        CHECK(list.Size() == expected_size);

        list.PopBack();
        --expected_size;
        CHECK(list.Size() == expected_size);

        for (int i = expected_size; i > 0; --i, --expected_size) {
            list.PopFront();
        }
        CHECK(list.Size() == expected_size);
    }
}

TEST_CASE("Test Clear", "[clear test]") {
    SECTION("Clear empty list is empty") {
        List list_empty;
        list_empty.Clear();
        CHECK(list_empty.Empty() == true);
        CHECK(list_empty.Size() == 0);
    }

    SECTION("Clear list") {
        List list;
        size_t expected_size = 5;
        FillList(list, expected_size);
        list.Clear();
        CHECK(list.Empty() == true);
        CHECK(list.Size() == 0);
    }

    SECTION("Double Clear") {
        List list;
        size_t expected_size = 5;
        FillList(list, expected_size);
        list.Clear();
        list.Clear();
        CHECK(list.Empty() == true);
        CHECK(list.Size() == 0);
    }
}

TEST_CASE("Test Push", "[push test]") {
    SECTION("PushBack") {
        List list;
        size_t expected_size = 5;
        for (int i = 0 ; i < expected_size; ++i) {
            CHECK(list.Size() == i);
            list.PushBack(i);
            CHECK(list.Empty() == false);
        }
        CHECK(list.Size() == expected_size);
    }

    SECTION("PushFront") {
        List list;
        size_t expected_size = 5;
        for (int i = 0 ; i < expected_size; ++i) {
            CHECK(list.Size() == i);
            list.PushFront(i);
            CHECK(list.Empty() == false);
        }
        CHECK(list.Size() == expected_size);
    }

    SECTION("PushBack PushFront") {
        List list;
        size_t expected_size = 10;
        for (int i = 0 ; i < expected_size; ++i) {
            CHECK(list.Size() == i);
            if (i % 2 == 0) {
                list.PushFront(i);
            } else {
                list.PushBack(i);
            }
            CHECK(list.Empty() == false);
        }
        CHECK(list.Size() == expected_size);
    }
}
TEST_CASE("Test Pop", "[push_back test]") {
    SECTION("Throw exception if pop empty list") {
        List list_empty;
        CHECK_THROWS_AS(list_empty.PopFront(), std::runtime_error);
        CHECK_THROWS_AS(list_empty.PopBack(), std::runtime_error);

        List list;
        size_t expected_size = 100;
        FillList(list, expected_size);
        list.Clear();
        CHECK_THROWS_AS(list_empty.PopFront(), std::runtime_error);
        CHECK_THROWS_AS(list_empty.PopBack(), std::runtime_error);
    }

    SECTION("PopFront") {
        List list;
        std::vector<int> expected = {1, 2, 3, 4, 5};
        FillListByPushBack(list, expected);
        for (size_t i = 0; i < expected.size(); ++i) {
            CHECK(list.PopFront() == expected[i]);
            CHECK(list.Size() == expected.size() - i - 1);
        }
        CHECK(list.Size() == 0);
        CHECK(list.Empty() == true);
    }

    SECTION("PopBack") {
        List list;
        std::vector<int> expected = {1, 2, 3, 4, 5};
        FillListByPushFront(list, expected);
        for (size_t i = 0; i < expected.size(); ++i) {
            CHECK(list.PopBack() == expected[i]);
            CHECK(list.Size() == expected.size() - i - 1);
        }
        CHECK(list.Size() == 0);
        CHECK(list.Empty() == true);
    }
}


int main() {
    return Catch::Session().run();
}