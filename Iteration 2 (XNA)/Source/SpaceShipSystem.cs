using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;

namespace Asteroids {

	class SpaceShipSystem {

		private int m_numberOfSpaceShips = 0;
		private const int m_maxSpaceShips = 4;
		private SpaceShip[] m_spaceShips = null;
		private SpriteSheet m_spaceShipSprites = null;
		private ProjectileSystem m_projectileSystem = null;
		private GameSettings m_settings = null;

		public SpaceShipSystem(SpriteSheetCollection spriteSheets, ProjectileSystem projectileSystem, GameSettings settings, ContentManager content) :
			this(0, spriteSheets, projectileSystem, settings, content) { }

		public SpaceShipSystem(int numberOfSpaceShips, SpriteSheetCollection spriteSheets, ProjectileSystem projectileSystem, GameSettings settings, ContentManager content) {
			this.numberOfSpaceShips = numberOfSpaceShips;
			if(spriteSheets != null) {
				m_spaceShipSprites = spriteSheets.getSpriteSheet("SpaceShip");
			}
			m_projectileSystem = projectileSystem;
			m_settings = settings;

			// initialize all space ships
			if(m_settings == null || content == null || m_spaceShipSprites == null) { return; }
			m_spaceShips = new SpaceShip[m_maxSpaceShips];
			m_spaceShips[0] = new SpaceShip(PlayerIndex.One, new Vector2(settings.screenWidth * 0.2f, settings.screenHeight * 0.2f), 135, m_spaceShipSprites, projectileSystem, settings, content);
			m_spaceShips[1] = new SpaceShip(PlayerIndex.Two, new Vector2(settings.screenWidth * 0.8f, settings.screenHeight * 0.8f), -45, m_spaceShipSprites, projectileSystem, settings, content);
			m_spaceShips[2] = new SpaceShip(PlayerIndex.Three, new Vector2(settings.screenWidth * 0.2f, settings.screenHeight * 0.8f), 45, m_spaceShipSprites, projectileSystem, settings, content);
			m_spaceShips[3] = new SpaceShip(PlayerIndex.Four, new Vector2(settings.screenWidth * 0.8f, settings.screenHeight * 0.2f), -135, m_spaceShipSprites, projectileSystem, settings, content);
		}

		// get the number of currently active space ships
		public int numberOfSpaceShips {
			get { return m_numberOfSpaceShips; }
			set { m_numberOfSpaceShips = (value < 0) ? 0 : ((value > m_maxSpaceShips) ? m_maxSpaceShips : value); }
		}

		// get the maximum number of space ships
		public int maxSpaceShips {
			get { return m_maxSpaceShips; }
		}

		// get the number of active space ships
		public int size() {
			return m_numberOfSpaceShips;
		}

		// get a space ship based on an integer index
		public SpaceShip getSpaceShip(int index) {
			if(index < 0 || index > m_maxSpaceShips) { return null; }

			return m_spaceShips[index];
		}

		// get a space ship based on a player index
		public SpaceShip getSpaceShip(PlayerIndex index) {
				 if(index == PlayerIndex.One)   { return m_spaceShips[0]; }
			else if(index == PlayerIndex.Two)   { return m_spaceShips[1]; }
			else if(index == PlayerIndex.Three) { return m_spaceShips[2]; }
			else if(index == PlayerIndex.Four)  { return m_spaceShips[3]; }
			return null;
		}

		// update each active space ship
		public void update(GameTime gameTime) {
			for(int i=0;i<m_numberOfSpaceShips;i++) {
				m_spaceShips[i].update(gameTime);
			}
		}

		// handle input for each active space ship
		public void handleInput(GameTime gameTime) {
			for(int i=0;i<m_numberOfSpaceShips;i++) {
				m_spaceShips[i].handleInput(gameTime);
			}
		}

		// render all active space ships
		public void draw(SpriteBatch spriteBatch) {
			for(int i=0;i<m_numberOfSpaceShips;i++) {
				m_spaceShips[i].draw(spriteBatch);
			}
		}

		// reset all active space ships to their default values
		public void reset() {
			for(int i=0;i<m_numberOfSpaceShips;i++) {
				m_spaceShips[i].reset();
			}
		}

	}



}
