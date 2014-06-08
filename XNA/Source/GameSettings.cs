using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Asteroids {

	class GameSettings {

		private static string m_defaultFile = "Content/settings.ini";

		private int m_screenWidth;
		private int m_screenHeight;
		private bool m_fullScreen;
		private bool m_musicEnabled;
		private string m_spriteSheetFileName;
		private InputDevice[] m_playerInputDevices;

		private VariableSystem m_variables = null;

		public GameSettings() {
			// initialize game settings to default values
			m_spriteSheetFileName = m_defaultFile;
			m_screenWidth = 1024;
			m_screenHeight = 768;
			m_fullScreen = false;
			m_musicEnabled = true;
			m_playerInputDevices = new InputDevice[4];
			m_playerInputDevices[0] = InputDevice.Controller1;
			m_playerInputDevices[1] = InputDevice.Controller2;
			m_playerInputDevices[2] = InputDevice.Controller3;
			m_playerInputDevices[3] = InputDevice.Controller4;
		}

		public static string defaultFile {
			get { return m_defaultFile; }
		}

		public int screenWidth {
			get { return m_screenWidth; }
			set { m_screenWidth = (value < 800) ? 800 : ((value > 4096) ? 4096 : value); }
		}

		public int screenHeight {
			get { return m_screenHeight; }
			set { m_screenHeight = (value < 600) ? 600 : ((value > 2160) ? 2160 : value); }
		}

		public bool fullScreen {
			get { return m_fullScreen; }
			set { m_fullScreen = value; }
		}

		public bool musicEnabled {
			get { return m_musicEnabled; }
			set { m_musicEnabled = value; }
		}

		public string spriteSheetFileName {
			get { return m_spriteSheetFileName; }
			set { if(value != null && value.Trim().Length != 0) { m_spriteSheetFileName = value; } }
		}

		public InputDevice player1InputDevice {
			get { return m_playerInputDevices[0]; }
			set { m_playerInputDevices[0] = value; }
		}

		public InputDevice player2InputDevice {
			get { return m_playerInputDevices[1]; }
			set { m_playerInputDevices[1] = value; }
		}

		public InputDevice player3InputDevice {
			get { return m_playerInputDevices[2]; }
			set { m_playerInputDevices[2] = value; }
		}

		public InputDevice player4InputDevice {
			get { return m_playerInputDevices[3]; }
			set { m_playerInputDevices[3] = value; }
		}

		public InputDevice getInputDevice(PlayerIndex playerNumber) {
				 if(playerNumber == PlayerIndex.One)   { return m_playerInputDevices[0]; }
			else if(playerNumber == PlayerIndex.Two)   { return m_playerInputDevices[1]; }
			else if(playerNumber == PlayerIndex.Three) { return m_playerInputDevices[2]; }
			else if(playerNumber == PlayerIndex.Four)  { return m_playerInputDevices[3]; }
			return InputDevice.WSAD;
		}

		public InputDevice getInputDevice(int playerNumber) {
			if(playerNumber < 0 || playerNumber >= 4) { return InputDevice.WSAD; }
			return m_playerInputDevices[playerNumber];
		}

		public void setInputDevice(PlayerIndex playerNumber, InputDevice inputDevice) {
				 if(playerNumber == PlayerIndex.One)   { m_playerInputDevices[0] = inputDevice; }
			else if(playerNumber == PlayerIndex.Two)   { m_playerInputDevices[1] = inputDevice; }
			else if(playerNumber == PlayerIndex.Three) { m_playerInputDevices[2] = inputDevice; }
			else if(playerNumber == PlayerIndex.Four)  { m_playerInputDevices[3] = inputDevice; }
		}

		public void setInputDevice(int playerNumber, InputDevice inputDevice) {
			if(playerNumber < 0 || playerNumber >= 4) { return; }
			m_playerInputDevices[playerNumber] = inputDevice;
		}

		public static InputDevice parseInputDeviceFrom(string data) {
			if(data != null) {
					 if(data.Equals("WSAD", StringComparison.OrdinalIgnoreCase))         { return InputDevice.WSAD; }
				else if(data.Equals("Arrows", StringComparison.OrdinalIgnoreCase))       { return InputDevice.Arrows; }
				else if(data.Equals("Controller 1", StringComparison.OrdinalIgnoreCase)) { return InputDevice.Controller1; }
				else if(data.Equals("Controller 2", StringComparison.OrdinalIgnoreCase)) { return InputDevice.Controller2; }
				else if(data.Equals("Controller 3", StringComparison.OrdinalIgnoreCase)) { return InputDevice.Controller3; }
				else if(data.Equals("Controller 4", StringComparison.OrdinalIgnoreCase)) { return InputDevice.Controller4; }
			}
			return InputDevice.WSAD;
		}

		public static string inputDeviceToString(InputDevice inputDevice) {
			switch(inputDevice) {
				case InputDevice.WSAD:
					return "WSAD";
				case InputDevice.Arrows:
					return "Arrows";
				case InputDevice.Controller1:
					return "Controller 1";
				case InputDevice.Controller2:
					return "Controller 2";
				case InputDevice.Controller3:
					return "Controller 3";
				case InputDevice.Controller4:
					return "Controller 4";
			}
			return "";
		}

		// load game settings from a specified file name
		public bool loadFrom(string fileName) {
			// use a variable system to parse the settings file
			VariableSystem newVariables = VariableSystem.readFrom(fileName);
			if(newVariables == null) { return false; }

			m_variables = newVariables;

			// create local variables instantiated with data parsed from the variable system
			try { screenWidth = int.Parse(m_variables.getValue("Screen Width", "Settings")); } catch(Exception) { }
			try { screenHeight = int.Parse(m_variables.getValue("Screen Height", "Settings")); } catch(Exception) { }
			try { fullScreen = bool.Parse(m_variables.getValue("Fullscreen", "Settings")); } catch(Exception) { }
			try { musicEnabled = bool.Parse(m_variables.getValue("Music", "Settings")); } catch(Exception) { }
			spriteSheetFileName = m_variables.getValue("SpriteSheet File", "Paths");
			m_playerInputDevices[0] = parseInputDeviceFrom(m_variables.getValue("Player 1", "Controls"));
			m_playerInputDevices[1] = parseInputDeviceFrom(m_variables.getValue("Player 2", "Controls"));
			m_playerInputDevices[2] = parseInputDeviceFrom(m_variables.getValue("Player 3", "Controls"));
			m_playerInputDevices[3] = parseInputDeviceFrom(m_variables.getValue("Player 4", "Controls"));

			return true;
		}

		public bool saveTo(string fileName) {
			// update the variable system with the new game settings values
			m_variables.setValue("Screen Width", m_screenWidth.ToString(), "Settings");
			m_variables.setValue("Screen Height", m_screenHeight.ToString(), "Settings");
			m_variables.setValue("Fullscreen", m_fullScreen.ToString().ToLower(), "Settings");
			m_variables.setValue("Music", m_musicEnabled.ToString().ToLower(), "Settings");
			m_variables.setValue("SpriteSheet File", m_spriteSheetFileName, "Paths");
			m_variables.setValue("Player 1", inputDeviceToString(m_playerInputDevices[0]), "Controls");
			m_variables.setValue("Player 2", inputDeviceToString(m_playerInputDevices[1]), "Controls");
			m_variables.setValue("Player 3", inputDeviceToString(m_playerInputDevices[2]), "Controls");
			m_variables.setValue("Player 4", inputDeviceToString(m_playerInputDevices[3]), "Controls");

			// group the variables by categories
			m_variables.sort();

			// update the settings file with the changes
			return m_variables.writeTo(fileName);
		}

	}

}
