using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Asteroids {

	class Explosion : GameObject {

		private SpriteAnimation m_explosion;

		public Explosion(Vector2 position, Vector2 velocity, SpriteSheet spriteSheet) {
			m_explosion = new SpriteAnimation(0.17f, SpriteAnimationType.Single, spriteSheet);

			this.position = position;
			this.velocity = velocity;
		}

		public new Sprite sprite {
			get { return m_explosion.sprite; }
		}

		// update the explosion
		public override void update(GameTime gameTime) {
			// decay the speed of the explosion
			m_velocity *= 0.97f;

			// move the explosion in the same direction as its source
			m_position.X += (float)(m_velocity.X * (gameTime.ElapsedGameTime.TotalSeconds / (1.0/60.0)));
			m_position.Y += (float)(m_velocity.Y * (gameTime.ElapsedGameTime.TotalSeconds / (1.0/60.0)));

			// update the explosion animation
			m_explosion.update(gameTime);
		}

		public override void draw(SpriteBatch spriteBatch) {
			m_explosion.draw(spriteBatch, m_scale, m_rotation, m_position, SpriteEffects.None);
		}

		public bool finished() {
			return m_explosion.finished();
		}

	}

}
