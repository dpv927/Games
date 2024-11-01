from entity import TexturedEntity
from particles.dirt_particle import DirtParticle
import pyray as rl 
import registry
import game
import random

class Player(TexturedEntity):

    def __init__(self):
        super().__init__(speed=rl.Vector2(5,5))
        self.lerp = rl.Vector2(self.position.x, self.position.y)
        self.width = 50
        self.height = 50

    def move(self):
        move_x = int(rl.is_key_down(rl.KeyboardKey.KEY_D)) - int(rl.is_key_down(rl.KeyboardKey.KEY_A))
        move_y = int(rl.is_key_down(rl.KeyboardKey.KEY_S)) - int(rl.is_key_down(rl.KeyboardKey.KEY_W))
        movement = rl.vector2_normalize(rl.Vector2(move_x, move_y))
        self.change_sprite_direction(move_x, move_y)

        if move_x != 0 or move_y !=0:
            x_center = self.position.x + self.width/2
            x = random.randrange(int(x_center - 10), int(x_center + 10))
            y = self.position.y + self.height - 10
            game.create_particle(DirtParticle, rl.Vector2(x, y))        

        self.lerp.x += movement.x * self.speed.x
        self.lerp.y += movement.y * self.speed.y
        
        self.position.x = rl.lerp(self.position.x, self.lerp.x, 0.15)
        self.position.y = rl.lerp(self.position.y, self.lerp.y, 0.15)

# Public player instance
registry.register_texture(Player)