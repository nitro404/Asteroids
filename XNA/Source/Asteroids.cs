using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;
using Microsoft.Xna.Framework.Net;
using Microsoft.Xna.Framework.Storage;

namespace Asteroids {
	
	public class Asteroids : Microsoft.Xna.Framework.Game {

		private GameSettings settings;
		private ContentManager content;
		private GraphicsDeviceManager graphics;
		private SpriteBatch spriteBatch;
		private SpriteSheetCollection spriteSheets;
		private Menu menu;
		private ProjectileSystem projectileSystem;
		private SpaceShipSystem spaceShipSystem;
		private AsteroidSystem asteroidSystem;
		private ExplosionSystem explosionSystem;
		private ScoreSystem scoreSystem;
		private CollisionSystem collisionSystem;

		public Song backgroundMusic;
		private bool fullScreenButtonPressed = false;

		public Asteroids() {
			settings = new GameSettings();
			graphics = new GraphicsDeviceManager(this);
			content = new ContentManager(Services, "Content");
		}
		
		protected override void Initialize() {
			// load the game settings from file
			settings.loadFrom(GameSettings.defaultFile);

			// set the screen resolution
			graphics.PreferredBackBufferWidth = settings.screenWidth;
			graphics.PreferredBackBufferHeight = settings.screenHeight;
			graphics.ApplyChanges();

			// set the screen attributes / full screen mode
			Window.AllowUserResizing = false;
			if(settings.fullScreen) {
				graphics.ToggleFullScreen();
			}

			base.Initialize();
		}
		
		protected override void LoadContent() {
			// initialize sprite batching and the sprite sheet collection
			spriteBatch = new SpriteBatch(GraphicsDevice);
			spriteSheets = SpriteSheetCollection.parseFrom(settings.spriteSheetFileName, content);
			if(spriteSheets == null) { Exit(); }

			// initialize the game management systems
			projectileSystem = new ProjectileSystem(spriteSheets, settings, content);
			spaceShipSystem = new SpaceShipSystem(spriteSheets, projectileSystem, settings, content);
			asteroidSystem = new AsteroidSystem(spriteSheets, spaceShipSystem, settings);
			explosionSystem = new ExplosionSystem(spriteSheets, content);
			scoreSystem = new ScoreSystem(spaceShipSystem, content, settings);
			collisionSystem = new CollisionSystem(projectileSystem, spaceShipSystem, asteroidSystem, explosionSystem, scoreSystem);

			// initialize the menu
			menu = new Menu(this, spaceShipSystem, settings, content);

			// load and start the background music (if appropriate)
			backgroundMusic = content.Load<Song>("myg0t");
			MediaPlayer.IsRepeating = true;
			if(settings.musicEnabled) {
				MediaPlayer.Play(backgroundMusic);
			}
		}

		protected override void UnloadContent() {
			content.Unload();
		}

		protected override void Update(GameTime gameTime) {
			KeyboardState keyboard = Keyboard.GetState();
			
			if(IsActive) {
				// toggle fullscreen / windowed mode with alt + enter
				if((keyboard.IsKeyDown(Keys.LeftAlt) || keyboard.IsKeyDown(Keys.RightAlt)) &&
					keyboard.IsKeyDown(Keys.Enter)) {
					if(!fullScreenButtonPressed) {
						graphics.ToggleFullScreen();
						settings.fullScreen = graphics.IsFullScreen;
						fullScreenButtonPressed = true;
					}
				}
				else { fullScreenButtonPressed = false; }

				bool alternateInput = fullScreenButtonPressed;

				if(!alternateInput) {
					// handle menu input
					menu.handleInput();

					if(!menu.active) {
						// handle player input
						spaceShipSystem.handleInput(gameTime);
					}
				}
			}
			
			// update game management systems (if menu is off)
			if(!menu.active) {
				projectileSystem.update(gameTime);

				spaceShipSystem.update(gameTime);

				asteroidSystem.update(gameTime);

				explosionSystem.update(gameTime);

				collisionSystem.handleCollisions();
			}

			base.Update(gameTime);
		}

		protected override void Draw(GameTime gameTime) {
			GraphicsDevice.Clear(Color.Black);
			
			spriteBatch.Begin();

			// tell the game management systems to render all of the game's entities (if the game has been started)
			if(spaceShipSystem.numberOfSpaceShips > 0) {
				projectileSystem.draw(spriteBatch);

				spaceShipSystem.draw(spriteBatch);

				asteroidSystem.draw(spriteBatch);
				
				explosionSystem.draw(spriteBatch);

				scoreSystem.draw(spriteBatch);
			}

			// render the menu (if appropriate)
			menu.draw(spriteBatch);

			spriteBatch.End();

			base.Draw(gameTime);
		}

		public void Reset() {
			// reset all appropriate game management systems
			spaceShipSystem.reset();

			asteroidSystem.reset();

			projectileSystem.reset();
		}

		public void ResetScores() {
			// reset the scores
			scoreSystem.reset();
		}

		protected override void OnExiting(object sender, EventArgs args) {
			// update the game settings file with changes
			settings.saveTo(GameSettings.defaultFile);
			base.OnExiting(sender, args);
		}
	}
}
