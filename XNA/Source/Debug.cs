using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Asteroids {

	// note: class must be initialized before it can be used
	//
	// this class is only used for debugging, and was used specifically for
	// debugging collision detection in this game with its simple ability to
	// render 2d primitives on the fly
	class Debug {

		private static BasicEffect m_effect;
		private static Matrix m_projectionMatrix;
		private static VertexDeclaration m_vertexDeclaration;

		private static VertexPositionColor[] m_pointVertex;
		private static VertexPositionColor[] m_lineVerticies;
		private static VertexPositionColor[] m_rectangleVerticies;
		private static VertexPositionColor[] m_emptyCircleVerticies;
		private static VertexPositionColor[] m_circleVerticies;

		private static GraphicsDeviceManager m_graphics = null;
		private static bool m_initialized = false;
		private static Color m_defaultColour;

		public static void drawPoint(int x, int y) {
			drawPoint(new Vector2(x, y), m_defaultColour);
		}

		public static void drawPoint(Vector2 position) {
			drawPoint(position, m_defaultColour);
		}

		public static void drawPoint(int x, int y, Color colour) {
			drawPoint(new Vector2(x, y), colour);
		}

		public static void drawPoint(Vector2 position, Color colour) {
			if(!m_initialized) { return; }

			m_pointVertex[0].Position.X = position.X;
			m_pointVertex[0].Position.Y = position.Y;
			m_pointVertex[0].Color = colour;

			m_effect.Begin();
			foreach(EffectPass p in m_effect.CurrentTechnique.Passes) {
				p.Begin();
				m_graphics.GraphicsDevice.DrawUserPrimitives<VertexPositionColor>(PrimitiveType.PointList, m_pointVertex, 0, 1);
				p.End();
			}
			m_effect.End();
		}

		public static void drawLine(int x1, int y1, int x2, int y2) {
			drawLine(new Vector2(x1, y1), new Vector2(x2, y2), m_defaultColour);
		}

		public static void drawLine(Vector2 a, Vector2 b) {
			drawLine(a, b, m_defaultColour);
		}

		public static void drawLine(int x1, int y1, int x2, int y2, Color colour) {
			drawLine(new Vector2(x1, y1), new Vector2(x2, y2), colour);
		}

		public static void drawLine(Vector2 a, Vector2 b, Color colour) {
			if(!m_initialized) { return; }

			m_lineVerticies[0].Position.X = a.X;
			m_lineVerticies[0].Position.Y = a.Y;
			m_lineVerticies[0].Color = colour;

			m_lineVerticies[1].Position.X = b.X;
			m_lineVerticies[1].Position.Y = b.Y;
			m_lineVerticies[1].Color = colour;

			m_effect.Begin();
			foreach(EffectPass p in m_effect.CurrentTechnique.Passes) {
				p.Begin();
				m_graphics.GraphicsDevice.DrawUserPrimitives<VertexPositionColor>(PrimitiveType.LineList, m_lineVerticies, 0, 1);
				p.End();
			}
			m_effect.End();
		}

		public static void drawEmptyRectangle(Rectangle r) {
			drawEmptyRectangle(r, m_defaultColour);
		}

		public static void drawEmptyRectangle(Rectangle r, Color colour) {
			if(!m_initialized) { return; }

			m_rectangleVerticies[0].Position.X = r.X;
			m_rectangleVerticies[0].Position.Y = r.Y;
			m_rectangleVerticies[0].Color = colour;

			m_rectangleVerticies[1].Position.X = r.X + r.Width;
			m_rectangleVerticies[1].Position.Y = r.Y;
			m_rectangleVerticies[1].Color = colour;

			m_rectangleVerticies[2].Position.X = r.X + r.Width;
			m_rectangleVerticies[2].Position.Y = r.Y + r.Height;
			m_rectangleVerticies[2].Color = colour;

			m_rectangleVerticies[3].Position.X = r.X;
			m_rectangleVerticies[3].Position.Y = r.Y + r.Height;
			m_rectangleVerticies[3].Color = colour;

			m_rectangleVerticies[4].Position.X = r.X;
			m_rectangleVerticies[4].Position.Y = r.Y;
			m_rectangleVerticies[4].Color = colour;

			m_effect.Begin();
			foreach(EffectPass p in m_effect.CurrentTechnique.Passes) {
				p.Begin();
				m_graphics.GraphicsDevice.DrawUserPrimitives<VertexPositionColor>(PrimitiveType.LineStrip, m_rectangleVerticies, 0, 4);
				p.End();
			}
			m_effect.End();
		}


		public static void drawRectangle(Rectangle r) {
			drawRectangle(r, m_defaultColour);
		}

		public static void drawRectangle(Rectangle r, Color colour) {
			if(!m_initialized) { return; }

			m_rectangleVerticies[0].Position.X = r.X;
			m_rectangleVerticies[0].Position.Y = r.Y;
			m_rectangleVerticies[0].Color = colour;

			m_rectangleVerticies[1].Position.X = r.X + r.Width;
			m_rectangleVerticies[1].Position.Y = r.Y;
			m_rectangleVerticies[1].Color = colour;

			m_rectangleVerticies[2].Position.X = r.X + r.Width;
			m_rectangleVerticies[2].Position.Y = r.Y + r.Height;
			m_rectangleVerticies[2].Color = colour;

			m_rectangleVerticies[3].Position.X = r.X;
			m_rectangleVerticies[3].Position.Y = r.Y + r.Height;
			m_rectangleVerticies[3].Color = colour;

			m_rectangleVerticies[4].Position.X = r.X;
			m_rectangleVerticies[4].Position.Y = r.Y;
			m_rectangleVerticies[4].Color = colour;

			m_effect.Begin();
			foreach(EffectPass p in m_effect.CurrentTechnique.Passes) {
				p.Begin();
				m_graphics.GraphicsDevice.DrawUserPrimitives<VertexPositionColor>(PrimitiveType.TriangleStrip, m_rectangleVerticies, 0, 3);
				p.End();
			}
			m_effect.End();
		}

		public static void drawEmptyCircle(int x, int y, float radius) {
			drawEmptyCircle(new Vector2(x, y), radius, m_defaultColour);
		}

		public static void drawEmptyCircle(Vector2 position, float radius) {
			drawEmptyCircle(position, radius, m_defaultColour);
		}

		public static void drawEmptyCircle(int x, int y, float radius, Color colour) {
			drawEmptyCircle(new Vector2(x, y), radius, colour);
		}

		public static void drawEmptyCircle(Vector2 position, float radius, Color colour) {
			if(!m_initialized) { return; }

			float c = 16.0f;
			float a = 0.0f;
			float inc = 360.0f / c;

			for(int i=0;i<m_emptyCircleVerticies.Length;i++) {
				a += inc;
				m_emptyCircleVerticies[i].Position.X = (float)(position.X - (Math.Sin(MathHelper.ToRadians(a)) * radius));
				m_emptyCircleVerticies[i].Position.Y = (float)(position.Y - (Math.Cos(MathHelper.ToRadians(a)) * radius));
				m_emptyCircleVerticies[i].Color = colour;
			}

			m_effect.Begin();
			foreach(EffectPass p in m_effect.CurrentTechnique.Passes) {
				p.Begin();
				m_graphics.GraphicsDevice.DrawUserPrimitives<VertexPositionColor>(PrimitiveType.LineStrip, m_emptyCircleVerticies, 0, m_emptyCircleVerticies.Length - 1);
				p.End();
			}
			m_effect.End();
		}

		public static void drawCircle(int x, int y, float radius) {
			drawCircle(new Vector2(x, y), radius, m_defaultColour);
		}

		public static void drawCircle(Vector2 position, float radius) {
			drawCircle(position, radius, m_defaultColour);
		}

		public static void drawCircle(int x, int y, float radius, Color colour) {
			drawCircle(new Vector2(x, y), radius, colour);
		}

		public static void drawCircle(Vector2 position, float radius, Color colour) {
			if(!m_initialized) { return; }

			float c = 16.0f;
			float a = 0.0f;
			float inc = 360.0f / c;

			m_circleVerticies[0].Position.X = position.X;
			m_circleVerticies[0].Position.Y = position.Y;
			m_circleVerticies[0].Color = colour;

			for(int i=1;i<m_circleVerticies.Length;i++) {
				a -= inc;
				m_circleVerticies[i].Position.X = (float) (position.X - (Math.Sin(MathHelper.ToRadians(a)) * radius));
				m_circleVerticies[i].Position.Y = (float) (position.Y - (Math.Cos(MathHelper.ToRadians(a)) * radius));
				m_circleVerticies[i].Color = colour;
			}

			m_effect.Begin();
			foreach(EffectPass p in m_effect.CurrentTechnique.Passes) {
				p.Begin();
				m_graphics.GraphicsDevice.DrawUserPrimitives<VertexPositionColor>(PrimitiveType.TriangleFan, m_circleVerticies, 0, m_circleVerticies.Length - 2);
				p.End();
			}
			m_effect.End();
		}

		public static void test() {
			if(!m_initialized) { return; }

			Debug.drawPoint(10, 10, Color.Aqua);
			Debug.drawPoint(10, 12);
			Debug.drawPoint(12, 12, Color.Red);

			Debug.drawLine(14, 14, 16, 22, Color.Yellow);

			Debug.drawEmptyRectangle(new Rectangle(34, 16, 8, 10), Color.White);
			Debug.drawRectangle(new Rectangle(22, 16, 8, 10), Color.Violet);

			Debug.drawEmptyCircle(34, 44, 15, Color.Red);
			Debug.drawCircle(34, 78, 15, Color.Orange);
		}

		public static void initialize(GraphicsDeviceManager graphics) {
			m_graphics = graphics;
			if(graphics == null) { return; }

			m_defaultColour = new Color(0, 255, 0);

			m_effect = new BasicEffect(graphics.GraphicsDevice, null);
			m_vertexDeclaration = new VertexDeclaration(graphics.GraphicsDevice, VertexPositionColor.VertexElements);
			graphics.GraphicsDevice.VertexDeclaration = m_vertexDeclaration;

			Viewport viewport = graphics.GraphicsDevice.Viewport;
			m_projectionMatrix = Matrix.CreateOrthographicOffCenter(0, viewport.Width, viewport.Height, 0, 0, 1.0f);

			m_effect.World = Matrix.Identity;
			m_effect.View = Matrix.Identity;
			m_effect.Projection = m_projectionMatrix;
			m_effect.VertexColorEnabled = true;

			m_pointVertex = new VertexPositionColor[1];
			m_pointVertex[0] = new VertexPositionColor(new Vector3(0, 0, 0), m_defaultColour);

			m_lineVerticies = new VertexPositionColor[2];
			for(int i=0;i<m_lineVerticies.Length;i++) {
				m_lineVerticies[i] = new VertexPositionColor(new Vector3(0, 0, 0), m_defaultColour);
			}

			m_rectangleVerticies = new VertexPositionColor[5];
			for(int i=0;i<m_rectangleVerticies.Length;i++) {
				m_rectangleVerticies[i] = new VertexPositionColor(new Vector3(0, 0, 0), m_defaultColour);
			}

			m_emptyCircleVerticies = new VertexPositionColor[17];
			for(int i=0;i<m_emptyCircleVerticies.Length;i++) {
				m_emptyCircleVerticies[i] = new VertexPositionColor(new Vector3(0, 0, 0), m_defaultColour);
			}

			m_circleVerticies = new VertexPositionColor[18];
			for(int i=0;i<m_circleVerticies.Length;i++) {
				m_circleVerticies[i] = new VertexPositionColor(new Vector3(0, 0, 0), m_defaultColour);
			}

			m_initialized = true;
		}

	}

}
