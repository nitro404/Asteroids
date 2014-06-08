using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Graphics;

namespace Asteroids {

	enum SpaceShipColour { Red, Blue, Green, Yellow }

	enum InputDevice { WSAD, Arrows, Controller1, Controller2, Controller3, Controller4 }

	class SpaceShip : GameObject {

		private SpaceShipColour m_colour;
		private PlayerIndex m_playerNumber;
		private InputDevice m_inputDevice;
		private PlayerIndex m_controllerNumber;
		
		private bool m_isMoving = false;
		private int m_rotatingSequence = 1;
		private float m_thumbStickAngle = 0;
		
		private bool m_fireLaserKeyPressed = false;
		
		private GameSettings m_settings;
		private SpriteSheet m_spriteSheet;
		private Sprite[] m_idleSprite;
		private SpriteAnimation[] m_movingAnimation;
		private ProjectileSystem m_projectileSystem;

		public SpaceShip(PlayerIndex playerNumber, Vector2 position, float rotation, SpriteSheet spriteSheet, ProjectileSystem projectileSystem, GameSettings settings, ContentManager content) {
			// instantiate the player's number with a player index
			m_playerNumber = playerNumber;
				 if(m_playerNumber == PlayerIndex.One)   { m_colour = SpaceShipColour.Red; }
			else if(m_playerNumber == PlayerIndex.Two)   { m_colour = SpaceShipColour.Blue; }
			else if(m_playerNumber == PlayerIndex.Three) { m_colour = SpaceShipColour.Green; }
			else if(m_playerNumber == PlayerIndex.Four)  { m_colour = SpaceShipColour.Yellow; }

			// instantiate the player's input device type
			m_inputDevice = settings.getInputDevice(playerNumber);
				 if(m_inputDevice == InputDevice.Controller1) { m_controllerNumber = PlayerIndex.One; }
			else if(m_inputDevice == InputDevice.Controller2) { m_controllerNumber = PlayerIndex.Two; }
			else if(m_inputDevice == InputDevice.Controller3) { m_controllerNumber = PlayerIndex.Three; }
			else if(m_inputDevice == InputDevice.Controller4) { m_controllerNumber = PlayerIndex.Four; }
			else											  { m_controllerNumber = PlayerIndex.One; }

			// instantiate local variables
			this.position = position;
			this.rotation = rotation;
			m_scale = new Vector2(1, 1);

			m_maximumVelocity = 5.8f;
			m_acceleration = 0.048f;
			m_rotationSpeed = 3.1f;

			m_settings = settings;
			m_spriteSheet = spriteSheet;
			m_projectileSystem = projectileSystem;

			if(m_spriteSheet == null) { return; }

			// initialize sprite / sprite animation arrays
			m_idleSprite = new Sprite[3];
			m_movingAnimation = new SpriteAnimation[3];

			// set the space ship sprite sheet offset based on the space ship colour
			int spriteOffset = 0;
				 if(m_colour == SpaceShipColour.Red)    { spriteOffset = 0; }
			else if(m_colour == SpaceShipColour.Blue)   { spriteOffset = 18; }
			else if(m_colour == SpaceShipColour.Green)  { spriteOffset = 3; }
			else if(m_colour == SpaceShipColour.Yellow) { spriteOffset = 21; }

			// load the idle sprites for each colour
			for(int i=0;i<3;i++) {
				m_idleSprite[i] = m_spriteSheet.getSprite(i + spriteOffset);
			}
			// create and store the movement animations for each colour
			for(int i=0;i<3;i++) {
				m_movingAnimation[i] = new SpriteAnimation(0.16f, SpriteAnimationType.Loop);
				m_movingAnimation[i].addSprite(m_spriteSheet.getSprite(i + spriteOffset + 6));
				m_movingAnimation[i].addSprite(m_spriteSheet.getSprite(i + spriteOffset + 12));
			}

			m_offset = new Vector2(m_idleSprite[1].xOffset * 0.9f, m_idleSprite[1].yOffset * 0.9f);
			m_size = new Vector2(m_offset.X * 2.0f, m_offset.Y * 2.0f);

			updateInitialValues();
		}

		public SpaceShipColour colour {
			get { return m_colour; }
		}

		public PlayerIndex playerNumber {
			get { return m_playerNumber; }
		}

		public InputDevice inputDevice {
			get { return m_inputDevice; }
			set { m_inputDevice = value; }
		}

		public override void update(GameTime gameTime) {
			if(gameTime == null) { return; }

			// update the movement animations
			for(int i=0;i<3;i++) {
				m_movingAnimation[i].update(gameTime);
			}

			// update the space ship's position
			m_position.X += (float) (m_velocity.X * (gameTime.ElapsedGameTime.TotalSeconds / (1.0/60.0)));
			m_position.Y += (float) (m_velocity.Y * (gameTime.ElapsedGameTime.TotalSeconds / (1.0/60.0)));

			if(m_settings == null) { return; }

			// check if the space ship is out of bounds and wrap it around the screen if neccessary
			if(m_position.X > m_settings.screenWidth + m_offset.X) {
				m_position.X -= (m_settings.screenWidth + (size.X * scale.X));
			}
			else if(m_position.X < 0 - m_offset.X) {
				m_position.X += (m_settings.screenWidth + (size.X * scale.X));
			}

			if(m_position.Y > m_settings.screenHeight + m_offset.Y) {
				m_position.Y -= (m_settings.screenHeight + (size.Y * scale.Y));
			}
			else if(m_position.Y < 0 - m_offset.Y) {
				m_position.Y += (m_settings.screenHeight + (size.Y * scale.Y));
			}
		}

		public override void handleInput(GameTime gameTime) {
			KeyboardState keyboard = Keyboard.GetState();

			m_rotatingSequence = 1;
			m_isMoving = false;

			// if the player input is WSAD/Space/LCtrl
			if(m_inputDevice == InputDevice.WSAD) {
				// handle the input
				if(keyboard.IsKeyDown(Keys.W)) { moveForwards(gameTime); }
				if(keyboard.IsKeyDown(Keys.S)) { moveBackwards(gameTime); }
				if(keyboard.IsKeyDown(Keys.A)) { turnLeft(gameTime); }
				if(keyboard.IsKeyDown(Keys.D)) { turnRight(gameTime); }
				if(keyboard.IsKeyDown(Keys.Space) || keyboard.IsKeyDown(Keys.LeftControl)) {
					if(!m_fireLaserKeyPressed) {
						fireLaser();
						m_fireLaserKeyPressed = true;
					}
				}
				else { m_fireLaserKeyPressed = false; }
			}
			// otherwise if the player input is UDLR/Enter/RCtrl
			else if(m_inputDevice == InputDevice.Arrows) {
				// handle the input
				if(keyboard.IsKeyDown(Keys.Up)) { moveForwards(gameTime); }
				if(keyboard.IsKeyDown(Keys.Down)) { moveBackwards(gameTime); }
				if(keyboard.IsKeyDown(Keys.Left)) { turnLeft(gameTime); }
				if(keyboard.IsKeyDown(Keys.Right)) { turnRight(gameTime); }
				if(keyboard.IsKeyDown(Keys.Enter) || keyboard.IsKeyDown(Keys.RightControl)) {
					if(!m_fireLaserKeyPressed) {
						fireLaser();
						m_fireLaserKeyPressed = true;
					}
				}
				else { m_fireLaserKeyPressed = false; }
			}
			// otherwise if the player input is from an Xbox 360 controller
			else {
				GamePadState gamePad = GamePad.GetState(m_controllerNumber);

				m_isMoving = false;

				// calculate the angle the thumbstick is pointing and adjust the ship accordingly
				m_thumbStickAngle = (float)(MathHelper.ToDegrees((float)Math.Atan2(gamePad.ThumbSticks.Left.Y, gamePad.ThumbSticks.Left.X)) - 90.0f);
				if(m_thumbStickAngle < 0) { m_thumbStickAngle += 360.0f; }
				m_thumbStickAngle = -m_thumbStickAngle;

				if(gamePad.ThumbSticks.Left.X != 0 || gamePad.ThumbSticks.Left.Y != 0) {
					m_rotation = m_thumbStickAngle;

					m_isMoving = true;

					updateVelocity(m_acceleration, gameTime);
				}

				// fire the ship's laser if the user presses a
				if(gamePad.IsButtonDown(Buttons.A)) {
					if(!m_fireLaserKeyPressed) {
						fireLaser();
						m_fireLaserKeyPressed = true;
					}
				}
				else { m_fireLaserKeyPressed = false; }
			}

		}

		public override void reset() {
			base.reset();

			m_isMoving = false;
			m_rotatingSequence = 1;
		}

		// render the space ship
		public override void draw(SpriteBatch spriteBatch) {
			if(spriteBatch == null) { return; }

			// if the space ship is moving, render the movement animation
			if(m_isMoving) {
				m_movingAnimation[m_rotatingSequence].sprite.draw(spriteBatch, m_scale, m_rotation, m_position, SpriteEffects.None);
			}
			// otherwise render the idle animation
			else {
				m_idleSprite[m_rotatingSequence].draw(spriteBatch, m_scale, m_rotation, m_position, SpriteEffects.None);
			}
		}

		// turn the ship left
		public void turnLeft(GameTime gameTime) {
			m_rotation -= m_rotationSpeed * (float) (gameTime.ElapsedGameTime.TotalSeconds * 100);
			if(m_rotation < 0) { m_rotation += 360; }
			m_rotatingSequence = 0;
		}

		// turn the ship right
		public void turnRight(GameTime gameTime) {
			m_rotation += m_rotationSpeed * (float) (gameTime.ElapsedGameTime.TotalSeconds * 100);
			if(m_rotation >= 360) { m_rotation -= 360; }
			m_rotatingSequence = 2;
		}

		// accelerate the ship
		public void moveForwards(GameTime gameTime) {
			updateVelocity(m_acceleration, gameTime);
			m_isMoving = true;
		}

		// decellerate the ship
		public void moveBackwards(GameTime gameTime) {
			updateVelocity(-m_acceleration, gameTime);
			m_isMoving = true;
		}

		// fire the ships laser (projectile spawns at the tip of the ship)
		public void fireLaser() {
			if(m_projectileSystem == null) { return; }

			Vector2 projectileSpawn = new Vector2((float)(position.X - 2 - (Math.Sin(MathHelper.ToRadians(-m_rotation)) * 14)),
												  (float)(position.Y - 2 - (Math.Cos(MathHelper.ToRadians(-m_rotation)) * 14)));

			m_projectileSystem.spawnProjectile(projectileSpawn, rotation, this);
		}

		// update the ship's velocity from a given acceleration
		public void updateVelocity(float acceleration, GameTime gameTime) {
			float s = speed;
			Vector2 v = new Vector2((float) (s * Math.Cos(MathHelper.ToRadians(m_rotation - 90.0f))),
									(float) (s * Math.Sin(MathHelper.ToRadians(m_rotation - 90.0f))));

			if(Math.Abs((v.X - m_velocity.X) / v.X) < 0.1f && Math.Abs((v.Y - m_velocity.Y) / v.Y) < 0.1f) {
				float dx = v.X - m_velocity.X;
				float dy = v.X - m_velocity.Y;
				dx /= v.X;
				dy /= v.Y;
				dx = Math.Abs(v.X - m_velocity.X) / v.X;
				dy = Math.Abs(v.Y - m_velocity.Y) / v.Y;
				
				m_velocity.X = v.X;
				m_velocity.Y = v.Y;
			}

			v.X = (float) (acceleration * Math.Cos(MathHelper.ToRadians(rotation - 90.0f)));
			v.Y = (float) (acceleration * Math.Sin(MathHelper.ToRadians(rotation - 90.0f)));

			Vector2 previousVelocity = new Vector2(m_velocity.X, m_velocity.Y);
			m_velocity += v * (float) (gameTime.ElapsedGameTime.TotalSeconds * 100);

			if(Math.Abs(speed) > maximumVelocity) {
				m_velocity = previousVelocity;
			}
		}

		// check if the ship is colliding with another object
		public override bool checkCollision(GameObject o) {
			float distance = (float) Math.Sqrt(Math.Pow(o.position.X - position.X, 2) + Math.Pow(o.position.Y - position.Y, 2));
			return distance < (o.offset.X * o.scale.X) + (m_offset.X * m_scale.X);
		}

		// check if the ship is too close to another object
		public bool checkExtendedCollision(GameObject o) {
			float distance = (float)Math.Sqrt(Math.Pow(o.position.X - position.X, 2) + Math.Pow(o.position.Y - position.Y, 2));
			return distance < (o.offset.X * o.scale.X) + 125.0f;
		}

	}

}
