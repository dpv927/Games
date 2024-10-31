import pyray as rl

class Entity:
    """
    Clase abstracta.
    Una entidad es un objeto el cual tiene la capacidad de desplazarse,
    representarse en la pantalla e interactuar visualmente (o no) con otras
    entidades. Los atributos de una entidad son:
    
    @position: Posicion (x,y) en el espacio de la entidad.
    @speed: Velocidad de desplazamiento (por los ejes x,y) en el espacio.
    """

    position: rl.Vector2
    speed: rl.Vector2

    def __init__(self, position = rl.Vector2(0,0), speed = rl.Vector2(0,0)):
        self.position = position
        self.speed = speed
        
    def move(self):
        """ 
        Funcion para el desplazamiento
        por el espacio. Debe ser sobreescrita.
        """
        pass

    def draw(self):
        """
        Funcion para la representacion de 
        la entidad en la ventana. Debe ser sobreescrita.
        """
        pass



class TexturedEntity(Entity):
    
    """
    A TexturedEntity is a Entity wich can hold sprites and use them
    to represent the Entity at the screen with them, instead of painting
    raw shapes into the screen.

    @texture: Raylib Texture object (Entity sprites).
    @texture_directions: Number of sprite directions.
    @current_sprite: Active sprite (rectangle pointing to it). 
    @sprite_width: Each sprite width in pixels. 
    @sprite_height: Same as @sprite_width but for height.
    @width: Width in pixels for the sprite to be scaled at the screen.
    @height: Same as @widt but for height in pixels.
    """
        
    texture: rl.Texture
    texture_directions = 6
    current_sprite: rl.Rectangle
    sprite_width: int
    sprite_height: int
    width: int
    height: int


    class Orientation():
        DOWN      = 0
        UP        = 1
        LEFT      = 2
        RIGHT     = 3
        DIG_LEFT  = 4
        DIG_RIGHT = 5

    def draw(self):
        rl.draw_texture_pro(
            self.texture,
            self.current_sprite,
            rl.Rectangle(
                self.position.x, 
                self.position.y,
                self.width,
                self.height
            ),
            rl.Vector2(0,0),
            0, rl.WHITE
        )

    def update_texture_info(self):
        self.texture_directions = 6
        self.sprite_width  = self.texture.width/self.texture_directions
        self.sprite_height = self.texture.height
        self.current_sprite = rl.Rectangle(0, 0, self.sprite_width, self.texture.height);

    def change_sprite_direction(self, mx, my):
        if (mx == 0 and my == 0) or (mx == 0 and my > 0):
            self.current_sprite.x = TexturedEntity.Orientation.DOWN
        elif (mx ==  0) and (my < 0):
            self.current_sprite.x = TexturedEntity.Orientation.UP * self.sprite_width
        elif (mx < 0 and my ==  0):
            self.current_sprite.x = TexturedEntity.Orientation.LEFT * self.sprite_width
        elif (mx > 0 and my ==  0):
            self.current_sprite.x = TexturedEntity.Orientation.RIGHT * self.sprite_width
        elif (mx < 0 and my !=  0):
            self.current_sprite.x = TexturedEntity.Orientation.DIG_LEFT * self.sprite_width
        else: self.current_sprite.x = TexturedEntity.Orientation.DIG_RIGHT * self.sprite_width

