import pyray as rl

def world_to_field(max_world, max_field, vec: rl.Vector2):
    x = (max_field * vec.x)/max_world
    y = (max_field * vec.y)/max_world
    return complex(x, y)

def field_to_world(max_world, max_field, vec: complex):
    x = (max_world * vec.real)/max_field
    y = (max_world * vec.imag)/max_field
    return rl.Vector2(x, y)

def calculate_secuence(c, n):
    last = complex(0, 0)
    list = [c]

    for i in range(n):
        new = last**2 + c
        list.append(new)
        last = new
    return list

screen_width = 750
rl.init_window(screen_width, screen_width, "mandelbrot")
rl.set_target_fps(60)


# Max world is basically the the limits of the window
# in a 2D world and max field is the maximum value to
# show in the imaginary representation (max_field + max_field * i).
max_world = screen_width/2
max_field = 1

# Setup the 2D camera with offset so the old window (0,0)
# is now at the middle of the screen.
camera = rl.Camera2D()
camera.offset = rl.Vector2(max_world, max_world)
camera.rotation = 0
camera.target = rl.vector2_zero()
camera.zoom = 1

# Secuence
c = complex(0.33,-0.452)
c_world = field_to_world(max_world, max_field, c)
n = 10
list = calculate_secuence(c, n)

while(not rl.window_should_close()):
    if rl.is_mouse_button_down(rl.MouseButton.MOUSE_BUTTON_LEFT):
        # New position for the c complex number
        c_world = rl.get_screen_to_world_2d(rl.get_mouse_position(), camera)
        c = world_to_field(max_world, max_field, c_world)

        # Calculate the secuence of 'n' complex numbers where zn+1 = zn^2 + c.
        # 0 -> 0^2 + c = c -> c^2 + c -> (c^2 + c)^2 + c ... 
        list = calculate_secuence(c, n)

    rl.begin_drawing()
    rl.clear_background(rl.BLACK)
    rl.begin_mode_2d(camera)

    for i in range(1, list.__len__()):
        previous = field_to_world(max_world, max_field, list[i - 1])
        actual   = field_to_world(max_world, max_field, list[i])
        rl.draw_circle_v(actual, 10, rl.YELLOW)
        rl.draw_line_v(previous, actual, rl.WHITE)
    rl.draw_text("(" + str(c.real) + "," + str(c.imag) + ")", int(c_world.x), int(c_world.y), 30, rl.WHITE)

    rl.end_mode_2d()
    rl.end_drawing()
rl.close_window()