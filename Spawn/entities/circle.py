from registry import register_entity
from entity import Entity
import pyray as rl
import game

class Circle(Entity):

    def __init__(self):
        super().__init__(speed=rl.Vector2(6.5,6.5))
        self.radius = 25.

    def draw(self):
        rl.draw_circle_v(self.position, self.radius, rl.YELLOW)
        rl.draw_circle_lines_v(self.position, self.radius, rl.BLACK)
    
    def move(self):
        dist = rl.vector2_subtract(game.player.position, self.position)
        dist = rl.vector2_normalize(dist)
        self.position.x += dist.x * self.speed.x;
        self.position.y += dist.y * self.speed.y;

register_entity(Circle)
