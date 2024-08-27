//
// Created by Vivien Mille on 25/08/2024.
//

#include "gilded_rose/gilded_rose.hxx"

namespace vm {

  gilded_rose::gilded_rose (std::vector<item>& items) : items(items) {}

  constexpr void update_sulfuras (item& _item) {
    --_item.sell_in;
  }

  constexpr void update_aged_brie (item& _item) {
    ++_item.quality;
    if (_item.sell_in < 0) {
      ++_item.quality;
    }
    _item.quality = std::min(_item.quality, 50);
  }

  constexpr void update_baskstage_passes (item& _item) {
    ++_item.quality;
    if (_item.sell_in < 11) {
      ++_item.quality;
    }
    if (_item.sell_in < 6) {
      ++_item.quality;
    }
    --_item.sell_in;
    if (_item.sell_in < 0) {
      _item.quality = 0;
    }
    _item.quality = std::min(_item.quality, 50);
  }

  constexpr void update_default (item& _item) {
    --_item.sell_in;
      _item.quality = _item.quality - 1;
    if (_item.sell_in < 0) {
      _item.quality = _item.quality - 1;
    }
    _item.quality = std::max(0, _item.quality);
  }

  static std::unordered_map<std::string_view, std::function<void (item&)>> rules{
      {aged_brie, update_aged_brie},
      {sulfuras, &update_sulfuras},
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
      update_product(_item);
    }
  }
} // vm