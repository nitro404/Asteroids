using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;

namespace Asteroids {
	
	class ProjectileSystem {

		private List<Projectile> m_projectiles = null;
		private SoundEffect m_laserSound = null;
		private GameSettings m_settings = null;
		private SpriteSheet m_projectileSprites = null;
		private SpriteAnimation[] m_projectileAnimations = null;

		public ProjectileSystem(SpriteSheetCollection spriteSheets, GameSettings settings, ContentManager content) {
			m_projectiles = new List<Projectile>();

			// load the projectile sprites and create an animation from them
			if(spriteSheets != null) {
				m_projectileSprites = spriteSheets.getSpriteSheet("Projectiles");
			}

			if(m_projectileSprites != null) {
				m_projectileAnimations = new SpriteAnimation[4];
				
				for(int i=0;i<4;i++) {
					m_projectileAnimations[i] = new SpriteAnimation(0.18f, SpriteAnimationType.Loop);
					m_projectileAnimations[i].addSprite(m_projectileSprites.getSprite(i * 2));
					m_projectileAnimations[i].addSprite(m_projectileSprites.getSprite(i * 2 + 1));
				}
			}

			// load the laser sound
			if(content != null) {
				m_laserSound = content.Load<SoundEffect>("Laser");
			}

			m_settings = settings;
		}

		// return the number of projectiles
		public int size() {
			return m_projectiles.Count();
		}

		// return a specific projectile
		public Projectile getProjectile(int index) {
			if(index < 0 || index >= m_projectiles.Count()) { return null; }

			return m_projectiles[index];
		}

		// spawn a projectile at a position with a rotation from a specific space ship
		public void spawnProjectile(Vector2 position, float rotation, SpaceShip spaceShip) {
			if(spaceShip == null) { return; }

			// get the colour of the projectile
			SpriteAnimation projectileAnimation = null;
				 if(spaceShip.colour == SpaceShipColour.Red)    { projectileAnimation = m_projectileAnimations[0]; }
			else if(spaceShip.colour == SpaceShipColour.Blue)   { projectileAnimation = m_projectileAnimations[1]; }
			else if(spaceShip.colour == SpaceShipColour.Green)  { projectileAnimation = m_projectileAnimations[2]; }
			else if(spaceShip.colour == SpaceShipColour.Yellow) { projectileAnimation = m_projectileAnimations[3]; }

			// create the projectile and store it
			m_projectiles.Add(new Projectile(position, rotation, projectileAnimation, spaceShip, m_settings));
			m_laserSound.Play();
		}

		// remove a projectile from the collection
		public bool removeProjectile(Projectile p) {
			if(p == null) { return false; }
			return removeProjectile(m_projectiles.IndexOf(p));
		}

		// remove a projectile at a specific index from the collection
		public bool removeProjectile(int index) {
			if(index < 0 || index >= m_projectiles.Count()) { return false; }
			if(m_projectiles.Count() == 1) {
				m_projectiles.RemoveAt(index);
			}
			else {
				int lastIndex = m_projectiles.Count() - 1;
				Projectile temp = m_projectiles[index];
				m_projectiles[index] = m_projectiles[lastIndex];
				m_projectiles[lastIndex] = temp;
				m_projectiles.RemoveAt(lastIndex);
			}
			return true;
		}

		// update the projectile system
		public void update(GameTime gameTime) {
			// update all of the projectile animations
			for(int i=0;i<4;i++) {
				m_projectileAnimations[i].update(gameTime);
			}
			
			// update all of the projectiles
			for(int i=0;i<m_projectiles.Count();i++) {
				m_projectiles[i].update(gameTime);

				// check for projectiles out of bounds, and remove them
				if(m_projectiles[i].outOfBounds()) {
					int lastIndex = m_projectiles.Count() - 1;
					Projectile temp = m_projectiles[i];
					m_projectiles[i] = m_projectiles[lastIndex];
					m_projectiles[lastIndex] = temp;
					m_projectiles.RemoveAt(lastIndex);
					i--;
				}
			}
		}

		public void draw(SpriteBatch spriteBatch) {
			for(int i=0;i<m_projectiles.Count();i++) {
				m_projectiles[i].draw(spriteBatch);
			}
		}

		public void reset() {
			m_projectiles.Clear();
		}

	}

}
