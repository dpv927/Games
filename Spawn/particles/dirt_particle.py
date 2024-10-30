from particle import Particle
import pyray as rl

class DirtParticle(Particle):
    
    def __init__(self, position):
        super().__init__(position=position, life_frames=10)
        self.color = rl.BROWN
        self.width = 10

    def draw(self):
        rl.draw_rectangle(int(self.position.x), int(self.position.y),
                          self.width, self.width, self.color)
        self.color.a -= 255/self.life_frames
