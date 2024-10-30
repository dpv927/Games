import game
import pyray as rl 
import registry
import random
import math

def scale_window():
    monitor = rl.get_current_monitor()
    mon_height = rl.get_monitor_height(monitor)
    mon_width = rl.get_monitor_width(monitor)
    
    width = int(mon_width * 0.8)
    height = int(mon_height * 0.8)
    scale = mon_width/1366
    
    rl.set_window_position(int((mon_width - width)/2), int((mon_height - height)/2))
    rl.set_window_size(width, height)
    return width, height, scale


def random_point_at_circunference(cx, cy, radius):
    alpha = 2 * math.pi * random.random()
    px = radius * (math.cos(alpha) + cx)
    py = radius * (math.sin(alpha) + cy)
    return rl.Vector2(px, py)


if __name__ == '__main__':

    rl.init_window(500, 500, "Spawn")
    rl.set_target_fps(60)
    w, h, s = scale_window()
    registry.load_textures()

    # Player 2D camera
    camera = rl.Camera2D(rl.Vector2(w/2, h/2), rl.Vector2(0,0), 0, s)

    for i in range(10):
        entity_class = random.choice(game.enemy_classes)
        entity = entity_class()
        entity.position = random_point_at_circunference(0,0,h/2)
        game.enemies.append(entity)

    while(not rl.window_should_close()):
        game.player.move()
        camera.target.x = game.player.position.x
        camera.target.y = game.player.position.y

        rl.begin_drawing()
        rl.clear_background(rl.BEIGE)
        rl.begin_mode_2d(camera)

        for enemy in game.enemies:
            enemy.move()
            enemy.draw()

        for particle in game.particles:
            particle.draw()
            particle.update()
        game.particles = [p for p in game.particles if not p.is_done()]           
    
        game.player.draw()
        rl.end_mode_2d()
        rl.end_drawing()

    registry.unload_textures()
    rl.close_window()
