using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Media;
using Microsoft.Xna.Framework.Audio;

namespace Asteroids {

	enum MenuType { Main, NewGame, Options, Controls, Help }

    class Menu {

		private Asteroids m_game = null;
		private SpaceShipSystem m_players = null;
		private GameSettings m_settings = null;

		private bool m_active = true;
		private int m_xPos = 0;
		private int m_yPos = 0;
		private MenuType m_menuType = MenuType.Main;
		private int m_mainIndex = 0;
		private List<MenuItem> m_mainItems;
		private int m_newGameIndex = 0;
		private List<MenuItem> m_newGameItems;
		private int m_optionsIndex = 0;
		private List<MenuItem> m_optionsItems;
		private int m_controlsIndex = 0;
		private List<MenuItem> m_controlsItems;
		private List<MenuItem> m_helpItems;

		private bool m_backKeyPressed = false;
		private bool m_selectKeyPressed = false;
		private bool m_upKeyPressed = false;
		private bool m_downKeyPressed = false;
		private bool m_leftKeyPressed = false;
		private bool m_rightKeyPressed = false;

		private Color m_titleColour;
		private Color m_unselectedColour;
		private Color m_selectedColour;
		private Color m_arrowColour;

		private SpriteFont m_titleFont = null;
		private SpriteFont m_menuFont = null;

		private SoundEffect m_scrollSound;
		private SoundEffect m_selectSound;
		private SoundEffect m_backSound;

		// create the game menu at the default location
		public Menu(Asteroids game, SpaceShipSystem spaceShipSystem, GameSettings settings, ContentManager content) :
			this(150, 150, game, spaceShipSystem, settings, content) { }

		// create the game menu at a specific location
		public Menu(int x, int y, Asteroids game, SpaceShipSystem spaceShipSystem, GameSettings settings, ContentManager content) {
			if(content == null) { return; }

			// initialize menu colours
			m_titleColour = new Color(255, 0, 0);
			m_unselectedColour = new Color(160, 160, 160);
			m_selectedColour = new Color(255, 255, 255);
			m_arrowColour = new Color(0, 255, 0);

			// initialize menu fonts
			m_titleFont = content.Load<SpriteFont>("TitleFont");
			m_menuFont = content.Load<SpriteFont>("MenuFont");

			// initialize menu sounds
			m_scrollSound = content.Load<SoundEffect>("menu_scroll");
			m_selectSound = content.Load<SoundEffect>("menu_select");
			m_backSound = content.Load<SoundEffect>("menu_back");

			// initialize main menu
			m_mainItems = new List<MenuItem>();
			m_mainItems.Add(new MenuItem("New Game", m_menuFont, m_unselectedColour, m_selectedColour, m_arrowColour));
			m_mainItems.Add(new MenuItem("Resume Game", m_menuFont, m_unselectedColour, m_selectedColour, m_arrowColour));
			m_mainItems.Add(new MenuItem("Options", m_menuFont, m_unselectedColour, m_selectedColour, m_arrowColour));
			m_mainItems.Add(new MenuItem("Controls", m_menuFont, m_unselectedColour, m_selectedColour, m_arrowColour));
			m_mainItems.Add(new MenuItem("Help", m_menuFont, m_unselectedColour, m_selectedColour, m_arrowColour));
			m_mainItems.Add(new MenuItem("Quit", m_menuFont, m_unselectedColour, m_selectedColour, m_arrowColour));

			// initialize new game sub-menu
			m_newGameItems = new List<MenuItem>();
			m_newGameItems.Add(new MenuItem("1 Player", m_menuFont, m_unselectedColour, m_selectedColour, m_arrowColour));
			m_newGameItems.Add(new MenuItem("2 Player", m_menuFont, m_unselectedColour, m_selectedColour, m_arrowColour));
			m_newGameItems.Add(new MenuItem("3 Player", m_menuFont, m_unselectedColour, m_selectedColour, m_arrowColour));
			m_newGameItems.Add(new MenuItem("4 Player", m_menuFont, m_unselectedColour, m_selectedColour, m_arrowColour));
			m_newGameItems.Add(new MenuItem("Back", m_menuFont, m_unselectedColour, m_selectedColour, m_arrowColour));

			// intitialize options sub-menu
			m_optionsItems = new List<MenuItem>();
			m_optionsItems.Add(new MenuItem("Music", m_menuFont, m_unselectedColour, m_selectedColour, m_arrowColour));
			m_optionsItems[0].addOption("On");
			m_optionsItems[0].addOption("Off");
			m_optionsItems.Add(new MenuItem("Back", m_menuFont, m_unselectedColour, m_selectedColour, m_arrowColour));

			// initialize controls sub-menu
			m_controlsItems = new List<MenuItem>();
			m_controlsItems.Add(new MenuItem("Player 1 ", m_menuFont, m_unselectedColour, m_selectedColour, m_arrowColour));
			m_controlsItems.Add(new MenuItem("Player 2", m_menuFont, m_unselectedColour, m_selectedColour, m_arrowColour));
			m_controlsItems.Add(new MenuItem("Player 3", m_menuFont, m_unselectedColour, m_selectedColour, m_arrowColour));
			m_controlsItems.Add(new MenuItem("Player 4", m_menuFont, m_unselectedColour, m_selectedColour, m_arrowColour));
			m_controlsItems.Add(new MenuItem("Back", m_menuFont, m_unselectedColour, m_selectedColour, m_arrowColour));
			for(int i=0;i<4;i++) {
				m_controlsItems[i].addOption("WSAD");
				m_controlsItems[i].addOption("Arrows");
				m_controlsItems[i].addOption("C1");
				m_controlsItems[i].addOption("C2");
				m_controlsItems[i].addOption("C3");
				m_controlsItems[i].addOption("C4");
			}

			// initialize help sub-menu
			m_helpItems = new List<MenuItem>();
			m_helpItems.Add(new MenuItem("Destroy the Asteroids... or each other!", m_menuFont, m_unselectedColour, m_selectedColour, m_arrowColour));
			m_helpItems.Add(new MenuItem("Big Asteroids = 5 Points", m_menuFont, m_unselectedColour, m_selectedColour, m_arrowColour));
			m_helpItems.Add(new MenuItem("Small Asteroids = 10 Points", m_menuFont, m_unselectedColour, m_selectedColour, m_arrowColour));
			m_helpItems.Add(new MenuItem("Space Ships = 50 Points", m_menuFont, m_unselectedColour, m_selectedColour, m_arrowColour));
			m_helpItems.Add(new MenuItem("Back", m_menuFont, m_unselectedColour, m_selectedColour, m_arrowColour));

			// initialize menu location
			xPos = x;
			yPos = y;

			m_settings = settings;
			m_game = game;
			m_players = spaceShipSystem;

			// initialize initial menu item option selections
			m_optionsItems[0].index = (settings.musicEnabled) ? 0 : 1;
			for(int i=0;i<4;i++) {
				int itemIndex = 0;
				switch(m_settings.getInputDevice(i)) {
					case InputDevice.WSAD:
						itemIndex = 0;
						break;
					case InputDevice.Arrows:
						itemIndex = 1;
						break;
					case InputDevice.Controller1:
						itemIndex = 2;
						break;
					case InputDevice.Controller2:
						itemIndex = 3;
						break;
					case InputDevice.Controller3:
						itemIndex = 4;
						break;
					case InputDevice.Controller4:
						itemIndex = 5;
						break;
				}
				m_controlsItems[i].index = itemIndex;
			}
		}

		public int xPos {
			get { return m_xPos; }
			set { m_xPos = (value < 0) ? 0 : value;  }
		}

		public int yPos {
			get { return m_yPos; }
			set { m_yPos = (value < 0) ? 0 : value; }
		}

		public bool active {
			get { return m_active; }
			set { m_active = value; }
		}

		public void handleInput() {
			GamePadState gamePad = GamePad.GetState(PlayerIndex.One);
			KeyboardState keyboard = Keyboard.GetState();

			bool menuWasOpen = m_active;

			// activate the menu if it was not already active (or close it if appropriate)
			if(keyboard.IsKeyDown(Keys.Escape) ||
			   gamePad.IsButtonDown(Buttons.B)) {
				if(!m_backKeyPressed) {
					back();
					m_backKeyPressed = true;
				}
			}
			else { m_backKeyPressed = false; }

			// if the menu was not already open, stop (already handled the command to open it)
			if(!menuWasOpen) { return; }

			// check for menu select input
			if(keyboard.IsKeyDown(Keys.Space) ||
			   keyboard.IsKeyDown(Keys.Enter) ||
			   gamePad.IsButtonDown(Buttons.A) ||
			   gamePad.IsButtonDown(Buttons.Start) ||
			   gamePad.IsButtonDown(Buttons.LeftStick) ||
			   gamePad.IsButtonDown(Buttons.RightStick)) {
				if(!m_selectKeyPressed) {
					select();
					m_selectKeyPressed = true;
				}
			}
			else { m_selectKeyPressed = false; }

			// check for move menu selection up input
			if(keyboard.IsKeyDown(Keys.W) ||
			   keyboard.IsKeyDown(Keys.Up) ||
			   keyboard.IsKeyDown(Keys.NumPad8) ||
			   gamePad.ThumbSticks.Left.Y > 0 ||
			   gamePad.ThumbSticks.Right.Y > 0 ||
			   gamePad.IsButtonDown(Buttons.DPadUp)) {
				if(!m_upKeyPressed) {
					up();
					m_upKeyPressed = true;
				}
			}
			else { m_upKeyPressed = false; }

			// check for move menu selection down input
			if(keyboard.IsKeyDown(Keys.S) ||
			   keyboard.IsKeyDown(Keys.Down) ||
			   keyboard.IsKeyDown(Keys.NumPad2) ||
			   gamePad.ThumbSticks.Left.Y < 0 ||
			   gamePad.ThumbSticks.Right.Y < 0 ||
			   gamePad.IsButtonDown(Buttons.DPadDown)) {
				if(!m_downKeyPressed) {
					down();
					m_downKeyPressed = true;
				}
			}
			else { m_downKeyPressed = false; }

			// check for move menu selection left input
			if(keyboard.IsKeyDown(Keys.A) ||
			   keyboard.IsKeyDown(Keys.Left) ||
			   keyboard.IsKeyDown(Keys.NumPad4) ||
			   gamePad.ThumbSticks.Left.X < 0 ||
			   gamePad.ThumbSticks.Right.X < 0 ||
			   gamePad.IsButtonDown(Buttons.DPadLeft)) {
				if(!m_leftKeyPressed) {
					left();
					m_leftKeyPressed = true;
				}
			}
			else { m_leftKeyPressed = false; }

			// check for move menu selection right input
			if(keyboard.IsKeyDown(Keys.D) ||
			   keyboard.IsKeyDown(Keys.Right) ||
			   keyboard.IsKeyDown(Keys.NumPad6) ||
			   gamePad.ThumbSticks.Left.X > 0 ||
			   gamePad.ThumbSticks.Right.X > 0 ||
			   gamePad.IsButtonDown(Buttons.DPadRight)) {
				if(!m_rightKeyPressed) {
					right();
					m_rightKeyPressed = true;
				}
			}
			else { m_rightKeyPressed = false; }
		}

		// toggle the menu
		public void toggle() {
			m_active = !m_active;
		}

		// scroll the menu / active sub-menu up
		public void up() {
			m_scrollSound.Play();

			if(m_menuType == MenuType.Main) {
				if(m_mainIndex <= 0) { m_mainIndex = m_mainItems.Count() - 1; }
				else { m_mainIndex--; }
			}
			else if(m_menuType == MenuType.NewGame) {
				if(m_newGameIndex <= 0) { m_newGameIndex = m_newGameItems.Count() - 1; }
				else { m_newGameIndex--; }
			}
			else if(m_menuType == MenuType.Options) {
				if(m_optionsIndex <= 0) { m_optionsIndex = m_optionsItems.Count() - 1; }
				else { m_optionsIndex--; }
			}
			else if(m_menuType == MenuType.Controls) {
				if(m_controlsIndex <= 0) { m_controlsIndex = m_controlsItems.Count() - 1; }
				else { m_controlsIndex--; }
			}
			else if(m_menuType == MenuType.Help) { }
		}

		// scroll the menu / active sub-menu down
		public void down() {
			m_scrollSound.Play();

			if(m_menuType == MenuType.Main) {
				if(m_mainIndex >= m_mainItems.Count() - 1) { m_mainIndex = 0; }
				else { m_mainIndex++; }
			}
			else if(m_menuType == MenuType.NewGame) {
				if(m_newGameIndex >= m_newGameItems.Count() - 1) { m_newGameIndex = 0; }
				else { m_newGameIndex++; }
			}
			else if(m_menuType == MenuType.Options) {
				if(m_optionsIndex >= m_optionsItems.Count() - 1) { m_optionsIndex = 0; }
				else { m_optionsIndex++; }
			}
			else if(m_menuType == MenuType.Controls) {
				if(m_controlsIndex >= m_controlsItems.Count() - 1) { m_controlsIndex = 0; }
				else { m_controlsIndex++; }
			}
			else if(m_menuType == MenuType.Help) { }
		}

		// scroll the active menu item left
		public void left() {
			if(m_menuType == MenuType.Main) {
				if(m_mainItems[m_mainIndex].numberOfOptions <= 1) { return; }
				m_mainItems[m_mainIndex].left();
			}
			else if(m_menuType == MenuType.NewGame) {
				if(m_newGameItems[m_newGameIndex].numberOfOptions <= 1) { return; }
				m_newGameItems[m_newGameIndex].left();
			}
			else if(m_menuType == MenuType.Options) {
				if(m_optionsItems[m_optionsIndex].numberOfOptions <= 1) { return; }
				m_optionsItems[m_optionsIndex].left();

				if(m_optionsIndex == 0) {
					updateMusic();
				}
			}
			else if(m_menuType == MenuType.Controls) {
				if(m_controlsItems[m_controlsIndex].numberOfOptions <= 1) { return; }
				m_controlsItems[m_controlsIndex].left();

				if(m_controlsIndex >= 0 || m_controlsIndex < 4) { updateControls(); }
			}
			else if(m_menuType == MenuType.Help) { return; }

			m_scrollSound.Play();
		}

		// scroll the active menu item right
		public void right() {
			if(m_menuType == MenuType.Main) {
				if(m_mainItems[m_mainIndex].numberOfOptions <= 1) { return; }
				m_mainItems[m_mainIndex].right();
			}
			else if(m_menuType == MenuType.NewGame) {
				if(m_newGameItems[m_newGameIndex].numberOfOptions <= 1) { return; }
				m_newGameItems[m_newGameIndex].right();
			}
			else if(m_menuType == MenuType.Options) {
				if(m_optionsItems[m_optionsIndex].numberOfOptions <= 1) { return; }
				m_optionsItems[m_optionsIndex].right();

				if(m_optionsIndex == 0) {
					updateMusic();
				}
			}
			else if(m_menuType == MenuType.Controls) {
				if(m_controlsItems[m_controlsIndex].numberOfOptions <= 1) { return; }
				m_controlsItems[m_controlsIndex].right();

				if(m_controlsIndex >= 0 || m_controlsIndex < 4) { updateControls(); }
			}
			else if(m_menuType == MenuType.Help) { return; }

			m_scrollSound.Play();
		}

		// select the current menu item and perform a corresponding action (if appropriate)
		public void select() {
			m_selectSound.Play();

			if(m_game == null) { return; }

			if(m_menuType == MenuType.Main) {
				switch(m_mainIndex) {
					case 0: // new game
						m_menuType = MenuType.NewGame;
						break;
					case 1: // resume game
						if(m_players.numberOfSpaceShips > 0) {
							m_active = false;
							m_mainIndex = 0;
						}
						break;
					case 2: // options
						m_menuType = MenuType.Options;
						break;
					case 3: // controls
						m_menuType = MenuType.Controls;
						break;
					case 4: // help
						m_menuType = MenuType.Help;
						break;
					case 5: // quit
						m_game.Exit();
						break;
				}
			}
			else if(m_menuType == MenuType.NewGame) {
				switch(m_newGameIndex) {
					case 0: // 1 player
					case 1: // 2 players
					case 2: // 3 players
					case 3: // 4 players
						// start a new game
						m_players.numberOfSpaceShips = m_newGameIndex + 1;
						m_game.Reset();
						m_game.ResetScores();
						m_active = false;
						m_menuType = MenuType.Main;
						m_newGameIndex = 0;
						break;
					case 4: // back
						m_menuType = MenuType.Main;
						m_newGameIndex = 0;
						break;
				}
			}
			else if(m_menuType == MenuType.Options) {
				switch(m_optionsIndex) {
					case 0: // toggle music
						m_optionsItems[m_optionsIndex].right();
						updateMusic();
						break;
					case 1: // back
						m_menuType = MenuType.Main;
						m_optionsIndex = 0;
						break;
				}
			}
			else if(m_menuType == MenuType.Controls) {
				switch(m_controlsIndex) {
					case 0: // player 1
					case 1: // player 2
					case 2: // player 3
					case 3: // player 4
						m_controlsItems[m_controlsIndex].right();
						updateControls();
						break;
					case 4: // back
						m_menuType = MenuType.Main;
						m_controlsIndex = 0;
						break;
				}
			}
			else if(m_menuType == MenuType.Help) {
				m_menuType = MenuType.Main;
			}
		}

		// open the menu if it is not already open,
		// otherwise traverse back to the previous sub-menu
		// unless already at the main menu, then close the menu
		// if a game is currently active (resume the game)
		public void back() {
			m_backSound.Play();

			// activate the menu if it is not active
			if(!m_active) { m_active = true; return; }

			// close the menu (if a game is active)
			if(m_menuType == MenuType.Main) {
				if(m_players.numberOfSpaceShips > 0) {
					m_active = false;
					m_mainIndex = 0;
				}
			}
			// open the new game sub-menu
			else if(m_menuType == MenuType.NewGame) {
				m_menuType = MenuType.Main;
				m_newGameIndex = 0;
			}
			// open the options sub-menu
			else if(m_menuType == MenuType.Options) {
				m_menuType = MenuType.Main;
				m_optionsIndex = 0;
			}
			// open the controls sub-menu
			else if(m_menuType == MenuType.Controls) {
				m_menuType = MenuType.Main;
				m_controlsIndex = 0;
			}
			// open the help sub-menu
			else if(m_menuType == MenuType.Help) {
				m_menuType = MenuType.Main;
			}
		}

		// update the status of the background music on all appropriate entities
		private void updateMusic() {
			if(m_optionsItems[0].index == 0) {
				if(MediaPlayer.State == MediaState.Paused) {
					MediaPlayer.Resume();
				}
				else if(MediaPlayer.State == MediaState.Stopped) {
					MediaPlayer.Play(m_game.backgroundMusic);
				}
				m_settings.musicEnabled = true;
			}
			else if(m_optionsItems[0].index == 1) {
				MediaPlayer.Pause();
				m_settings.musicEnabled = false;
			}

		}

		// update the status of all player input devices on all appropriate entities
		private void updateControls() {
			InputDevice inputDevice = InputDevice.WSAD;
			switch(m_controlsItems[m_controlsIndex].index) {
				case 0:
					inputDevice = InputDevice.WSAD;
					break;
				case 1:
					inputDevice = InputDevice.Arrows;
					break;
				case 2:
					inputDevice = InputDevice.Controller1;
					break;
				case 3:
					inputDevice = InputDevice.Controller2;
					break;
				case 4:
					inputDevice = InputDevice.Controller3;
					break;
				case 5:
					inputDevice = InputDevice.Controller4;
					break;
			}
			m_players.getSpaceShip(m_controlsIndex).inputDevice = inputDevice;
			m_settings.setInputDevice(m_controlsIndex, inputDevice);
		}

		// render the menu
		public void draw(SpriteBatch spriteBatch) {
			if(spriteBatch == null || !m_active || m_titleFont == null || m_menuFont == null) { return; }

			int x = m_xPos, y = m_yPos;

			// get the active list of menu items and draw the appropriate menu title
			List<MenuItem> currentMenu = null;
			if(m_menuType == MenuType.Main) {
				currentMenu = m_mainItems;
				spriteBatch.DrawString(m_titleFont, "Asteroids", new Vector2(x, y), m_titleColour);
			}
			else if(m_menuType == MenuType.NewGame) {
				currentMenu = m_newGameItems;
				spriteBatch.DrawString(m_titleFont, "New Game", new Vector2(x, y), m_titleColour);
			}
			else if(m_menuType == MenuType.Options) {
				currentMenu = m_optionsItems;
				spriteBatch.DrawString(m_titleFont, "Options", new Vector2(x, y), m_titleColour);
			}
			else if(m_menuType == MenuType.Controls) {
				currentMenu = m_controlsItems;
				spriteBatch.DrawString(m_titleFont, "Controls", new Vector2(x, y), m_titleColour);
			}
			else if(m_menuType == MenuType.Help) {
				currentMenu = m_helpItems;
				spriteBatch.DrawString(m_titleFont, "Help!", new Vector2(x, y), m_titleColour);
			}

			y += m_titleFont.LineSpacing;

			if(currentMenu == null) { return; }

			bool selected;
			// loop through all menu items in the active menu and render them
			for(int i=0;i<currentMenu.Count();i++) {
				// determine if the current item is selected or not, and render it
				// with a different colour if it is
				selected =  (i == m_mainIndex && m_menuType == MenuType.Main) ||
							(i == m_newGameIndex && m_menuType == MenuType.NewGame) ||
							(i == m_optionsIndex && m_menuType == MenuType.Options) ||
							(i == m_controlsIndex && m_menuType == MenuType.Controls) ||
							(i == m_helpItems.Count() - 1 && m_menuType == MenuType.Help);
				// render the current menu item
				currentMenu[i].draw(x, y, selected, spriteBatch);
				y += m_menuFont.LineSpacing;
			}
		}

    }
}
