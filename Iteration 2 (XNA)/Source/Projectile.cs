using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Asteroids {

	class Projectile : GameObject {
		
		private SpriteAnimation m_projectile;
		private SpaceShip m_projectileSource;
		private GameSettings m_settings;

		public Projectile(Vector2 position, float rotation, SpriteAnimation projectileAnimation, SpaceShip projectileSource, GameSettings settings) {
			m_projectile = projectileAnimation;
			this.position = position;
			this.rotation = rotation;
			m_projectileSource = projectileSource;
			m_settings = settings;

			// set the acceleration and velocity of the projectile
			m_acceleration = 9.0f;
			m_velocity.X = (float) (m_acceleration * Math.Cos(MathHelper.ToRadians(m_rotation - 90)));
			m_velocity.Y = (float) (m_acceleration * Math.Sin(MathHelper.ToRadians(m_rotation - 90)));
			
			m_offset = new Vector2(2.0f, 2.0f);
			m_size = new Vector2(4.0f, 4.0f);
		}

		// get the space ship that fired the projectile
		public SpaceShip getProjectileSource() {
			return m_projectileSource;
		}

		// update the projectile
		public override void update(GameTime gameTime) {
			// translate the projectile's position
			m_position.X += (float)(m_velocity.X * (gameTime.ElapsedGameTime.TotalSeconds / (1.0/60.0)));
			m_position.Y += (float)(m_velocity.Y * (gameTime.ElapsedGameTime.TotalSeconds / (1.0/60.0)));

			// update the projectile animation
			if(m_projectile != null) {
				m_projectile.update(gameTime);
			}
		}

		// draw the projectile
		public override void draw(SpriteBatch spriteBatch) {
			if(m_projectile != null) {
				m_projectile.draw(spriteBatch, m_scale, m_rotation, m_position, SpriteEffects.None);
			}
		}

		// check if the projectile is colliding with another object
		public override bool checkCollision(GameObject o) {
			float distance = (float) Math.Sqrt(Math.Pow(o.position.X - position.X, 2) + Math.Pow(o.position.Y - position.Y, 2));
			return distance < (o.offset.X * o.scale.X) + (m_offset.X * m_scale.X);
		}

		// check if the projectile is out of the screen boundaries
		public bool outOfBounds() {
			return m_position.X + m_size.X < 0 ||
				   m_position.Y + m_size.Y < 0 ||
				   m_position.X - m_size.X > ((m_settings == null) ? 0 : m_settings.screenWidth) ||
				   m_position.Y - m_size.Y > ((m_settings == null) ? 0 : m_settings.screenHeight);
		}

	}

}
