from entities.player import Player
from particle import Particle
from entity import Entity
import registry

enemies: list[Entity]     = []  # List of existing enemies
particles: list[Particle] = []  # List of existing particles
player = Player()               # Instance of the player

# List with all registered types of enemies
registry.load_entities_modules()
enemy_classes = list(registry.entity_register.values())

def update_game():
    global enemies, particles
    for enemy in enemies:
        enemy.move()
        enemy.draw()

    for particle in particles:
        particle.draw()
        particle.update()
    particles = [p for p in particles if not p.is_done()]

def create_enemy(enemy_class, position):
    # Todo create enemy and
    # register it at enemies
    pass

def create_particle(particle_class, position):
    particle = particle_class(position)
    particles.append(particle)
    pass


# TODO put this somewhre
#def random_point_at_circunference(cx, cy, radius):
#    alpha = 2 * math.pi * random.random()
#    px = radius * (math.cos(alpha) + cx)
#    py = radius * (math.sin(alpha) + cy)
#    return rl.Vector2(px, py)
#
#for i in range(10):
#    entity_class = random.choice(game.enemy_classes)
#    entity = entity_class()
#    entity.position = random_point_at_circunference(0,0,h/2)
#    game.enemies.append(entity)