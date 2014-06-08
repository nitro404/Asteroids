using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using Microsoft.Xna.Framework.Content;

namespace Asteroids {

	class SpriteSheetCollection {

		List<SpriteSheet> m_spriteSheets;

		public SpriteSheetCollection() {
			m_spriteSheets = new List<SpriteSheet>();
		}

		public int size() {
			return m_spriteSheets.Count();
		}

		// obtain a sprite sheet based on its index within the collection of sprite sheets
		public SpriteSheet getSpriteSheet(int index) {
			return (index < 0 || index >= m_spriteSheets.Count()) ? null : m_spriteSheets.ElementAt(index);
		}

		// obtain a sprite sheet based on its name
		public SpriteSheet getSpriteSheet(string name) {
			if(name == null) { return null; }
			string temp = name.Trim();
			if(temp.Length == 0) { return null; }

			for(int i=0;i<m_spriteSheets.Count();i++) {
				if(m_spriteSheets.ElementAt(i).name != null &&
				   m_spriteSheets.ElementAt(i).name.Equals(temp, StringComparison.OrdinalIgnoreCase)) {
					return m_spriteSheets.ElementAt(i);
				}
			}
			return null;
		}

		// obtain the index of a sprite sheet based on its name
		public int getSpriteSheetIndex(string name) {
			if(name == null) { return -1; }
			string temp = name.Trim();
			if(temp.Length == 0) { return -1; }

			for(int i=0;i<m_spriteSheets.Count();i++) {
				if(m_spriteSheets.ElementAt(i).name != null &&
				   m_spriteSheets.ElementAt(i).name.Equals(temp, StringComparison.OrdinalIgnoreCase)) {
					return i;
				}
			}
			return -1;
		}

		// obtain the first sprite with a matching name from amy sprite sheet
		// within the collection of sprite sheets
		public Sprite getSprite(String name) {
			if(name == null) { return null; }
			string temp = name.Trim();
			if(temp.Length == 0) { return null; }

			for(int i=0;i<m_spriteSheets.Count();i++) {
				for(int j=0;j<m_spriteSheets.ElementAt(i).size();j++) {
					if(m_spriteSheets.ElementAt(i).getSprite(i).name!= null &&
					   temp.Equals(m_spriteSheets.ElementAt(i).getSprite(j).name)) {
						return m_spriteSheets.ElementAt(i).getSprite(j);
					}
				}
			}
			return null;
		}

		// add a sprite sheet to the collection of sprite sheets
		public bool addSpriteSheet(SpriteSheet spriteSheet) {
			if(spriteSheet == null) { return false; }

			if(!m_spriteSheets.Contains(spriteSheet)) {
				m_spriteSheets.Add(spriteSheet);
				return true;
			}
			return false;
		}

		// parse a collection of sprite sheets from a specified sprite sheet data file
		public static SpriteSheetCollection parseFrom(String fileName, ContentManager content) {
			if(fileName == null || !File.Exists(fileName)) { return null; }
			
			StreamReader instream;
			SpriteSheet spriteSheet;
			SpriteSheetCollection spriteSheets = new SpriteSheetCollection();

			// open the sprite sheet data file and parse until either:
			// an invalid sprite sheet is encountered
			// or the end of the file is encountered
			try {
				instream = File.OpenText(fileName);
				
				do {
					// parse the sprite sheet and store it
					spriteSheet = SpriteSheet.parseFrom(instream, content);
					spriteSheets.addSpriteSheet(spriteSheet);
				} while(spriteSheet != null);
				
				instream.Close();
			}
			catch(Exception) { return null; }
			
			return spriteSheets;
		}

	}

}
