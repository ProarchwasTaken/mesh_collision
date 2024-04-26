# About
This is project is made to learn about how to detect collisions with a
model's mesh, rather than their bounding box. Collisions are done through
the usage of raycasts. Which means collisions could be a lot more precise,
and it allows for the addition of slopes.

There's still issues with the engine though. For example, the raycasts is
only shot from the player's center position, which still allows for
clipping in some occasions, but I could already think of a couple ways to
fix that.

# Controls
**WASD** - Movement
**R** - Reset player Y position.

The player's position also gets reset if they fall off the map.

# Personal Thoughts
I'm impressed with myself that I managed to figure out how to do this all
on my own. No youtube tutorials at all. I suppose that the method I've
used is what other game developers has used into over to implement 3D
collision as well, but obviously more refined.

One thing about raylib is that their's barely any proper documentation on
how any specific function, or data structure works. I've only managed to
learn the framework by using the cheatsheet, and using common sense. Using
the various raylib examples also helped has well.

Not gonna lie, I think I'm starting to like this fashion of learning. I
don't know why, but I've almost always had trouble learning programming
from youtube tutorials. I guess looking it up and reading the 
documentation is much better for me.

Anyway, I'm planning on making another game eventually. So stay tuned!
