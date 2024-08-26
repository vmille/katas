//
// Created by Vivien Mille on 25/08/2024.
//

#include "gilded_rose/gilded_rose.hxx"

namespace vm {

  gilded_rose::gilded_rose (std::vector<item>& items) : items(items) {}

  void gilded_rose::update_quality () {
    for (auto& item: items) {
      if (item.name == sulfuras) {
        continue;
      }
      else if (item.name == aged_brie) {
        if (item.quality < 50) {
          item.quality = item.quality + 1;
        }
        if (item.sell_in < 0) {
          if (item.quality < 50) {
            item.quality = item.quality + 1;
          }
        }
        continue;
      }
      else if (item.name == backstage_passes) {
        if (item.quality < 50) {
          item.quality = item.quality + 1;
          if (item.sell_in < 11) {
            item.quality = item.quality + 1;
          }
          if (item.sell_in < 6) {
            item.quality = item.quality + 1;
          }
        }
        item.sell_in = item.sell_in - 1;
        if (item.sell_in < 0) {
          item.quality = 0;
        }
        continue;
      }
      else {
        if (item.quality > 0) {
          item.quality = item.quality - 1;
        }

        item.sell_in = item.sell_in - 1;

        if (item.sell_in < 0) {
          if (item.quality > 0) {
            item.quality = item.quality - 1;
          }
        }
      }
    }
  }
} // vm