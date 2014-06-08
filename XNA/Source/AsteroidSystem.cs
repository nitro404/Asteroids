using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Asteroids {
	
	class AsteroidSystem {

		private List<Asteroid> m_asteroids;
		private SpriteSheet m_asteroidSprites;
		private int m_maxSmallAsteroids;
		private int m_maxBigAsteroids;
		private int m_numberOfSmallAsteroids;
		private int m_numberOfBigAsteroids;
		private SpaceShipSystem m_spaceShipSystem;
		private GameSettings m_settings;

		public AsteroidSystem(SpriteSheetCollection spriteSheets, SpaceShipSystem spaceShipSystem, GameSettings settings) {
			m_asteroids = new List<Asteroid>();
			if(spriteSheets != null) {
				m_asteroidSprites = spriteSheets.getSpriteSheet("Asteroids");
			}
			m_spaceShipSystem = spaceShipSystem;
			m_settings = settings;

			m_maxSmallAsteroids = 12;
			m_maxBigAsteroids = 10;
		}

		// get the number of asteroids in the collection
		public int size() {
			return m_asteroids.Count();
		}

		// get an asteroid at a specific index
		public Asteroid getAsteroid(int index) {
			if(index < 0 || index >= m_asteroids.Count()) { return null; }

			return m_asteroids[index];
		}

		// spawn a random asteroid at a random location with random attributes
		public void spawnAsteroid() {
			int asteroidIndex;
			bool bigAsteroid;
			Random rand = new Random();
			if(rand.Next(0, 99) < 30) {
				// spawn small asteroid (30% chance)
				asteroidIndex = rand.Next(0, 4) + 2;
				bigAsteroid = false;
			}
			else {
				// spawn big asteroid (70% chance)
				asteroidIndex = rand.Next(0, 2) % 2;
				bigAsteroid = true;
			}

			// if there are too many asteroids of this type, do not spawn it
			if(bigAsteroid && m_numberOfBigAsteroids >= m_maxBigAsteroids) { return; }
			if(!bigAsteroid && m_numberOfSmallAsteroids >= m_maxSmallAsteroids) { return; }

			bool isInsideOfAsteroid;
			bool isTooCloseToShip;
			Asteroid newAsteroid = new Asteroid(m_asteroidSprites.getSprite(asteroidIndex), bigAsteroid, m_settings);
			do {
				// make sure that the new asteroid is not too close to a space ship
				isTooCloseToShip = false;
				for(int i=0;i<m_spaceShipSystem.size();i++) {
					if(m_spaceShipSystem.getSpaceShip(i).checkExtendedCollision(newAsteroid)) {
						isTooCloseToShip = true;
					}
				}

				// also make sure that the asteroid is not stuck inside of another asteroid
				isInsideOfAsteroid = false;
				if(!isTooCloseToShip) {
					for(int i=0;i<m_asteroids.Count();i++) {
						if(m_asteroids[i].checkCollision(newAsteroid)) {
							isInsideOfAsteroid = true;
						}
					}
				}

				// if it is too close to a ship or inside of another asteroid, then re-randomize its position until it isn't
				if(isTooCloseToShip || isInsideOfAsteroid) {
					newAsteroid.randomizePosition();
				}
			} while(isTooCloseToShip || isInsideOfAsteroid);

			// store the asteroid
			if(newAsteroid.bigAsteroid) { m_numberOfBigAsteroids++; } else { m_numberOfSmallAsteroids++; }
			m_asteroids.Add(newAsteroid);
		}

		public void spawnAsteroidCluster(GameObject o) {
			if(o == null || m_numberOfSmallAsteroids >= m_maxSmallAsteroids) { return; }

			Random rand = new Random();

			// randomly choose how many small asteroids to spawn from a bigger asteroid
			int clusterSize = 0;
			int clusterSeed = rand.Next(0, 100);
				 if(clusterSeed <  34) { clusterSize = 0; } // 34% chance no asteroids
			else if(clusterSeed <  76) { clusterSize = 1; } // 42% chance 1 asteroid
			else if(clusterSeed <  90) { clusterSize = 2; } // 14% chance 2 asteroids
			else if(clusterSeed <  96) { clusterSize = 3; } //  6% chance 3 asteroids
			else if(clusterSeed < 100) { clusterSize = 4; } //  4% chance 4 asteroids

			// create the corresponding number of mini-asteroids, and set their appropriate locations and directions
			// by rotating a pair of x/y co-ordinates around the origin of the original asteroid, randomized at equal
			// intervals and set their velocities so they are moving away from the origin of the original asteroid
			float angle = (float) (rand.NextDouble() * 359.0f);
			float angleIncrement = (360.0f / clusterSize);
			Asteroid newAsteroid;
			for(int i=0;i<clusterSize;i++) {
				newAsteroid = new Asteroid(m_asteroidSprites.getSprite(rand.Next(0, 4) + 2), false, m_settings);

				// calculate the velocities of the new asteroid
				float minVelocity = (float) (rand.NextDouble() * 0.3f) + 0.007f;
				float maxVelocity = (float) (rand.NextDouble() * 2.5f) + 0.8f;
				float xVelocity = (float) ( (((rand.Next(0, 2) % 2) == 0) ? 1 : -1) * (rand.NextDouble() * (maxVelocity - minVelocity) + minVelocity) );
				float yVelocity = (float) ( (((rand.Next(0, 2) % 2) == 0) ? 1 : -1) * (rand.NextDouble() * (maxVelocity - minVelocity) + minVelocity) );

				// set the velocities and locations of the new asteroid
				newAsteroid.position = new Vector2((float) (o.position.X + (o.offset.X * Math.Cos(MathHelper.ToRadians(angle)))), (float) (o.position.Y + (o.offset.Y * Math.Sin(MathHelper.ToRadians(angle)))));
				newAsteroid.velocity = new Vector2((float) (xVelocity * Math.Cos(MathHelper.ToRadians(angle))), (float) (yVelocity * Math.Sin(MathHelper.ToRadians(angle))));

				// store the asteroid
				if(newAsteroid.bigAsteroid) { m_numberOfBigAsteroids++; } else { m_numberOfSmallAsteroids++; }
				m_asteroids.Add(newAsteroid);

				// increment to the next projection angle
				angle += angleIncrement;
			}
		}

		// remove an already existing asteroid
		public bool removeAsteroid(Asteroid a) {
			if(a == null) { return false; }
			return removeAsteroid(m_asteroids.IndexOf(a));
		}

		// remove an asteroid at a specific index
		public bool removeAsteroid(int index) {
			// validate the index
			if(index < 0 || index >= m_asteroids.Count()) { return false; }

			// if there is only one asteroid, remove it
			if(m_asteroids.Count() == 1) {
				if(m_asteroids[0].bigAsteroid) { m_numberOfBigAsteroids--; } else { m_numberOfSmallAsteroids--; }
				m_asteroids.RemoveAt(index);
			}
			// if there is more than one asteroid, swap it with the last element for efficiency, and remove it
			else {
				int lastIndex = m_asteroids.Count() - 1;
				Asteroid temp = m_asteroids[index];
				m_asteroids[index] = m_asteroids[lastIndex];
				m_asteroids[lastIndex] = temp;
				if(temp.bigAsteroid) { m_numberOfBigAsteroids--; } else { m_numberOfSmallAsteroids--; }
				m_asteroids.RemoveAt(lastIndex);
			}
			return true;
		}

		public void update(GameTime gameTime) {
			// update all asteroids
			for(int i=0;i<m_asteroids.Count();i++) {
				m_asteroids[i].update(gameTime);
			}

			// spawn new asteroids if there are not enough present
			while(m_numberOfBigAsteroids < m_maxBigAsteroids && m_asteroids.Count() < 20) {
				spawnAsteroid();
			}
		}

		public void draw(SpriteBatch spriteBatch) {
			// render all asteroids
			for(int i=0;i<m_asteroids.Count();i++) {
				m_asteroids[i].draw(spriteBatch);
			}
		}

		public void reset() {
			// remove all asteroids
			m_asteroids.Clear();
			m_numberOfSmallAsteroids = 0;
			m_numberOfBigAsteroids = 0;
		}

	}

}
