from registry import register_entity
from entity import Entity
import pyray as rl

class Square(Entity):

    def __init__(self):
        super().__init__(position=rl.Vector2(300,400))

    def draw(self):
        rl.draw_rectangle(int(self.position.x), int(self.position.y), 
                             100, 100, rl.YELLOW);

register_entity(Square)
