import pyray as rl
from buff import Buff

class Entity:
    position: rl.Vector2
    speed: rl.Vector2
    life: int
    buffs: list[Buff]
    texture: rl.Texture

    def __init__(self, position = rl.Vector2(0,0), speed = rl.Vector2(0,0), life = 0, buffs=[]):
        self.position = position
        self.speed = speed
        self.life = life
        self.buffs = buffs

    def move(self):
        pass

    def draw(self):
        pass
