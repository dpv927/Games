import pyray as rl

class Entity:
    position: rl.Vector2
    speed: rl.Vector2
    life: int

    def __init__(self, position = rl.Vector2(0,0), speed = rl.Vector2(0,0), life = 0):
        self.position = position
        self.speed = speed
        self.life = life

    def move(self):
        pass

    def draw(self):
        pass


class TexturedEntity(Entity):
    texture: rl.Texture
    texture_directions = 6
    current_sprite: rl.Rectangle
    sprite_width: int
    sprite_height: int

    def draw(self):
        rl.draw_texture_pro(
            self.texture,
            self.current_sprite,
            rl.Rectangle(
                self.position.x, 
                self.position.y,
                self.sprite_width,
                self.sprite_height
            ),
            rl.Vector2(0,0),
            0, rl.WHITE
        );

    def update_texture_info(self):
        self.texture_directions = 6
        self.sprite_width  = self.texture.width/self.texture_directions
        self.sprite_height = self.sprite_width
        self.current_sprite = rl.Rectangle(0, 0, self.sprite_width, self.texture.height);

