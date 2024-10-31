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
    squares_horizontal = 20
    square_width = int(math.ceil(math.ceil(w/squares_horizontal)/s))
    squares_vertical = int(math.ceil((h/s)/square_width))
    visible_chunk = np.zeros((squares_horizontal, squares_vertical))


    while(not rl.window_should_close()):
        game.player.move()
        camera.target.x = game.player.position.x
        camera.target.y = game.player.position.y

        rl.begin_drawing()
        rl.clear_background(rl.BEIGE)
        rl.begin_mode_2d(camera)              
        
        # Draw background with perlin noise.
        # Calculate origin (x,y)
        x = int(math.floor(camera.target.x - camera.offset.x/s))
        y = int(math.floor(camera.target.y - camera.offset.y/s))

        for i in range(squares_horizontal):
            for j in range(squares_vertical):
                perlin_x = ((i * square_width) + x)/square_width
                perlin_y = ((j * square_width) + y)/square_width
                noise = perlin.noise_at(perlin_x, perlin_y, 32)
                color = color = rl.Color(168, 120, 62, 255)

                if(noise <= 0.1):
                    color = rl.Color(75, 53, 27,255)
                elif(noise <= 0.2):
                    color = rl.Color(94, 67, 34,255)
                elif(noise <= 0.3):
                    color = rl.Color(112, 80, 41, 255)
                elif(noise <= 0.4):
                    color = rl.Color(130, 93, 48,255)
                elif(noise <= 0.5):
                    color = rl.Color(149, 107, 55, 255)               

                rl.draw_rectangle(
                    x + i * square_width, 
                    y + j * square_width,
                    square_width,
                    square_width,
                    color)
                
                
        game.update_game()
        game.player.draw()  

        rl.end_mode_2d()
        rl.end_drawing()

    registry.unload_textures()
    rl.close_window()