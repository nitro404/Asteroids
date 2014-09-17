using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;

namespace Asteroids {

	class ExplosionSystem {

		private List<Explosion> m_explosions;
		private SpriteSheet m_explosionSprites;
		private SoundEffect m_explosionSound;

		public ExplosionSystem(SpriteSheetCollection spriteSheets, ContentManager content) {
			m_explosions = new List<Explosion>();
			if(spriteSheets != null) {
				m_explosionSprites = spriteSheets.getSpriteSheet("Explosion");
			}
			m_explosionSound = content.Load<SoundEffect>("Explosion");
		}

		// spawn an explosion based on a source object
		public void spawnExplosion(GameObject o) {
			if(o == null) { return; }
			spawnExplosion(o.position, o.velocity);
		}

		// spawn an explosion at a specific position with a corresponding velocity
		public void spawnExplosion(Vector2 position, Vector2 velocity) {
			m_explosions.Add(new Explosion(position, velocity, m_explosionSprites));
			m_explosionSound.Play();
		}

		// update the explosion (and remove explosions that are finished their animation)
		public void update(GameTime gameTime) {
			for(int i=0;i<m_explosions.Count();i++) {
				m_explosions[i].update(gameTime);
				if(m_explosions[i].finished()) {
					int lastIndex = m_explosions.Count() - 1;
					Explosion temp = m_explosions[i];
					m_explosions[i] = m_explosions[lastIndex];
					m_explosions[lastIndex] = temp;
					m_explosions.RemoveAt(lastIndex);
					i--;
				}
			}
		}

		public void draw(SpriteBatch spriteBatch) {
			for(int i=0;i<m_explosions.Count();i++) {
				m_explosions[i].draw(spriteBatch);
			}
		}

	}

}
