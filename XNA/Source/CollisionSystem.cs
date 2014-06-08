using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Asteroids {

	class CollisionSystem {

		private ProjectileSystem m_projectileSystem;
		private SpaceShipSystem m_spaceShipSystem;
		private AsteroidSystem m_asteroidSystem;
		private ExplosionSystem m_explosionSystem;
		private ScoreSystem m_scoreSystem;

		public CollisionSystem(ProjectileSystem projectileSystem, SpaceShipSystem spaceShipSystem, AsteroidSystem asteroidSystem, ExplosionSystem explosionSystem, ScoreSystem scoreSystem) {
			m_projectileSystem = projectileSystem;
			m_spaceShipSystem = spaceShipSystem;
			m_asteroidSystem = asteroidSystem;
			m_explosionSystem = explosionSystem;
			m_scoreSystem = scoreSystem;
		}

		public void handleCollisions() {
			if(m_projectileSystem == null ||
			   m_spaceShipSystem == null ||
			   m_asteroidSystem == null ||
			   m_explosionSystem == null ||
			   m_scoreSystem == null) {
				return;
			}

			// remove any collisions that have been handled and are no longer in collision
			for(int i=0;i<m_asteroidSystem.size();i++) {
				Asteroid a1 = m_asteroidSystem.getAsteroid(i);
				for(int j=0;j<m_asteroidSystem.size();j++) {
					Asteroid a2 = m_asteroidSystem.getAsteroid(j);
					if(i != j &&
					   (a1.isCollidingWith(a2) && !a1.checkCollision(a2)) ||
					   (a2.isCollidingWith(a1) && !a2.checkCollision(a1))) {
						a1.removeCollision(a2);
						a2.removeCollision(a1);
					}
				}
			}

			// check asteroid > asteroid collision
			for(int i=0;i<m_asteroidSystem.size();i++) {
				for(int j=i+1;j<m_asteroidSystem.size();j++) {
					if(i != j && m_asteroidSystem.getAsteroid(i).checkCollision(m_asteroidSystem.getAsteroid(j))) {
						handleCollision(m_asteroidSystem.getAsteroid(i), m_asteroidSystem.getAsteroid(j));
					}
				}

				// check projectile > asteroid collision
				for(int j=0;j<m_projectileSystem.size();j++) {
					if(m_projectileSystem.getProjectile(j).checkCollision(m_asteroidSystem.getAsteroid(i))) {
						// [potentially] create a cluster of smaller asteroids if this was a big asteroid
						m_scoreSystem.addPoints(m_projectileSystem.getProjectile(j).getProjectileSource(), (m_asteroidSystem.getAsteroid(i).bigAsteroid) ? ScoreType.BigAsteroid : ScoreType.SmallAsteroid);

						if(m_asteroidSystem.getAsteroid(i).bigAsteroid) {
							m_asteroidSystem.spawnAsteroidCluster(m_asteroidSystem.getAsteroid(i));
						}

						m_explosionSystem.spawnExplosion(m_asteroidSystem.getAsteroid(i));

						clearCollisions(m_asteroidSystem.getAsteroid(i));

						m_asteroidSystem.removeAsteroid(i);
						m_projectileSystem.removeProjectile(j);

						i--;
						j--;

						break;
					}
				}
			}

			// check ship > ship collision
			for(int i=0;i<m_spaceShipSystem.size();i++) {
				for(int j=i+1;j<m_spaceShipSystem.size();j++) {
					if(i != j && m_spaceShipSystem.getSpaceShip(i).checkCollision(m_spaceShipSystem.getSpaceShip(j))) {
						m_explosionSystem.spawnExplosion(m_spaceShipSystem.getSpaceShip(i));
						m_explosionSystem.spawnExplosion(m_spaceShipSystem.getSpaceShip(j));

						m_spaceShipSystem.getSpaceShip(i).reset();
						m_spaceShipSystem.getSpaceShip(j).reset();
					}
				}

				// check ship > asteroid collision
				for(int j=0;j<m_asteroidSystem.size();j++) {
					if(m_spaceShipSystem.getSpaceShip(i).checkCollision(m_asteroidSystem.getAsteroid(j))) {
						m_explosionSystem.spawnExplosion(m_spaceShipSystem.getSpaceShip(i));

						m_spaceShipSystem.getSpaceShip(i).reset();

						clearCollisions(m_asteroidSystem.getAsteroid(j));

						m_asteroidSystem.removeAsteroid(j);
						j--;
					}
				}

				// check projectile > ship collision
				for(int j=0;j<m_projectileSystem.size();j++) {
					if(!m_projectileSystem.getProjectile(j).getProjectileSource().Equals(m_spaceShipSystem.getSpaceShip(i)) &&
					   m_projectileSystem.getProjectile(j).checkCollision(m_spaceShipSystem.getSpaceShip(i))) {
						m_scoreSystem.addPoints(m_projectileSystem.getProjectile(j).getProjectileSource(), ScoreType.SpaceShip);

						m_explosionSystem.spawnExplosion(m_spaceShipSystem.getSpaceShip(i));
						m_spaceShipSystem.getSpaceShip(i).reset();

						m_projectileSystem.removeProjectile(j);
						j--;
					}
				}
			}

		}

		// clear all collisions associated with the specified asteroid
		private void clearCollisions(Asteroid a) {
			if(a == null) { return; }

			for(int i=0;i<m_asteroidSystem.size();i++) {
				Asteroid a2 = m_asteroidSystem.getAsteroid(i);
				if(a2.isCollidingWith(a)) {
					a2.removeCollision(a);
					a.removeCollision(a2);
				}
			}
		}

		// handle a collision between two asteroids
		private void handleCollision(Asteroid a1, Asteroid a2) {
			if(a1 == a2) { return; }
			if(a1.isCollidingWith(a2) || a2.isCollidingWith(a1)) { return; }

			a1.addCollision(a2);
			a2.addCollision(a1);

			double v = a1.speed;

			double dx = Math.Abs(a2.x - a1.x);
			double dy = Math.Abs(a2.y - a1.y);
			double d = Math.Sqrt((dx * dx) + (dy * dy));

			if(d == 0)
				return;

			double angle_b = Math.Asin(dy / d);
			double angle_d = Math.Asin(Math.Abs(a1.velocity.X) / v);
			double angle_a = (Math.PI / 2.0f) - angle_b - angle_d;
			double angle_c = angle_b - angle_a;

			double v1 = v * Math.Abs(Math.Sin(angle_a));
			double v2 = v * Math.Abs(Math.Cos(angle_a));

			double v1x = v1 * Math.Abs(Math.Cos(angle_c));
			double v1y = v1 * Math.Abs(Math.Sin(angle_c));
			double v2x = v2 * Math.Abs(Math.Cos(angle_b));
			double v2y = v2 * Math.Abs(Math.Sin(angle_b));

			if(a1.velocity.X > 0) {
				if(a1.x < a2.x)
					v1x = -v1x;
				else
					v2x = -v2x;
			}
			else {
				if(a1.x > a2.x)
					v2x = -v2x;
				else
					v1x = -v1x;
			}

			if(a1.velocity.Y > 0) {
				if(a1.y < a2.y)
					v1y = -v1y;
				else
					v2y = -v2y;
			}
			else {
				if(a1.y > a2.y)
					v2y = -v2y;
				else
					v1y = -v1y;
			}

			if(double.IsNaN(v1x) || double.IsNaN(v1y) || double.IsNaN(v2x) || double.IsNaN(v2y)) { return; }

			// update the asteroids with their new velocities
			a1.velocity = new Vector2((float) v1x, (float) v1y);
			a2.velocity = new Vector2((float) v2x, (float) v2y);
		}

	}

}
