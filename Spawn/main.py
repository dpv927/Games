import game
import pyray as rl
import registry
from perlin_map import PerlinMap

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
    game.window_width = w
    game.window_height = h
    game.scale = s
    registry.load_textures()

    camera = rl.Camera2D(rl.Vector2(w/2, h/2), rl.Vector2(0,0), 0, s)
    world_map = PerlinMap(w, h, s)

    while(not rl.window_should_close()):
        game.player.move()
        game.player.shoot()
        camera.target.x = game.player.position.x
        camera.target.y = game.player.position.y
        world_map.update()

        rl.begin_drawing()
        rl.begin_mode_2d(camera)

        world_map.draw(camera.target)
        game.update_game()
        game.player.draw()  

        rl.end_mode_2d()
        rl.end_drawing()

    registry.unload_textures()
    rl.close_window()