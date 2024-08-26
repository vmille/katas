//
// Created by Vivien Mille on 25/08/2024.
//
#include <catch2/catch_test_macros.hpp>
#include <ApprovalTests/ApprovalTests.hpp>

#include "gilded_rose/gilded_rose.hxx"

#include <iostream>

namespace vm {
  std::ostream& operator<< (std::ostream& os, vm::item const& obj) {
    return os
        << "name: " << obj.name
        << ", sell_in: " << obj.sell_in
        << ", quality: " << obj.quality;
  }
}
// This is a normal unit test using Catch2
TEST_CASE("update_quality") {
  std::vector<vm::item> items;
  items.push_back(vm::item("foo", 0, 0));
  vm::gilded_rose app(items);
  app.update_quality();
  REQUIRE("foo" == app.items[0].name);
}

// This is an Approval test using https://github.com/approvals/approvaltests.cpp
TEST_CASE("update_quality_approval_test") {
  std::vector<vm::item> items;
  items.push_back(vm::item("foo", 0, 0));
  vm::gilded_rose app(items);
  app.update_quality();
  auto item = app.items[0];
  ApprovalTests::Approvals::verify(item);
}

TEST_CASE("gilded_rose_approval_tests", "VerifyCombinations")
{
  std::vector<std::string> names{"Foo"};
  std::vector<int> sellIns{1};
  std::vector<int> qualities{1};

  auto f = [] (std::string name, int sellIn, int quality) {
    std::vector<vm::item> items = {vm::item(std::move(name), sellIn, quality)};
    vm::gilded_rose app(items);
    app.update_quality();
    return items[0];
  };

  ApprovalTests::CombinationApprovals::verifyAllCombinations(
      f,
      names, sellIns, qualities);
}

TEST_CASE("Sulfuras", "[harness][item test]") {
  std::vector<vm::item> items;
  items.push_back(vm::item("Sulfuras, Hand of Ragnaros", 1, 80));
  vm::gilded_rose app(items);
  REQUIRE("Sulfuras, Hand of Ragnaros" == app.items[0].name);
  REQUIRE(80 == app.items[0].quality);
  app.update_quality();
  REQUIRE(80 == app.items[0].quality);
  app.update_quality();
  REQUIRE(80 == app.items[0].quality);
}

TEST_CASE("Quality decrease by 1 before sold date", "[harness][item test]") {
  std::vector<vm::item> items;
  items.push_back(vm::item("Foo", 10, 30));
  vm::gilded_rose app(items);
  REQUIRE("Foo" == app.items[0].name);
  REQUIRE(30 == app.items[0].quality);
  app.update_quality();
  REQUIRE(29 == app.items[0].quality);
  app.update_quality();
  REQUIRE(28 == app.items[0].quality);
}

TEST_CASE("Quality decrease by 2 after sold date", "[harness][item test]") {
  std::vector<vm::item> items;
  items.push_back(vm::item("Foo", 1, 30));
  vm::gilded_rose app(items);
  REQUIRE("Foo" == app.items[0].name);
  REQUIRE(30 == app.items[0].quality);
  app.update_quality();
  REQUIRE(29 == app.items[0].quality);
  app.update_quality();
  REQUIRE(27 == app.items[0].quality);
  app.update_quality();
  REQUIRE(25 == app.items[0].quality);
}

TEST_CASE("Quality never negative", "[harness][item test]") {
  std::vector<vm::item> items;
  items.push_back(vm::item("Foo", 1, 1));
  vm::gilded_rose app(items);
  REQUIRE("Foo" == app.items[0].name);
  REQUIRE(1 == app.items[0].quality);
  app.update_quality();
  REQUIRE(0 == app.items[0].quality);
  app.update_quality();
  REQUIRE(0 == app.items[0].quality);
}

TEST_CASE("After sold date, Aged Brie gets better quality", "[harness][item test][Aged Brie]") {
  std::vector<vm::item> items;
  items.push_back(vm::item("Aged Brie", 2, 1));
  vm::gilded_rose app(items);
  REQUIRE("Aged Brie" == app.items[0].name);
  REQUIRE(1 == app.items[0].quality);
  app.update_quality();
  REQUIRE(2 == app.items[0].quality);
  app.update_quality();
  REQUIRE(3 == app.items[0].quality);
}