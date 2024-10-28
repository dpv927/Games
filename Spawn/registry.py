import os
import importlib
import pyray as rl

entity_register = {}
texture_register = []


def register_entity(entity_class):
    """ Register a new class as an entity """
    entity_register[entity_class.__name__] = entity_class


def load_entities_modules(path="entities"):
    """ Loads all entities classes """
    for file in os.listdir("entities"):
        if(file.endswith(".py")):
            module_name = f"{path}.{file[:-3]}"
            importlib.import_module(module_name)


def register_texture(texture_class):
    """ Register and load the texture of a class """
    texture_register.append(texture_class)


def load_textures():
    """ Load all class textures """
    for texture_class in texture_register:
        texture_class.texture = rl.load_texture("entities/" + texture_class.__name__ + ".png")
        texture_class.update_texture_info(texture_class)


def unload_textures():
    """ All textures must be unloaded """
    for texture_class in texture_register:
        rl.unload_texture(texture_class.texture)
