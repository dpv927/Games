from entities.player import player_instance as player
import pyray as rl 
import random
import registry

def scale_window():
    monitor = rl.get_current_monitor()
    mon_height = rl.get_monitor_height(monitor)
    mon_width = rl.get_monitor_width(monitor)
    
    width = int(mon_width * 0.5)
    height = int(mon_height * 0.5)
    
    rl.set_window_position(int((mon_width - width)/2), int((mon_height - height)/2))
    rl.set_window_size(width, height)
    return width, height


if __name__ == '__main__':

    #cl = random.choice(list(registry.entity_register.values()))
    #entity = cl()
    
    # Load resources before creating the window
    registry.load_entities_modules() 

    rl.init_window(500, 500, "Spawn")
    rl.set_target_fps(60)
    w, h = scale_window()
    registry.load_textures()

    # Player 2D camera
    camera = rl.Camera2D(rl.Vector2(w/2, h/2), rl.Vector2(0,0), 0, 1)

    # Create a list with enemies arround the player
    # TODO Create a function that spawns entities arround a 
    # circle (out of the window)
    enemies = []
    for i in range(10):
        entity_class = random.choice(list(registry.entity_register.values()))
        entity = entity_class()
        enemies.append(entity)

    while(not rl.window_should_close()):
        player.move()
        camera.target.x = player.position.x
        camera.target.y = player.position.y
        
        for enemy in enemies:
            enemy.move()
    
        rl.begin_drawing()
        rl.clear_background(rl.BROWN)
        rl.begin_mode_2d(camera)
        player.draw()
    
        for enemy in enemies:
            enemy.draw()

        rl.end_mode_2d()
        rl.end_drawing()

    registry.unload_textures()
    rl.close_window()
