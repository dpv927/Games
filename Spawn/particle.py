import pyray as rl

class Particle:
    position: rl.Vector2
    life_frames: int
    frames: int

    def __init__(self, position, life_frames):
        self.position = position
        self.life_frames = life_frames
        self.frames = 0

    def draw(self):
        pass

    def update(self):
        self.frames += 1

    def is_done(self) -> bool:
        return self.life_frames == self.frames