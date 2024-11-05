from projectile import Projectile
import pyray as rl

class MilkProjectile(Projectile):

    cooldown_frames = 15

    def __init__(self, position=..., direction=..., father=None):
        super().__init__(position, rl.Vector2(6,6), direction, father)
        self.life_frames = 100
        self.radius = 10

    def move(self):
        self.position.x += self.direction.x * self.speed.x
        self.position.y += self.direction.y * self.speed.y
        self.life_frames_count += 1

    def draw(self):
        rl.draw_circle(int(self.position.x), int(self.position.y), self.radius, rl.WHITE)
        rl.draw_circle_lines(int(self.position.x), int(self.position.y), self.radius, rl.BLACK)