using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Asteroids {

	class Asteroid : GameObject {

		private bool m_bigAsteroid = false;
		private List<Asteroid> m_activeCollisions;
		private GameSettings m_settings;

		public Asteroid(Sprite sprite, bool isBigAsteroid, GameSettings settings) {
			m_sprite = sprite;
			m_bigAsteroid = isBigAsteroid;
			m_activeCollisions = new List<Asteroid>();
			m_settings = settings;

			Random rand = new Random();

			if(settings == null) { return; }

			m_position = new Vector2(rand.Next(0, settings.screenWidth), rand.Next(0, settings.screenHeight));

			m_scale = new Vector2(1.0f, 1.0f);

			switch(rand.Next(0, 2)) {
				case 0:
					m_rotationDirection = RotationDirection.Clockwise;
					break;
				case 1:
					m_rotationDirection = RotationDirection.CounterClockwise;
					break;
			}

			float minRotationStep = 0.3153f;
			float maxRotationStep = 0.4584f;
			m_rotationSpeed = (float) (rand.NextDouble() * (maxRotationStep - minRotationStep)) + minRotationStep;
			m_rotation = (float) rand.NextDouble() * 359.0f;

			m_acceleration = 0;
			float minVelocity = (float) (rand.NextDouble() * 0.3f) + 0.08f;
			float maxVelocity = (float) (rand.NextDouble() * 2.5f) + 0.8f;
			float xVelocity = (float) ( (((rand.Next(0, 2) % 2) == 0) ? 1 : -1) * (rand.NextDouble() * (maxVelocity - minVelocity) + minVelocity) );
			float yVelocity = (float) ( (((rand.Next(0, 2) % 2) == 0) ? 1 : -1) * (rand.NextDouble() * (maxVelocity - minVelocity) + minVelocity) );
			m_velocity = new Vector2(xVelocity, yVelocity);
			 
			if(m_sprite == null) { return; }
			m_offset = new Vector2(m_sprite.xOffset * 0.9f, m_sprite.yOffset * 0.9f);
			m_size = new Vector2(m_offset.X * 2.0f, m_offset.Y * 2.0f);
		}

		public bool bigAsteroid {
			get { return m_bigAsteroid; }
			set { m_bigAsteroid = value; }
		}

		public bool addCollision(Asteroid a) {
			if(a == null || m_activeCollisions.Contains(a)) { return false; }
			m_activeCollisions.Add(a);
			return true;
		}

		public bool isCollidingWith(Asteroid a) {
			if(a == null) { return false; }
			return m_activeCollisions.Contains(a);
		}

		public bool removeCollision(Asteroid a) {
			if(a == null) { return false; }
			return m_activeCollisions.Remove(a);
		}

		public void randomizePosition() {
			Random rand = new Random();
			m_position = new Vector2(rand.Next(0, m_settings.screenWidth), rand.Next(0, m_settings.screenHeight));
		}

		public override void update(GameTime gameTime) {
			// increment the rotation of the asteroid
			rotation += ((m_rotationDirection == RotationDirection.Clockwise) ? m_rotationSpeed : -m_rotationSpeed) * (float) (gameTime.ElapsedGameTime.TotalSeconds / (1.0/60.0));

			// increment the position of the asteroid
			float minSpeed = 0.08f;
			if(m_velocity.X < -minSpeed && !(m_velocity.X < minSpeed)) { m_velocity.X = -minSpeed; }
			if(m_velocity.X < minSpeed && !(m_velocity.X < -minSpeed)) { m_velocity.X = minSpeed; }
			if(m_velocity.Y < -minSpeed && !(m_velocity.Y < minSpeed)) { m_velocity.Y = -minSpeed; }
			if(m_velocity.Y < minSpeed && !(m_velocity.Y < -minSpeed)) { m_velocity.Y = minSpeed; }

			m_position.X += (float)(m_velocity.X * (gameTime.ElapsedGameTime.TotalSeconds / (1.0/60.0)));
			m_position.Y += (float)(m_velocity.Y * (gameTime.ElapsedGameTime.TotalSeconds / (1.0/60.0)));

			// boundary check the position of the asteroid and make it wrap-around if it is out of bounds
			if(m_settings == null) { return; }

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

		public override void draw(SpriteBatch spriteBatch) {
			if(m_sprite == null) { return; }
			m_sprite.draw(spriteBatch, m_scale, m_rotation, m_position, SpriteEffects.None);
		}

		public override bool checkCollision(GameObject o) {
			float distance = (float)Math.Sqrt(Math.Pow(o.position.X - position.X, 2) + Math.Pow(o.position.Y - position.Y, 2));
			return distance < (o.offset.X * o.scale.X) + (m_offset.X * m_scale.X);
		}

	}

}
