import game
import pyray as rl
import registry
import math
import perlin
import numpy as np

def scale_window():
    monitor = rl.get_current_monitor()
    mon_height = rl.get_monitor_height(monitor)
    mon_width = rl.get_monitor_width(monitor)
    
    height = int(mon_height * 0.8)
    width = int(mon_width * 0.8)
    scale = mon_width/1366
    
    rl.set_window_position(int((mon_width - width)/2), int((mon_height - height)/2))
    rl.set_window_size(width, height)
    return width, height, scale


if __name__ == '__main__':

    rl.init_window(500, 500, "Spawn")
    rl.set_target_fps(60)
    w, h, s = scale_window()
    registry.load_textures()

    camera = rl.Camera2D(rl.Vector2(w/2, h/2), rl.Vector2(0,0), 0, s)
    
    # Initialize perlin noise variables 
    # (For map generation)
    squares_horizontal = 25
    square_width = int(math.ceil(math.ceil(w/squares_horizontal)/s))
    squares_vertical = int(math.ceil((h/s)/square_width))

    map_squares_horizontal = squares_horizontal + 2
    map_squares_vertical = squares_vertical + 2
    map_chunk = np.zeros((map_squares_vertical, map_squares_horizontal))
    base_map_x = int(math.floor(-(w/2)/s)) - square_width
    base_map_y = int(math.floor(-(h/2)/s)) - square_width
    map_x = 0   # Perlin (x) a la izq arriba
    map_y = 0   # Perlin (y) a la izq arriba
    map_dx = 0
    map_dy = 0

    for i in range(squares_vertical + 2):
        for j in range(squares_horizontal + 2):
            map_chunk[i][j] = perlin.noise_at(i,j)


    while(not rl.window_should_close()):
        game.player.move()
        camera.target.x = game.player.position.x
        camera.target.y = game.player.position.y

        map_dx -= game.player.position.x - game.player.previous_x
        map_dy -= game.player.position.y - game.player.previous_y

        # As we lower or raise the map "image" with map_dx and map_dy (following) 
        # the speed of the player to cause a moving sentation, we need to detect
        # when we need to reposition the map image and calculate new perlin noise
        # rows or columns
    
        if map_dy >= square_width:
            # Generate more terrain up (Move every row down and generate a new
            # perlin noise row at the first row).
            for i in range(map_squares_vertical - 1, 0, -1):
                map_chunk[i] = map_chunk[i - 1]

            map_y -= 1
            map_dy = map_dy - square_width

            for j in range(squares_horizontal + 2):
                map_chunk[0][j] = perlin.noise_at(map_x + j, map_y)

        elif map_dy <= -square_width:
            # Generate more terrain up (Move every row up and generate a new
            # perlin noise row at the last row).
            for i in range(map_squares_vertical - 1):
                map_chunk[i] = map_chunk[i + 1]

            map_y += 1
            map_dy = map_dy + square_width

            for j in range(map_squares_horizontal):
                map_chunk[map_squares_vertical - 1][j] = perlin.noise_at(map_x + j,
                    map_y + map_squares_vertical - 1)

        if map_dx <= -square_width:
            # Generate more terrain at the right (Move every row to the left and 
            # generate a new perlin noise column at the last column).
            for i in range(map_squares_horizontal - 1):
                map_chunk[:,i] = map_chunk[:,i + 1]

            map_x += 1
            map_dx = map_dx + square_width

            for j in range(map_squares_vertical):
                map_chunk[j][map_squares_horizontal-1] = perlin.noise_at(map_x + map_squares_horizontal -1
                    , map_y + j)

        elif map_dx >= square_width:
            # Generate more terrain at the right (Move every row to the left and 
            # generate a new perlin noise column at the last column).
            for i in range(map_squares_horizontal - 1, 0, -1):
                map_chunk[:,i] = map_chunk[:,i - 1]

            map_x -= 1
            map_dx = map_dx - square_width

            for j in range(map_squares_vertical):
                map_chunk[j][0] = perlin.noise_at(map_x , map_y + j)

        rl.begin_drawing()
        rl.begin_mode_2d(camera)
        rl.clear_background(rl.BLACK)

        # Here we just draw the map relatively to the player camera. Notice the
        # map_dx and map_dy parts to move the map "image" and let the player see
        # some fractions of map tiles at the borders. If we didnt do this, the
        # map would just "jump" from pixel to pixel of the perlin noise image
        # causing a weird sensation.

        for i in range(map_squares_vertical):
            for j in range(map_squares_horizontal):
                noise = map_chunk[i][j]

                color = color = rl.Color(0xa8, 0x78, 0x3e, 0xff)
                if(noise <= 0.1):   color = rl.Color(0x4b, 0x35, 0x1b, 0xff)
                elif(noise <= 0.2): color = rl.Color(0x5e, 0x43, 0x22, 0xff)
                elif(noise <= 0.3): color = rl.Color(0x70, 0x50, 0x29, 0xff)
                elif(noise <= 0.4): color = rl.Color(0x82, 0x5d, 0x30, 0xff)
                elif(noise <= 0.5): color = rl.Color(0x95, 0x6b, 0x37, 0xff)

                rl.draw_rectangle(
                    base_map_x + int(camera.target.x) + square_width * j + int(map_dx),
                    base_map_y + int(camera.target.y) + square_width * i + int(map_dy),
                    square_width,
                    square_width,
                    color)
        
        game.update_game()
        game.player.draw()  

        rl.end_mode_2d()
        rl.end_drawing()

    registry.unload_textures()
    rl.close_window()