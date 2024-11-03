from projectile import Projectile
import pyray as rl

class MilkProjectile(Projectile):

    def __init__(self, position=..., direction=..., father=None):
        super().__init__(position, rl.Vector2(10,10), direction, father)
        self.life_frames = 100
        self.radius = 10

    def move(self):
        self.position.x += self.direction.x * self.speed.x
        self.position.y += self.direction.y * self.speed.y
        self.frames += 1

    def draw(self):
        rl.draw_circle(int(self.position.x), int(self.position.y), self.radius, rl.WHITE)
        rl.draw_circle_lines(int(self.position.x), int(self.position.y), self.radius, rl.BLACK)