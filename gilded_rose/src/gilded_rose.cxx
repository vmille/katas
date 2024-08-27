//
// Created by Vivien Mille on 25/08/2024.
//

#include "gilded_rose/gilded_rose.hxx"

namespace vm {

  gilded_rose::gilded_rose (std::vector<item>& items) : items(items) {}

  constexpr void increase_quality (item& _item, int fold = 1) {
    _item.quality += fold;
  }

  constexpr void decrease_quality (item& _item, int fold = 1) {
    _item.quality -= fold;
  }

  constexpr void cancel_quality (item& _item) {
    _item.quality = 0;
  }

  constexpr void clamp_quality (item& _item) {
    _item.quality = std::clamp(_item.quality, 0, 50);
  }

  constexpr void update_sulfuras (item& _item) {
    --_item.sell_in;
  }

  constexpr void add_day (item& _item) {
    --_item.sell_in;
  }

  constexpr void update_aged_brie (item& _item) {
    increase_quality(_item);
    if (_item.sell_in < 0) {
      increase_quality(_item);
    }
    clamp_quality(_item);
  }

  constexpr void update_baskstage_passes (item& _item) {
    increase_quality(_item);
    if (_item.sell_in < 10) {
      increase_quality(_item);
    }
    if (_item.sell_in < 5) {
      increase_quality(_item);
    }
    if (_item.sell_in < 0) {
      cancel_quality(_item);
    }
    clamp_quality(_item);
  }

  constexpr void update_default (item& _item) {
    decrease_quality(_item);
    if (_item.sell_in < 0) {
      decrease_quality(_item);
    }
    clamp_quality(_item);
  }

  static std::unordered_map<std::string_view, std::function<void (item&)>> rules{
      {aged_brie, update_aged_brie},
      {sulfuras,  &update_sulfuras},
      {backstage_passes, &update_baskstage_passes}
  };

  void update_product (item& _item) {
    auto const iter = rules.find(_item.name);
    if (iter != std::end(rules)) {
      iter->second(_item);
    }
    else {
      update_default(_item);
    }
  }

  void gilded_rose::update_quality () {
    for (auto& _item: items) {
      add_day(_item);
      update_product(_item);
    }
  }
} // vm