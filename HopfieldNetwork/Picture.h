//
// Created by andrew on 08.03.26.
//

#pragma once
#include <vector>
#include <cstdint>
#include "IDrawable.h"
class Picture : public IDrawable {
public:
    explicit Picture(const std::vector<std::vector<int8_t>>& data_) {
        for (auto& vec : data_) {
            for (auto num : vec) {
                if (num == 0) this->data.push_back(-1);
                else this->data.push_back(num);
            }
        }
    }
    [[nodiscard]] std::size_t numOfPixels() const {return this->data.size();}

    bool operator==(Picture& p) const {
        for (int i = 0 ; i < this->data.size(); ++i) {
            if (this->data.at(i) != p(i)) {
                return false;
            }
            return true;
        }
    }

    int8_t& operator()(std::size_t index) {
        return this->data.at(index);
    }

    void draw(const Rectangle& rec) override;
private:
    std::vector<int8_t> data;
};

