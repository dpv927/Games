from entity import Entity
import pyray as rl


class Projectile:

    """ 
    The idea of a projectile is very simple: a object that can be spawned
    and controlled by an Entity. A projectile life will be determined by 
    a number of frames from the running game.
    """

    position: rl.Vector2
    speed: rl.Vector2
    direction: rl.Vector2
    father: Entity
    life_frames: int
    frames: int

    def __init__(self, position=rl.Vector2(0,0), speed=rl.Vector2(0,0), 
                 direction=rl.Vector2(0,0), father=None):
        self.position = position
        self.speed = speed
        self.direction = direction
        self.father = father
        self.life_frames = 0
        self.frames = 0

    def move(self):
        pass

    def draw(self):
        pass

    def is_done(self) -> bool:
        return self.frames == self.life_frames


class TexturedProjectile(Projectile):

    """ 
    TexturedProjectile represents a projectile that can be drawn with
    a sprite instead of a raw shape. In this implementation, we suppose that a 
    the projectile's texture contains only 1 sprite. 
    
    If you want more sprites per texture you will have to do override draw() and 
    do something similar as the TexturedEntity from the "entity" module.
    """

    texture: rl.Texture
    width: int
    height: int

    def draw(self):
        rl.draw_texture_pro(
            self.texture,
            rl.Rectangle(
                0, 0,
                self.texture.width,
                self.texture.height
            ),
            rl.Rectangle(
                self.position.x, 
                self.position.y,
                self.width,
                self.height
            ),
            rl.Vector2(0,0),
            0, rl.WHITE
        )