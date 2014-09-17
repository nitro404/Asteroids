using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Asteroids {

	class MenuItem {
	
		private string m_text = null;
		private List<string> m_options = null;
		private int m_index = 0;
		private SpriteFont m_font;
		private Color m_unselectedColour;
		private Color m_selectedColour;
		private Color m_arrowColour;
		private static Color m_arrowColour2 = new Color(255, 0, 0);
		private static int m_optionSpacing = 10;
		private static int m_arrowSpacing = 20;

		// create a menu item with no options
		public MenuItem(string text, SpriteFont font, Color unselectedColour, Color selectedColour, Color arrowColour) {
			m_text = text;
			m_options = new List<string>();
			m_font = font;
			m_unselectedColour = unselectedColour;
			m_selectedColour = selectedColour;
			m_arrowColour = arrowColour;
		}

		// create a menu item with a collection of options from an array
		public MenuItem(string text, string[] options, SpriteFont font, Color unselectedColour, Color selectedColour, Color arrowColour) {
			m_text = text;
			m_options = new List<string>();
			if(options == null) { return; }
			for(int i=0;i<options.Length;i++) {
				addOption(options[i]);
			}
			m_font = font;
			m_unselectedColour = unselectedColour;
			m_selectedColour = selectedColour;
			m_arrowColour = arrowColour;
		}

		// create a menu item with a collection of options from a list
		public MenuItem(string text, List<string> options, SpriteFont font, Color unselectedColour, Color selectedColour, Color arrowColour) {
			m_text = text;
			m_options = new List<string>();
			if(options == null) { return; }
			for(int i=0;i<options.Count();i++) {
				addOption(options[i]);
			}
			m_font = font;
			m_unselectedColour = unselectedColour;
			m_selectedColour = selectedColour;
			m_arrowColour = arrowColour;
		}

		public bool addOption(string option) {
			if(option == null || m_options.Contains(option)) { return false; }
			m_options.Add(option);
			return true;
		}

		public string text {
			get { return m_text; }
			set { m_text = (value == null) ? "" : value; }
		}

		public int numberOfOptions {
			get { return m_options.Count(); }
		}

		public int index {
			get { return m_index; }
			set { if(m_index >= 0 && m_index < m_options.Count()) { m_index = value; } }
		}

		public string getOption(int index) {
			if(index < 0 || index >= m_options.Count()) { return null; }
			return m_options[index];
		}

		public int getSelectionIndex() {
			return m_index;
		}

		public void left() {
			if(m_index <= 0) { m_index = m_options.Count() - 1; }
			else { m_index--; }
		}

		public void right() {
			if(m_index >= m_options.Count() - 1) { m_index = 0; }
			else { m_index++; }
		}

		// render the menu item
		public void draw(int x, int y, bool selected, SpriteBatch spriteBatch) {
			// render the front green selection arrow (if selected)
			if(selected) { spriteBatch.DrawString(m_font, ">", new Vector2(x, y), m_arrowColour); }
			x += m_arrowSpacing;

			// render the item's text
			if(m_text.Length > 0) {
				spriteBatch.DrawString(m_font, m_text, new Vector2(x, y), (selected) ? m_selectedColour : m_unselectedColour);
				x += (int) m_font.MeasureString(m_text).X;
			}
			// render all of the menu item's options
			for(int i=0;i<m_options.Count();i++) {
				x += m_optionSpacing;
				// render the red selection arrow if the current option is selected / enabled
				if(m_index == i) { spriteBatch.DrawString(m_font, ">", new Vector2(x, y), m_arrowColour2); }
				x += m_arrowSpacing;
				// render the option's text
				spriteBatch.DrawString(m_font, m_options[i], new Vector2(x, y), (m_index == i) ? m_selectedColour : m_unselectedColour);
				x += (int) m_font.MeasureString(m_options[i]).X;
			}
		}

	}

}
