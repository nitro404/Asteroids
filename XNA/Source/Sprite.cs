using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;

namespace Asteroids {

	enum SpriteType { Unknown = -1, Sheet, SpaceShip, Asteroid, Laser, Bomb, Explosion }

	class Sprite {

		private Texture2D m_image = null;
		private Rectangle m_source;
		private Vector2 m_offset;
		private Rectangle m_destination;

		string m_name = null;
		private SpriteType m_type;
		string m_parentName = null;
		int m_index = -1;

		// constructor to load a sprite from a specified file
		public Sprite(string fileName, ContentManager content) {
			if(fileName != null && content != null) {
				try {
					m_image = content.Load<Texture2D>(fileName);
					m_source = new Rectangle(0, 0, m_image.Width, m_image.Height);
					m_offset = new Vector2(m_source.Width / 2.0f, m_source.Height / 2.0f);
					m_destination = new Rectangle(0, 0, m_source.Width, m_source.Height);
				}
				catch(Exception) { }
			}
		}

		// constructor to create a sprite from a specified region of an already existing sprite
		public Sprite(Sprite sprite, Rectangle source) {
			if(sprite != null && sprite.m_image != null &&
			   source.X >= 0 && source.Y >= 0 &&
			   source.Width >= 0 && source.Height >= 0) {
				m_image = sprite.m_image;
				m_source = source;
				m_offset = new Vector2(m_source.Width / 2.0f, m_source.Height / 2.0f);
				m_destination = new Rectangle(0, 0, m_source.Width + 1, m_source.Height + 1);
			}
		}

		public Texture2D image { get { return m_image; } }

		public Rectangle source { get { return m_source; } }

		public int x { get { return m_source.X; } }

		public int y { get { return m_source.Y; } }

		public int width { get { return m_source.Width; } }

		public int height { get { return m_source.Height; } }

		public int xOffset { get { return (int) m_offset.X; } }

		public int yOffset { get { return (int) m_offset.Y; } }

		public string name {
			get { return m_name; }
			set { m_name = value; }
		}

		public SpriteType type {
			get { return m_type; }
			set { m_type = value; }
		}

		public string parentName {
			get { return m_parentName; }
			set { m_parentName = value; }
		}

		public int index {
			get { return m_index; }
			set { m_index = (index < -1) ? -1 : value; }
		}

		// parse a sprite type from a string
		public static SpriteType parseType(String data) {
			if(data == null) { return SpriteType.Unknown; }
			string temp = data.Trim();
			
			if(temp.Equals("SpriteSheet", StringComparison.OrdinalIgnoreCase)) {
				return SpriteType.Sheet;
			}
			else if(temp.Equals("SpaceShip", StringComparison.OrdinalIgnoreCase)) {
				return SpriteType.SpaceShip;
			}
			else if(temp.Equals("Asteroid", StringComparison.OrdinalIgnoreCase)) {
				return SpriteType.Asteroid;
			}
			else if(temp.Equals("Laser", StringComparison.OrdinalIgnoreCase)) {
				return SpriteType.Laser;
			}
			else if(temp.Equals("Bomb", StringComparison.OrdinalIgnoreCase)) {
				return SpriteType.Bomb;
			}
			else if(temp.Equals("Explosion", StringComparison.OrdinalIgnoreCase)) {
				return SpriteType.Explosion;
			}
			return SpriteType.Unknown;
		}

		public void draw(SpriteBatch spriteBatch, Vector2 scale, float rotationDegrees, Vector2 position, SpriteEffects effect) {
			if(m_image == null || spriteBatch == null) { return; }
			
			// update the destination rectangle
			m_destination.X = (int) position.X;
			m_destination.Y = (int) position.Y;
			m_destination.Width = (m_source.Width + 1) * (int) scale.X;
			m_destination.Height = (m_source.Height + 1) * (int) scale.Y;

			// draw the sprite
			spriteBatch.Draw(m_image, m_destination, m_source, Color.White, MathHelper.ToRadians(rotationDegrees), m_offset, effect, 0);
		}

	}

}
