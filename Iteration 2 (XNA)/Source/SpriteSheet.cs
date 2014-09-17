using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;

namespace Asteroids {

	enum SpriteSheetType { Invalid = -1, ArbitraryOffsets, SingleGrid, MultipleGrids }

	enum Axis { Vertical, Horizontal }

	class SpriteSheet {

		private string m_name = null;
		private Sprite m_spriteSheet = null;
		private List<Sprite> m_sprites = null;

		public SpriteSheet() {
			m_sprites = new List<Sprite>();
		}

		// constructor for creating a sprite sheet from a collection of arbitrary offsets
		public SpriteSheet(Sprite externalSpriteSheet, Rectangle[] offsets) {
			m_spriteSheet = externalSpriteSheet;
			m_sprites = new List<Sprite>();
			if(m_spriteSheet != null) {
				for(int i=0;i<offsets.Length;i++) {
					m_sprites.Add(new Sprite(externalSpriteSheet, offsets[i]));
				}
			}
		}

		// constructor for creating a sprite sheet from a grid based specification
		public SpriteSheet(Sprite externalSpriteSheet, Rectangle grid, Axis direction, int rows, int columns) {
			if(externalSpriteSheet == null) { return; }

			m_spriteSheet = externalSpriteSheet;
			m_sprites = new List<Sprite>();

			int x = grid.X;
			int y = grid.Y;
			for(int i=0;i<rows;i++) {
				for(int j=0;j<columns;j++) {
					m_sprites.Add(new Sprite(externalSpriteSheet, new Rectangle(x, y, grid.Width, grid.Height)));
					if(direction == Axis.Horizontal) { x += grid.Width + 2; }
					else { y += grid.Height + 2; }
				}
				if(direction == Axis.Horizontal) { y += grid.Height + 2; x = grid.X; }
				else { x += grid.Width + 2; y = grid.Y;  }
			}
		}

		public string name {
			get { return m_name; }
			set { m_name = value; }
		}

		public Sprite image {
			get { return m_spriteSheet; }
			set { m_spriteSheet = value; }
		}

		public int size() {
			return m_sprites.Count();
		}

		public Sprite getSprite(int index) {
			return (index < 0 || index >= m_sprites.Count()) ? null : m_sprites.ElementAt(index);
		}

		// return a sprite from a sprite sheet based on its name
		public Sprite getSprite(string name) {
			if(name == null) { return null; }
			for(int i=0;i<m_sprites.Count();i++) {
				if(name.Equals(m_sprites.ElementAt(i).name, StringComparison.OrdinalIgnoreCase)) {
					return m_sprites.ElementAt(i);
				}
			}
			return null;
		}

		// add a sprite to the sprite sheet (if it is not a duplicate)
		public bool addSprite(Sprite sprite) {
			if(sprite == null) { return false; }
			if(!m_sprites.Contains(sprite)) {
				m_sprites.Add(sprite);
			}
			return true;
		}

		// obtain a sub-list of sprites within a specified range
		public List<Sprite> getSprites(int startIndex, int endIndex) {
			if(startIndex < 0) { startIndex = 0; }
			if(endIndex >= m_sprites.Count()) { endIndex = m_sprites.Count() - 1; }

			// add the sprites within the specified range to a list and return it
			List<Sprite> spriteGroup = new List<Sprite>();
			for(int i=startIndex;i<=endIndex;i++) {
				spriteGroup.Add(m_sprites.ElementAt(i));
			}
			return spriteGroup;
		}

		// parse a sprite sheet type from a given string
		public static SpriteSheetType parseType(string data) {
			if(data == null) { return SpriteSheetType.Invalid; }
			string temp = data.Trim();

			if(temp.Equals("Arbitrary Offsets", StringComparison.OrdinalIgnoreCase)) {
				return SpriteSheetType.ArbitraryOffsets;
			}
			else if(temp.Equals("Single Grid", StringComparison.OrdinalIgnoreCase)) {
				return SpriteSheetType.SingleGrid;
			}
			else if(temp.Equals("Multiple Grids", StringComparison.OrdinalIgnoreCase)) {
				return SpriteSheetType.MultipleGrids;
			}
			return SpriteSheetType.Invalid;
		}

		// parse an axis from a given string
		public static Axis parseAxis(string data) {
			return (data != null && data.Trim().Equals("Horizontal", StringComparison.OrdinalIgnoreCase)) ? Axis.Horizontal : Axis.Vertical;
		}

		// parse and create a sprite sheet from a text file input stream
		public static SpriteSheet parseFrom(StreamReader instream, ContentManager content) {
			if(instream == null || content == null) { return null; }

			string input = null;
			string data = null;

			Variable v;
			VariableSystem properties = new VariableSystem();
			string spriteSheetName, spriteSheetFileName = null;
			SpriteSheetType spriteSheetType = SpriteSheetType.Invalid;
			Sprite spriteSheetImage = null;
			SpriteSheet spriteSheet = null;

			try {
				while((input = instream.ReadLine()) != null) {
					// trim the current line being read
					data = input.Trim();

					// if the line is blank, discard it
					if(data.Length == 0) {
						continue;
					}
					// otherwise, if it contains information
					else {
						// attempt to parse a variable from the data and store it
						v = Variable.parseFrom(data);

						// if successful, store it
						if(v != null) {
							properties.add(v);
						}

						// if the variable is a specification of the number of sprites or
						// the number of grids to be parsed, begin doing so
						if(v != null && (v.id.Equals("Number of Sprites", StringComparison.OrdinalIgnoreCase) ||
						   v.id.Equals("Number of Grids", StringComparison.OrdinalIgnoreCase))) {

							// get the sprite sheet name and verify it exists
							spriteSheetName = properties.getValue("SpriteSheet Name");
							if(spriteSheetName == null) { return null; }

							// parse the sprite sheet type and ensure it is valid
							spriteSheetType = parseType(properties.getValue("SpriteSheet Type"));
							if(spriteSheetType == SpriteSheetType.Invalid) { return null; }

							// get the sprite sheet file name
							spriteSheetFileName = properties.getValue("File Name");
							if(spriteSheetFileName == null) { return null; }

							// load the sprite to be parsed by the sprite sheet system
							spriteSheetImage = new Sprite(spriteSheetFileName, content);
							spriteSheetImage.type = SpriteType.Sheet;

							// ===============================================================================
							// Arbitrary Offset SpriteSheet ==================================================
							// ===============================================================================
							if(spriteSheetType == SpriteSheetType.ArbitraryOffsets) {
								VariableSystem spriteAttributes = new VariableSystem();
								int numberOfSprites;

								// verify that the number of sprites is valid
								try { numberOfSprites = int.Parse(v.value); }
								catch(Exception) { return null; }
								if(numberOfSprites <= 0) { return null; }

								int spriteIndex;
								string spriteName, spriteType;
								Rectangle grid;
								Rectangle[] offsets = new Rectangle[numberOfSprites];
								string[] spriteNames = new string[numberOfSprites];
								SpriteType[] spriteTypes = new SpriteType[numberOfSprites];
								for(int i=0;i<numberOfSprites;i++) {
									spriteNames[i] = null;
									spriteTypes[i] = SpriteType.Unknown;
									offsets[i] = new Rectangle(0, 0, 0, 0);
								}
								// loop through and collect the attributes for each sprite
								for(int i=0;i<numberOfSprites;i++) {
									spriteAttributes.clear();
									// get the 5 sprite attributes (index, name, type, offset, size)
									for(int j=0;j<5;j++) {
										spriteAttributes.add(Variable.parseFrom(instream.ReadLine()));
									}
									
									// store the sprite index value and validate it
									try { spriteIndex = int.Parse(spriteAttributes.getValue("Sprite")); }
									catch(Exception) { return null; }
									if(spriteIndex < 0 || spriteIndex >= numberOfSprites) { return null; } 
									
									// get the sprite name
									spriteName = spriteAttributes.getValue("Name");
									if(spriteName == null) { return null; }
									
									// get the sprite type (as a string)
									spriteType = spriteAttributes.getValue("Type");
									if(spriteType == null) { return null; }
									
									// parse the sprite's offset in its parent sprite sheet
									string temp = spriteAttributes.getValue("Offset");
									if(temp == null) { return null; }
									string[] offsetValues = temp.Split(',');
									if(offsetValues.Length != 2) { return null; }

									// parse the size of the sprite
									temp = spriteAttributes.getValue("Size");
									if(temp == null) { return null; }
									string[] sizeValues = temp.Split(',');
									if(sizeValues.Length != 2) { return null; }

									// attempt to create a source grid based off of these specifications
									try { grid = new Rectangle(int.Parse(offsetValues[0]),
															   int.Parse(offsetValues[1]),
															   int.Parse(sizeValues[0]),
															   int.Parse(sizeValues[1])); }
									catch(Exception) { return null; }
									
									// assign the values for temporary storage
									spriteNames[spriteIndex] = spriteName;
									spriteTypes[spriteIndex] = Sprite.parseType(spriteType);
									offsets[spriteIndex] = new Rectangle(grid.X, grid.Y, grid.Width, grid.Height);
								}

								// once the attributes and offsets for all of the sprites have been collected, create the sprite sheet
								spriteSheet = new SpriteSheet(spriteSheetImage, offsets);
								spriteSheet.name = spriteSheetName;

								// loop through the temporarily stored sprite attributes and assign them to each corresponding sprite
								for(int i=0;i<numberOfSprites;i++) {
									spriteSheet.getSprite(i).name = spriteNames[i];
									spriteSheet.getSprite(i).index = i;
									spriteSheet.getSprite(i).parentName = spriteSheetName;
									spriteSheet.getSprite(i).type = spriteTypes[i];
								}
							}

							// ===============================================================================
							// Single Grid SpriteSheet =======================================================
							// ===============================================================================
							else if(spriteSheetType == SpriteSheetType.SingleGrid) {
								VariableSystem spriteAttributes = new VariableSystem();
								Rectangle grid;
								Axis direction;
								int numberOfRows, numberOfColumns, numberOfSprites;

								// get the number of sprites to obtain attributes for
								try { numberOfSprites = int.Parse(v.value); }
								catch(Exception) { return null; }

								// get the grid offset
								string temp = properties.getValue("Offset");
								if(temp == null) { return null; }
								string[] offsetValues = temp.Split(',');
								if(offsetValues.Length != 2) { return null; }

								// get the size of each cell within the grid
								temp = properties.getValue("Size");
								if(temp == null) { return null; }
								string[] sizeValues = temp.Split(',');
								if(sizeValues.Length != 2) { return null; }

								// convert the offset and cell size to a rectangle
								try { grid = new Rectangle(int.Parse(offsetValues[0]),
														   int.Parse(offsetValues[1]),
														   int.Parse(sizeValues[0]),
														   int.Parse(sizeValues[1])); }
								catch(Exception) { return null; }
								
								// get the direction to parse the sprites in
								direction = parseAxis(properties.getValue("Direction"));

								// get the number of rows in the grid
								try { numberOfRows = int.Parse(properties.getValue("Number of Rows")); }
								catch(Exception) { return null; }
								
								// get the number of columns in the grid
								try { numberOfColumns = int.Parse(properties.getValue("Number of Columns")); }
								catch(Exception) { return null; }
								
								// create the sprite sheet based on the corresponding specifications
								spriteSheet = new SpriteSheet(spriteSheetImage,
															  grid,
															  direction,
															  numberOfRows,
															  numberOfColumns);
								spriteSheet.name = spriteSheetName;
								
								int spriteIndex;
								string spriteName, spriteType;
								// loop through the sprite sheet specifications
								for(int i=0;i<numberOfSprites;i++) {
									// obtain the 3 specifications for the current sprite (index, name, type)
									for(int j=0;j<3;j++) {
										spriteAttributes.add(Variable.parseFrom(instream.ReadLine()));
									}
									
									// get the sprite index and verify it
									try { spriteIndex = int.Parse(spriteAttributes.getValue("Sprite")); }
									catch(Exception) { return null; }
									if(spriteIndex < 0 || spriteIndex >= spriteSheet.size()) { return null; }
									
									// get the sprite name
									spriteName = spriteAttributes.getValue("Name");
									if(spriteName == null) { return null; }
									
									// get the sprite type (as a string)
									spriteType = spriteAttributes.getValue("Type");
									if(spriteType == null) { return null; }
									
									// assign the attributes to the corresponding sprite
									spriteSheet.getSprite(spriteIndex).name = spriteName;
									spriteSheet.getSprite(spriteIndex).index = spriteIndex;
									spriteSheet.getSprite(spriteIndex).parentName = spriteSheetName;
									spriteSheet.getSprite(spriteIndex).type = Sprite.parseType(spriteType);

									// clear the list of attributes presently associated with the current sprite
									spriteAttributes.clear();
								}
							}

							// ===============================================================================
							// Multiple Grids SpriteSheet ====================================================
							// ===============================================================================
							else if(spriteSheetType == SpriteSheetType.MultipleGrids) {
								int numberOfGrids;
								int spriteIndexOffset = 0;
								
								// verify that the number of grids to parse is specified and valid
								try { numberOfGrids = int.Parse(v.value); }
								catch(Exception) { return null; }
								if(numberOfGrids < 1) { return null; }
								
								// create an empty sprite sheet
								spriteSheet = new SpriteSheet();
								spriteSheet.name = spriteSheetName;
								spriteSheet.image = spriteSheetImage;
								
								// temporary storage
								VariableSystem gridAttributes = new VariableSystem();
								int[] numberOfSprites = new int[numberOfGrids];
								Rectangle[] grid = new Rectangle[numberOfGrids];
								Axis[] direction = new Axis[numberOfGrids];
								int[] numberOfRows = new int[numberOfGrids];
								int[] numberOfColumns = new int[numberOfGrids];
								for(int i=0;i<numberOfGrids;i++) {
									numberOfSprites[i] = -1;
									grid[i] = new Rectangle(0, 0, 0, 0);
									direction[i] = Axis.Horizontal;
									numberOfRows[i] = -1;
									numberOfColumns[i] = -1;
								}
								
								// loop through all of the grids
								for(int i=0;i<numberOfGrids;i++) {
									// obtain the 7 attributes for each grid (index, offset, size, parse direction, number of rows, number of columns, number of sprite attributes)
									for(int j=0;j<7;j++) {
										gridAttributes.add(Variable.parseFrom(instream.ReadLine()));
									}
									
									// get the index of the current grid
									int gridIndex;
									try { gridIndex = int.Parse(gridAttributes.getValue("Grid")); }
									catch(Exception) { return null; }
									if(gridIndex < 0 || gridIndex >= numberOfGrids) { return null; }
									
									// get the number of sprites within the current grid and validate it
									try { numberOfSprites[gridIndex] = int.Parse(gridAttributes.getValue("Number of Sprites")); }
									catch(Exception) { return null; }
									
									// get the offset of the current grid
									string temp = gridAttributes.getValue("Offset");
									if(temp == null) { return null; }
									string[] offsetValues = temp.Split(',');
									if(offsetValues.Length != 2) { return null; }
									
									// get the size of each cell within the current grid
									temp = gridAttributes.getValue("Size");
									if(temp == null) { return null; }
									string[] sizeValues = temp.Split(',');
									if(sizeValues.Length != 2) { return null; }

									// create a rectangle representing the first cell in the current grid
									try { grid[gridIndex] = new Rectangle(int.Parse(offsetValues[0]),
																		  int.Parse(offsetValues[1]),
																		  int.Parse(sizeValues[0]),
																		  int.Parse(sizeValues[1])); }
									catch(Exception) { return null; }

									// obtain the direction in which to parse the sprites from the current sprite sheet grid
									direction[gridIndex] = parseAxis(gridAttributes.getValue("Direction"));
									
									// get the number of rows in the current grid
									try { numberOfRows[gridIndex] = int.Parse(gridAttributes.getValue("Number of Rows")); }
									catch(Exception) { return null; }
									
									// get the number of columns in the current grid
									try { numberOfColumns[gridIndex] = int.Parse(gridAttributes.getValue("Number of Columns")); }
									catch(Exception) { return null; }

									// start parsing at the initial offset
									// loop through all of the rows and columns incrementing the x position and y position as appropriate
									// parse each sprite according to the current offset and size and store it in the main sprite collection
									int xPos = grid[gridIndex].X;
									int yPos = grid[gridIndex].Y;
									for(int j=0;j<numberOfRows[gridIndex];j++) {
										for(int k=0;k<numberOfColumns[gridIndex];k++) {
											spriteSheet.addSprite(new Sprite(spriteSheetImage, new Rectangle(xPos, yPos, grid[gridIndex].Width, grid[gridIndex].Height)));
											if(direction[gridIndex] == Axis.Horizontal) { xPos += grid[gridIndex].Width + 2; }
											else { yPos += grid[gridIndex].Height + 2; }
										}
										if(direction[gridIndex] == Axis.Horizontal) { yPos += grid[gridIndex].Height + 2; xPos = grid[gridIndex].X; }
										else { xPos += grid[gridIndex].Width + 2; yPos = grid[gridIndex].Y; }
									}
									
									int spriteIndex;
									string spriteName, spriteType;
									VariableSystem spriteAttributes = new VariableSystem();
									// loop through the sprite attribute specifications for the current grid
									for(int j=0;j<numberOfSprites[gridIndex];j++) {
										// read in the 3 sprite attributes (index, name, type) and store them
										for(int k=0;k<3;k++) {
											spriteAttributes.add(Variable.parseFrom(instream.ReadLine()));
										}
										
										// get the sprite index and validate it
										try { spriteIndex = spriteIndexOffset + int.Parse(spriteAttributes.getValue("Sprite")); }
										catch(Exception) { return null; }
										if(spriteIndex < spriteIndexOffset || spriteIndex >= spriteSheet.size()) {
											return null;
										}
										
										// get the sprite name
										spriteName = spriteAttributes.getValue("Name");
										if(spriteName == null) { return null; }
										
										// get the sprite type
										spriteType = spriteAttributes.getValue("Type");
										if(spriteType == null) { return null; }

										// assign the current set of attributes to the corresponding sprite
										spriteSheet.getSprite(spriteIndex).name = spriteName;
										spriteSheet.getSprite(spriteIndex).index = spriteIndex;
										spriteSheet.getSprite(spriteIndex).parentName = spriteSheetName;
										spriteSheet.getSprite(spriteIndex).type = Sprite.parseType(spriteType);

										// clear the current collection of sprite attributes
										spriteAttributes.clear();
									}
									
									// clear the current collection of grid attributes and update the Sprite index offset (current position in the main SpriteSheet collection)
									gridAttributes.clear();
									spriteIndexOffset = spriteSheet.size();
								}
							}

							// return null if sprite sheet type is invalid
							else {
								return null;
							}

							// return the current sprite sheet
							return spriteSheet;
						}
					}
				}
			}
			catch(Exception) { }

			return null;
		}

	}

}
