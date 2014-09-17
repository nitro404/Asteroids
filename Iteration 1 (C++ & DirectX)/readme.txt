===============================
  COMP 2501A Assignment 4
             a.k.a. Tutorial 7
             a.k.a. Tutorial 8
       NAME: Kevin Scroggins
 STUDENT ID: 100679071
     E-MAIL: kscrogg2@connect.carleton.ca
             OR nitro404@hotmail.com
   DATE DUE: March 10, 2010
  SUBMITTED: March 10, 2010
===============================

==========
 Comments
==========
 + So.. I basically got a little carried away with this assignment and decided to see what I was
   capable of doing, and I rather surprised myself. I also wanted to implement things that I would
   later be implementing in my final project, to avoid making critical mistakes when it was too
   late. I've learned a lot from experimenting with different online tutorials and trial/error. I
   had collision detection and a fully-functional game as of a week ago. I've just been adding
   finishing touches to it over the past week and a bit. Very happy with how it turned out, I hope
   you enjoy it!


=======
 Notes
=======
 + Fully-functional single player and multiplayer hot seat re-make of Asteroids.

 + Made with Visual Studio 2008

 + Copied over some of my own added functionality from previous tutorials / assignments, which has
   since been re-written.

 + Will need to change DirectX includes/library directories before compiling for all projects.

 + Compile under Release mode only - Debug mode contains additional debug outputting for collision
   detection and other misc. things; unless you want to try it out. You will also have to remove
   the reference to #include <vld.h> - this is the Virtual Leak Detector, a really awesome tool for
   detecting memory leaks in your code and showing you explicitly where they are.

 + Controls
   - In-Menu
     > UP/W - Move selection up.

     > DOWN/S - Move selection down.

     > SPACE/ENTER - Select current item.

     > ESCAPE - Go to main menu / exit.

   - In-Game
     > ESCAPE - Return to main menu (forgets current game session).

     > W/S/A/D - Player 1 movement controls.

     > LEFT CTRL/SPACE/LEFT-CLICK - Player 1 fire laser.

     > UP/DOWN/LEFT/RIGHT - Player 2 movement controls.

     > RIGHT CTRL/ENTER - Player 2 fire laser

     > RIGHT-CLICK - Change rotation direction of all asteroids.

 + Original artwork and test spritesheets have been included for your convenience / curiosity.

 + 90% of the code in this project was either entirely re-written from scratch or heavily modified
   from it's original state. The entire structure of the program was changed drastically. For
   example:
   - Added personal code which automatically parses a settings / configuration file for the game.

   - Added extra macros for debugging purposes.

   - Simplified the program structure - the main entry point function can be found in Main.cpp.

   - All code related to the game engine itself is encapsulated in Game.cpp.

   - There is also a simple menu which is created and manipulated in the Game object.

   - Added various abstractions for easily creating/rendering/manipulating sprites, spritesheets,
     text and sounds.

   - Added sound effects to the game (though a little buggy).

   - Multiplayer has a dynamically placed scoreboard (currently has a rough implementation) which
     is placed at the top of the screen if more than one player is present. Also functions
     perfectly, unless you happen to get two scores over 100 - then the text will overlap.

   - Collision detection is done using circular radius checks based on the distance between two
     objects. Was the best approach given the circumstances. Left collision detection with a fairly
     inefficient algorithm - there will not be many checks to be done, so this really wont be an
     issue. Can change later, if neccessary.

   - Objects follow a specific layout as specified in Object.h (abstract class).

   - Added objects:
     > SpaceShip - Previously named "Rocket" - this is the player's space ship. It stores data
                   relevant to the ship itself, and the projectiles it fires. Each space ship
                   is colour co-ordinated based on which player it belongs to. Player 1 is red,
                   player 2 is blue, player 3 is green and player 4 is yellow. Also contains simple
                   animation for pulsating boosters and turning.

     > Asteroid - Previously named "QuadRock" - this is the asteroid object. There is no explicit
                  constructor allowing you to customize the attributes of the asteroid, simply a
                  somewhat default constructor which instantiates the asteroid with random values.
                  There are some public interface methods which allow you to manipulate it, but
                  nothing more at the present time. If a large asteroid is destroyed, a randomized
                  value of asteroids will spawn from it and begin moving away. Asteroids are also
                  able to collide with each other and bounce away with appropriate velocities and
                  angles.

     > Projectile - Also known as "Bullet" - this is currently the laser projectile that is fired
                    from the space ship. It is also colour co-ordinated based on which ship fired
                    it. The projectile is pointing the same direction as the ship and continues
                    travelling in the direction the ship was aiming and it also explicitly spawns at
                    the tip of the ship.

     > Explosion - An added explosion effect - appears when a player's ship collides with another
                   asteroid or is shot by another ship. It is removed from the Game once its
                   animation sequence has been completed. The explosion also moves (gradually
                   slower) on each tick, in the same direction as the original object was
                   travelling.

 + Game currently supports up to 4 players, but does not have keypindings for players 3 and 4. You
   can test this by explicitly adding the following to the Game constructor:
   - setNumberOfPlayers(3);   OR   setNumberOfPlayers(4);
   - mainMenuActive(false);
   - reset(true);

 + Etc.

 + Main CPP code files not really commented - but header files have brief explanation with comments
   of general program layout. So if you want to know how anything functions or what it does, check
   out the header file for it! Feel free to ask me if you have any questions or concerns, thanks!



========================
 Future Implementations
========================
 + Multiplayer networking (as well as hotseat networking, ie. 2v2 on 2 computers)

 + Different gamemodes that actually use the scoring system (ie. deathmatch, team deathmatch, last
   man standing, capture the flag, asteroid destruction race, etc.)

 + Better asteroid spawning - they currently spawn in arbitrary places on the screen, would like to
   make them either fade in or appear outside the screen and enter from an edge.

 + Better asteroid wrap-around - currently if an asteroid is half-off the screen, it simply
   teleports to the opposite side. I would like to change it so it's a more smooth operation - this
   would involve adding a second "duplicate" asteroid on the other side of the screen, then once
   original asteroid goes out of bounds, it is simply deleted. Will look into this later.

 + Proper sound playback - currently sounds interrupt each other if more than one begins to play at
   the same time. I only used the simple windows PlaySound() function, but will be changing this
   later. I attempted to use multi-threading in the sound class, but was met with no success.

 + Possibly more gameplay dynamics, such as shields, powerups, alternate weapons, bombs (already
   half-implemented), space proximity mines, aliens (enemies with ai), etc.


=========
 Credits
=========
 + Primary Sprites (Used with Permission): http://arboris.deviantart.com/art/Spaceship-sprites-43030167

 + Explosion Animation: http://img206.imageshack.us/i/marinezsheetbq3.png/

 + Explosion Sound Effect: N/A

 + Laser Sound Effect: http://www.therecordist.com/pages/game_sfx.html
