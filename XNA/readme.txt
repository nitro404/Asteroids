===============================
  COMP 3501A Asteroids 1.02
             (Assignment 1)
       NAME: Kevin Scroggins
 STUDENT ID: 100679071
     E-MAIL: kscrogg2@connect.carleton.ca
             OR nitro404@hotmail.com
   DATE DUE: September 22, 2010
  SUBMITTED: September 22, 2010
===============================

=======
 Notes
=======
 + Fully-functional single player and multiplayer game inspired by Atari's Asteroids. Control
   layouts can be changed in the menu for your convenience. A more detailed list of the game
   controls is further down. Currently supports up to 4 players which can be controlled using
   Xbox 360 controllers and / or the keyboard (WSAD / Arrows).

 + I know I did a lot more than was required for this assignment, but hey - I was having way too
   much fun! Let me know what you think! Also if you have any problems compiling or running the
   game, please feel free to contact me via nitro404@hotmail.com .

 + Made with Visual Studio 2008 from scratch in about 4-5 days. Referenced a very similar C++
   version of the game which I made last year, also from scratch in about a week.

 + Uses font "Aston-f1.ttf" - please install this to your fonts directory before compiling/running
   the game. If you do not wish to use this font for any reason, rename the entry in each sprite
   font to "Arial" - though this is strongly recommended against. For your convenience, precompiled
   executables are included. XNA 3.1 and .NET Framework 3.5 required.

 + Artwork found online, used with permission from artist. Sound effects found from free online
   sound effect websites. All sources sited at the bottom of this file.

 + Resolution can only be changed in "settings.ini", all other options are changeable in-game.



==========
 Controls
==========
 + General Controls
   - Alt+Enter: Toggle fullscreen / windowed mode

 + Menu Controls
   - Escape/B: Open / Close menu.
   - Up/W/Joystick: Move menu selection up
   - Down/S/Joystick: Move menu selection down
   - Left/A/Joystick: Move menu selection left
   - Right/D/Joystick: Move menu selection right
   - Enter/Space/A/Start: Activate currently selected menu item

 + In-Game Controls
   - W/Up/Joystick: Accelerate space ship
   - S/Down/Joystick: Deccelerate space ship
   - A/Left/Joystick: Turn space ship left
   - D/Right/Joystick: Turn space ship right
   - Space/Enter/Ctrl/A: Fire primary space ship laser



==========
 Features
==========
 + Fully featured configuration file parsing system which is utilized by a central game settings
   manager which instantiates variables frequently used by the game for simple, quick access.
   Settings files are written in a fashion similar to MS-DOS ini files.

 + Advanced sprite sheet parsing system - sprite details are specified in a single file which is
   read and parsed at load time. Corresponding data is used to load and parse through specified
   sprite sheet, storing each individual sprite in a sprite sheet object. All sprite sheets are
   then stored in a sprite sheet collection object for easy access. Sprites and sprite sheets can
   be accessed by name or index, for ease of use.

 + Fully functional menu with sub-menus and the ability to choose multiple options on a single menu
   item.

 + Multiple input device types (WSAD / Arrow Keys / Xbox 360 Controllers) and the ability to map
   each device to a specific player via the game's menu.

 + Audio track and assorted sound effects for a more in-depth game experience.

 + Simple sprite animation (ie. laser projectiles, space ship afterburner, turning space ship,
   explosions, etc.) give a more interesting look and feel.

 + etc.



========
 Design
========
 + Modular system based design - most functionality for each type of element in the game is
   encapsulated into its own system (for the most part).

 + Variable / VariableSystem / GameSettings
   - A system used to load in configuration files and update them with changes. Fully dynamic, can
     be (and is) reused in various scenarios. Includes categorization of variables for easy access
     and readability. Settings files are in an MS-DOS style INI format for easy editing.

   - A variable represents a pairing of an identifier string (id) and a value (stored as as string)
     as well as an optional category (integer). When used in combination with the VariableSystem,
     the integer is set to reference an index in a collection of category strings to give it more
     meaning and prevent data redundancy (essentially used as a primitive hash).

 + Sprite / SpriteSheet / SpriteSheetCollection
   - A sprite is essentially an abstraction which stores an image that can be rendered to the
     screen. It also has the ability to render only part of a source image (ie. a spritesheet).

   - The SpriteSheet is a collection of sprites (images) which are part of a larger image
     (spritesheet). It has support for parsing sprite sheets from a data file containing
     specifications on how the sprite sheet is designed / layed out. It creates and stores all of
     the corresponding sprites (images) from these specifications.

   - There are 3 types of SpriteSheets:
     1) Arbitrary Offsets - A collection of offsets (x, y) and sizes (width, height) which each
                            represent a sub-image (Sprite) within a larger image (SpriteSheet).
                            Can be instantiated using a constructor or parsed from a file using an
                            array of Rectangles. Name and type can also be specified for each
                            individual Sprite if using the file parser in the order they are to be
                            parsed.
  
     2) Single Grid - Only requires a single offset (x, y) and a single size (width, height) as
                      well as a specification indicating the number of rows and columns, and the
                      direction to parse (vertical or horizontal). Name and type can also be
                      specified for each Sprite in the order they are to be parsed. The constructor
                      will automatically loop through, incrementing as appropriate and creating
                      each Sprite from the SpriteSheet.
  
     3) Multiple Grids - This specification currently only works from the data file parser and does
                         not have a constructor available. Requires the same specifications as a
                         single grid for each grid it is to parse within a single image - these
                         specifications include offset of the current grid (x, y), sizes of each
                         item in the current grid (width, height), number of rows and columns in
                         the current grid and the direction to parse the current grid (vertical or
                         horizontal).

 + Asteroid / AsteroidSystem
   - The asteroid object is automatically instantiated with random values, so there is no
     constructor available that allows you to create a custom asteroid, but it is not needed for
     this project. There are some public interface methods which allow you to manipulate it, but
     nothing more at the present time. If a large asteroid is destroyed, a randomized value of
     small asteroids will spawn from it and begin moving away. Asteroids are also able to collide
     with each other and bounce away with appropriate velocities and angles (for the most part - it
     is a little buggy currently and there are no weights associated with collisions).

   - The asteroid system manages all the asteroids in the game.

 + Projectile / ProjectileSystem
   - The laser projectile is currently the only available projectile in the game. All projectiles
     are managed in the projectile system. Projectiles spawn at the tip of the player's ship and
     move in the direction the ship was aiming.

 + Explosion / ExplosionSystem
   - Explosions can be spawned in place of objects that have been destroyed. The explosion sound is
     managed and played via the explosion system. Explosions that have finished their animation
     cycle are automatically removed. Explosions also move at a gradually decaying speed in the
     same direction as their source.

 + SpaceShip / SpaceShipSystem
   - The space ship represents the player in the game. Handles all input and fires projectiles
     using the projectile system. Space ships are managed through the space ship system.

 + ScoreSystem
   - A simple system to handle the scoring in the game. Keeps track of all player scores and
     updates them accordingly when a player scores more points.

 + CollisionSystem
   - The heart of the game logic - manages all of the games systems. Handles all of the collision
     detection (of all types), updates the scoring system when appropriate, removes destroyed
     objects, spawns explosions, spawns asteroids / asteroid clusters when appropriate, plays
     sounds, resets players when they die, etc.

 + Debug
   - Used for debugging the game by rendering 2D primitives to the screen on the fly (iff it is
     initialized first). Allows for easy on/off by commenting out the initialize line, so you don't
     have to re-add / un-comment your primitive drawing code every time you want to test something.
     Not currently used, but left in for reference.



==============
 Known Issues
==============
 + Turning animations do not play when using a controller

 + Asteroid collision detection is buggy, after a short while asteroids get stuck to each other
   and in most cases will slow down to a halt



==================
 Future Additions
==================
 + Additional game modes (aside from deathmatch):
   - Team Deathmatch
   - Co-Operative
   - Last Man Standing
   - King of the Hill
   - Capture the Flag

 + Powerups and shields

 + Respawn delay options

 + Asteroid population density options

 + Weighted collisions

 + Respawning of asteroids at the edge of the screen instead of anywhere

 + Brake ability (for gamepad users)

 + Extra weapons (ie. bomb sprites added but not implemented)

 + Hit points on certain items (ie. larger asteroids would take 2 shots to destroy)

 + Multiplayer via internet and local networks

 + Artificial intelligence

 + Extra UI features



=========
 Credits
=========
 + Primary Sprites (Used with Permission): http://arboris.deviantart.com/art/Spaceship-sprites-43030167

 + Explosion Animation: http://img206.imageshack.us/i/marinezsheetbq3.png/

 + Explosion Sound Effect: N/A

 + Laser Sound Effect: http://www.therecordist.com/pages/game_sfx.html

 + Menu Sound Effects: http://www.soundjay.com/button-sounds-1.html
   - "Button Sound 33"
   - "Button Sound 43"
   - "Beep 3"
   - "Beep 24"

 + Inspiration: Atari's Asteroids
