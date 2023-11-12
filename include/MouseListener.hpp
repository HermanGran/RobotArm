#ifndef MAPPEEKSAMEN_MOUSELISTENER_HPP
#define MAPPEEKSAMEN_MOUSELISTENER_HPP

#include "threepp/threepp.hpp"

using namespace threepp;

namespace {

    struct MyMouseListener: MouseListener {

        bool& mouseClicked;
        Vector2& mousePosition;

        MyMouseListener(bool& clicked, Vector2& pos): mouseClicked(clicked), mousePosition(pos) {}

        void onMouseDown(int button, const Vector2& pos) override {
            if (button == 1) {
                mouseClicked = true;
                mousePosition = pos;
            }
        }

        void onMouseUp(int button, const Vector2& pos) override {
            if (button == 1) {
                mouseClicked = false;
            }
        }
    };
}

#endif //MAPPEEKSAMEN_MOUSELISTENER_HPP
