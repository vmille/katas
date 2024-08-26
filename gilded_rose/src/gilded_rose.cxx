//
// Created by Vivien Mille on 25/08/2024.
//

#include "gilded_rose/gilded_rose.hxx"

namespace vm {

  gilded_rose::gilded_rose (std::vector<item>& items) : items(items) {}

  void gilded_rose::update_quality () {
    for (auto& item : items) {
      if (item.name == sulfuras) {
        continue;
      }
      if (item.name != aged_brie && item.name != backstage_passes) {
        if (item.quality > 0 && item.name != sulfuras) {
          item.quality = item.quality - 1;
        }
      }
      else {
        if (item.quality < 50) {
          item.quality = item.quality + 1;
          if (item.name == backstage_passes) {
            if (item.sell_in < 11) {
              item.quality = item.quality + 1;
            }
            if (item.sell_in < 6) {
              item.quality = item.quality + 1;
            }
          }
        }
      }

      item.sell_in = item.sell_in - 1;

      if (item.sell_in < 0) {
        if (item.name != aged_brie) {
          if (item.name != backstage_passes) {
            if (item.quality > 0 && item.name != sulfuras) {
              item.quality = item.quality - 1;
            }
          }
          else {
            item.quality = item.quality - item.quality;
          }
        }
        else if (item.quality < 50) {
          item.quality = item.quality + 1;
        }
      }
    }
  }
} // vm