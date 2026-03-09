//
// Created by andrew on 3/9/26.
//


#include <memory>

#include "IDrawable.h"
#include "raygui.h"
#include "Picture.h"
#include "HopfieldNetwork.h"
#include <vector>
class Menu : public IDrawable {
public:
    Menu(std::vector<Picture> pictures,
        std::shared_ptr<HopfieldNetwork> network) : pictures(std::move(pictures)),network(std::move(network)) {}
    void draw(const Rectangle& rec) override;
private:
    std::vector<Picture> pictures;
    std::shared_ptr<HopfieldNetwork> network;
    int currentPictureIndex = 0;
    double energyTextValue = 0;
};


