<div align="center">
  <h1>Dungeon Tree Generator</h1>
  <img src="https://github.com/user-attachments/assets/4f4d506f-9e35-412d-ae6e-7c5a740ab3a5" alt="image" width="500" height="500">
</div>

## About

This algorithm generates a dungeon by generating a tree of connections between rooms.
Each room has 4 sides, on which a single connection to another room can be created.

The procedure is simple: first, a root room connected to 4 rooms (one on each side)
is created and for each of these 4 rooms a sub-tree of connections is created 
recursively until a certain level of depth is reached.

The recursion consists in creating a random number between 1 and 3 of connections to new
rooms, and for each new room repeat the process. During the process, it is checked that 
the generated room does not have the same (x,y) coordinates as another existing room 
(avoiding overlapping) and that there are no repeated rooms.

A detail that can be implemented is to modify the procedure to avoid overlapping, so a 
new room is not created but the existing room is connected to the current room.
