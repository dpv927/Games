from particle import Particle
import pyray as rl
import math

class DirtParticle(Particle):
    
    def __init__(self, position):
        super().__init__(position=position, life_frames=10)
        self.width = 10
        self.brightness = 255

    def draw(self):
        rl.draw_rectangle(int(self.position.x), int(self.position.y),
                          self.width, self.width, rl.Color(127, 106, 79, self.brightness))
        
        self.brightness = abs(self.brightness - int(255/self.life_frames))
        self.width -= 1