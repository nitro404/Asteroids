using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;

namespace Asteroids {

	enum ScoreType { SmallAsteroid, BigAsteroid, SpaceShip }

	class ScoreSystem {

		private long[] m_score = null;
		private SpaceShipSystem m_players = null;
		private SpriteFont m_scoreFont = null;
		private Color m_colourRed;
		private Color m_colourBlue;
		private Color m_colourGreen;
		private Color m_colourYellow;
		private GameSettings m_settings = null;

		public ScoreSystem(SpaceShipSystem spaceShipSystem, ContentManager content, GameSettings settings) {
			if(spaceShipSystem == null) { return; }

			m_players = spaceShipSystem;
			m_settings = settings;

			if(spaceShipSystem == null) { return; }

			// initialize the player scores
			m_score = new long[m_players.maxSpaceShips];
			for(int i=0;i<m_score.Length;i++) {
				m_score[i] = 0;
			}

			// initialize the score colours
			m_colourRed = new Color(255, 0, 0);
			m_colourBlue = new Color(0, 0, 255);
			m_colourGreen = new Color(0, 255, 0);
			m_colourYellow = new Color(255, 255, 0);

			if(content == null) { return; }

			// load the score font
			m_scoreFont = content.Load<SpriteFont>("ScoreFont");
		}

		// add a corresponding number of points to a player's score (based on space ship object)
		public void addPoints(SpaceShip player, ScoreType scoreType) {
			if(player == null) { return; }
			addPoints(player.playerNumber, scoreType);
		}

		// add a corresponding number of points to a player's score (based on player index)
		public void addPoints(PlayerIndex playerNumber, ScoreType scoreType) {
			if(m_players == null) { return; }

			int score = 0;
			switch(scoreType) {
				case ScoreType.BigAsteroid: // add 5 points for big asteroids
					score = 5;
					break;
				case ScoreType.SmallAsteroid: // add 10 points for small asteroids
					score = 10;
					break;
				case ScoreType.SpaceShip: // add 50 points for space ships (enemy players)
					score = 50;
					break;
			}

			// add the points to the appropriate player
			switch(playerNumber) {
				case PlayerIndex.One:
					m_score[0] += score;
					break;
				case PlayerIndex.Two:
					m_score[1] += score;
					break;
				case PlayerIndex.Three:
					m_score[2] += score;
					break;
				case PlayerIndex.Four:
					m_score[3] += score;
					break;
			}
		}

		// get the score colour based on the space ship colour
		public Color getColour(SpaceShip spaceShip) {
			if(spaceShip == null) { return Color.White; }
			switch(spaceShip.colour) {
				case SpaceShipColour.Red:
					return m_colourRed;
				case SpaceShipColour.Blue:
					return m_colourBlue;
				case SpaceShipColour.Green:
					return m_colourGreen;
				case SpaceShipColour.Yellow:
					return m_colourYellow;
			}
			return Color.White;
		}

		// reset the scores
		public void reset() {
			if(m_players == null) { return; }

			for(int i=0;i<m_players.maxSpaceShips;i++) {
				m_score[i] = 0;
			}
		}

		// draw the scores to the top of the screen
		public void draw(SpriteBatch spriteBatch) {
			if(m_players == null || m_settings == null || spriteBatch == null) { return; }

			else if(m_players.numberOfSpaceShips == 0) { return; }
			else if(m_players.numberOfSpaceShips == 1) {
				spriteBatch.DrawString(m_scoreFont, m_score[0].ToString(), new Vector2(m_settings.screenWidth / 2, 0), getColour(m_players.getSpaceShip(0)));
			}
			else if(m_players.numberOfSpaceShips == 2) {
				spriteBatch.DrawString(m_scoreFont, m_score[0].ToString(), new Vector2(m_settings.screenWidth / 3, 0), getColour(m_players.getSpaceShip(0)));
				spriteBatch.DrawString(m_scoreFont, m_score[1].ToString(), new Vector2(2 * (m_settings.screenWidth / 3), 0), getColour(m_players.getSpaceShip(1)));
			}
			else if(m_players.numberOfSpaceShips == 3) {
				spriteBatch.DrawString(m_scoreFont, m_score[0].ToString(), new Vector2(m_settings.screenWidth / 4, 0), getColour(m_players.getSpaceShip(0)));
				spriteBatch.DrawString(m_scoreFont, m_score[1].ToString(), new Vector2(2 * (m_settings.screenWidth / 4), 0), getColour(m_players.getSpaceShip(1)));
				spriteBatch.DrawString(m_scoreFont, m_score[2].ToString(), new Vector2(3 * (m_settings.screenWidth / 4), 0), getColour(m_players.getSpaceShip(2)));
			}
			else if(m_players.numberOfSpaceShips == 4) {
				spriteBatch.DrawString(m_scoreFont, m_score[0].ToString(), new Vector2(m_settings.screenWidth / 5, 0), getColour(m_players.getSpaceShip(0)));
				spriteBatch.DrawString(m_scoreFont, m_score[1].ToString(), new Vector2(2 * (m_settings.screenWidth / 5), 0), getColour(m_players.getSpaceShip(1)));
				spriteBatch.DrawString(m_scoreFont, m_score[2].ToString(), new Vector2(3 * (m_settings.screenWidth / 5), 0), getColour(m_players.getSpaceShip(2)));
				spriteBatch.DrawString(m_scoreFont, m_score[3].ToString(), new Vector2(4 * (m_settings.screenWidth / 5), 0), getColour(m_players.getSpaceShip(3)));
			}

		}

	}

}
