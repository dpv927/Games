from entities.player import Player
import registry

enemies = []      # List of registered enemies
particles = []    # List of particles
player = Player() # Instance of the player

# List with all registered types of enemies
registry.load_entities_modules()
enemy_classes = list(registry.entity_register.values())


def create_enemy(enemy_class, position):
    # Todo create enemy and
    # register it at enemies
    pass

def create_particle(particle_class, position):
    particle = particle_class(position)
    particles.append(particle)
    pass
