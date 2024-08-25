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
        << ", sellIn: " << obj.sellIn
        << ", quality: " << obj.quality;
  }
}
// This is a normal unit test using Catch2
TEST_CASE("UpdateQuality") {
  std::vector<vm::item> items;
  items.push_back(vm::item("foo", 0, 0));
  vm::gilded_rose app(items);
  app.update_quality();
  REQUIRE("foo" == app.items[0].name);
}

// This is an Approval test using https://github.com/approvals/approvaltests.cpp
TEST_CASE("UpdateQualityApprovalTest") {
  std::vector<vm::item> items;
  items.push_back(vm::item("foo", 0, 0));
  vm::gilded_rose app(items);
  app.update_quality();
  auto item = app.items[0];
  ApprovalTests::Approvals::verify(item);
}

TEST_CASE("GildedRoseApprovalTests", "VerifyCombinations")
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