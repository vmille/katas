//
// Created by Vivien Mille on 25/08/2024.
//

#include "gilded_rose/gilded_rose.hxx"

namespace vm {

  gilded_rose::gilded_rose (std::vector<item>& items) : items(items) {}

  void gilded_rose::update_quality () {
    for (int i = 0; i < items.size(); i++) {
      if (items[i].name != aged_brie && items[i].name != backstage_passes) {
        if (items[i].quality > 0 && items[i].name != sulfuras) {
          items[i].quality = items[i].quality - 1;
        }
      }
      else {
        if (items[i].quality < 50) {
          items[i].quality = items[i].quality + 1;
          if (items[i].name == backstage_passes) {
            if (items[i].sell_in < 11 && items[i].quality < 50) {
              items[i].quality = items[i].quality + 1;
            }

            if (items[i].sell_in < 6 && items[i].quality < 50) {
              items[i].quality = items[i].quality + 1;
            }
          }
        }
      }

      if (items[i].name != sulfuras) {
        items[i].sell_in = items[i].sell_in - 1;
      }

      if (items[i].sell_in < 0) {
        if (items[i].name != aged_brie) {
          if (items[i].name != backstage_passes) {
            if (items[i].quality > 0 && items[i].name != sulfuras) {
              items[i].quality = items[i].quality - 1;
            }
          }
          else {
            items[i].quality = items[i].quality - items[i].quality;
          }
        }
        else if (items[i].quality < 50) {
          items[i].quality = items[i].quality + 1;
        }
      }
    }
  }
} // vm