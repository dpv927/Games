from registry import register_entity
from entity import Entity
from .player import player_instance
import random
import pyray as rl

# Possible colors that a Square entity can be
possible_colors = [rl.PURPLE, rl.YELLOW, rl.RED, rl.GREEN]

class Square(Entity):

    def __init__(self):
        super().__init__(speed=rl.Vector2(5,5),position=rl.Vector2(500,500))
        self.color = random.choice(possible_colors)
        self.width = 100

    def draw(self):
        rl.draw_rectangle(int(self.position.x), int(self.position.y),
            self.width, self.width, self.color);
        rl.draw_rectangle_lines(int(self.position.x), int(self.position.y), 
            self.width, self.width, rl.BLACK);
    
    def move(self):
        dist = rl.vector2_subtract(player_instance.position, self.position)
        dist = rl.vector2_normalize(dist)
        self.position.x += dist.x * self.speed.x;
        self.position.y += dist.y * self.speed.y;

register_entity(Square)
