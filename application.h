#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>

#include "gl_viewer.h"
#include "obj.h"
#include "grid.h"
#include "surface.h"

class application : public gl_viewer
{
public:
    application();
    ~application();
    void init_event();
    void draw_event();
    void mouse_click_event(int button, int button_state, int x, int y);
    void mouse_move_event(int x, int y);
    void keyboard_event(unsigned char key, int x, int y);

    void load_grid(char file[]);

private:
    bool solid;
    float lightAngle;
    GLuint program;
    Grid grid;
    Surface surface;
    bool right_button_down;
    int initial_x;
    int material_index;
};

#endif
