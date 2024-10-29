from entity import TexturedEntity
from buff import Buff
import pyray as rl 
import registry

class Player(TexturedEntity):

    texture: rl.Texture
    buffs: list[Buff]

    def __init__(self):
        super().__init__(speed=rl.Vector2(10,10))
        self.lerp_x = self.position.x
        self.lerp_y = self.position.y
        self.buffs = []

    def move(self):
        move_x = int(rl.is_key_down(rl.KeyboardKey.KEY_D)) - int(rl.is_key_down(rl.KeyboardKey.KEY_A))
        move_y = int(rl.is_key_down(rl.KeyboardKey.KEY_S)) - int(rl.is_key_down(rl.KeyboardKey.KEY_W))
        movement = rl.vector2_normalize(rl.Vector2(move_x, move_y))
        self.change_sprite_direction(move_x, move_y)

        self.lerp_x += movement.x * self.speed.x
        self.lerp_y += movement.y * self.speed.y
        
        self.position.x = rl.lerp(self.position.x, self.lerp_x, 0.15)
        self.position.y = rl.lerp(self.position.y, self.lerp_y, 0.15)

    def set_position(self, x, y):
        self.position.x = x 
        self.position.y = y 
        self.lerp_x = x
        self.lerp_y = y

# Public player instance
registry.register_texture(Player)
