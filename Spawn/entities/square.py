from registry import register_entity
from entity import Entity
import pyray as rl
import game

class Square(Entity):

    def __init__(self):
        super().__init__(speed=rl.Vector2(3,3))
        self.width = 50

    def draw(self):
        rl.draw_rectangle(int(self.position.x), int(self.position.y),
            self.width, self.width, rl.PURPLE);
        rl.draw_rectangle_lines(int(self.position.x), int(self.position.y), 
            self.width, self.width, rl.BLACK);
    
    def move(self):
        dist = rl.vector2_subtract(game.player.position, self.position)
        dist = rl.vector2_normalize(dist)
        self.position.x += dist.x * self.speed.x;
        self.position.y += dist.y * self.speed.y;

register_entity(Square)
