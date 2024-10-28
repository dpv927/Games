import pyray as rl 
import random
import registry
from player import player_instance

if __name__ == '__main__':
    window_width = 1000 
    window_height = 1000

    rl.init_window(window_width, window_height, "Spawn")
    rl.set_target_fps(60)


    registry.load_entities_modules() 
    registry.load_textures()

    cl = random.choice(list(registry.entity_register.values()))
    entity = cl()
    player = player_instance
    
    while(not rl.window_should_close()):
        player.move()
        rl.begin_drawing()
        rl.clear_background(rl.BLACK)
        entity.draw()
        player.draw()
        rl.end_drawing()

    registry.unload_textures()
    rl.close_window()
