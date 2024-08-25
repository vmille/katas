//
// Created by Vivien Mille on 25/08/2024.
//

#ifndef KATAS_GILDED_ROSE_HXX
#define KATAS_GILDED_ROSE_HXX

#include <string>
#include <vector>

namespace vm {
    struct item {
        std::string name;
        int sellIn;
        int quality;
        item(std::string _name, int _sellIn, int _quality) : name(std::move(_name)), sellIn(_sellIn), quality(_quality) {}
    };

    struct gilded_rose {
        std::vector<item>& items;

        gilded_rose(std::vector<item>& items);

        void update_quality();
    };
}
#endif //KATAS_GILDED_ROSE_HXX
