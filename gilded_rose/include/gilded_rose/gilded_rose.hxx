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
        int sell_in;
        int quality;
        item(std::string _name, int _sell_in, int _quality) : name(std::move(_name)), sell_in(_sell_in), quality(_quality) {}
    };

    struct gilded_rose {
        std::vector<item>& items;

        gilded_rose(std::vector<item>& items);

        void update_quality();
    };
}
#endif //KATAS_GILDED_ROSE_HXX
