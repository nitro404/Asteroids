using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Content;

namespace Asteroids {

	enum RotationDirection { Clockwise, CounterClockwise, None }

	enum ScaleDirection { Smaller, Larger, None }

	class GameObject {

		protected Sprite m_sprite;
		
		protected Vector2 m_position;
		protected Vector2 m_initialPosition;
		protected Vector2 m_offset;
		protected Vector2 m_velocity;
		protected Vector2 m_initialVelocity;
		protected float m_maximumVelocity;
		protected float m_acceleration;
		protected float m_initialAcceleration;
		protected float m_maximumAcceleration;

		protected float m_rotation;
		protected float m_initialRotation;
		protected float m_rotationSpeed;
		protected float m_initialRotationSpeed;
		protected float m_maximumRotationSpeed;
		protected RotationDirection m_rotationDirection;
		protected RotationDirection m_initialRotationDirection;

		protected Vector2 m_size;
		protected Vector2 m_scale;
		protected Vector2 m_initialScale;
		protected float m_scaleSpeed;
		protected float m_initialScaleSpeed;

		protected ScaleDirection m_scaleDirection;
		protected ScaleDirection m_initialScaleDirection;

		public GameObject() {
			m_sprite = null;

			m_position = new Vector2(0, 0);
			m_offset = new Vector2(0, 0);
			m_velocity = new Vector2(0, 0);
			m_maximumVelocity = 1;
			m_acceleration = 0;
			m_maximumAcceleration = 1;

			m_rotation = 0;
			m_rotationSpeed = 0;
			m_maximumRotationSpeed = 1;
			m_rotationDirection = RotationDirection.None;

			m_size = new Vector2(0, 0);
			m_scale = new Vector2(1, 1);
			m_scaleSpeed = 0;
			m_scaleDirection = ScaleDirection.None;

			updateInitialValues();
		}

		public Sprite sprite {
			get { return m_sprite; }
			set { m_sprite = value; }
		}

		public string name {
			get { return (m_sprite == null) ? null : m_sprite.name; }
		}

		public int x {
			get { return (int) (m_position.X); }
		}

		public int y {
			get { return (int) (m_position.Y); }
		}

		public Vector2 position {
			get { return m_position; }
			set { if(value != null) { m_position = new Vector2(value.X, value.Y); } }
		}

		public Vector2 initialPosition {
			get { return m_initialPosition;  }
			set { if(value != null) { m_initialPosition = value; } }
		}

		public Vector2 offset {
			get { return m_offset; }
		}

		public Vector2 velocity {
			get { return m_velocity; }
			set { if(value != null) { m_velocity = new Vector2(value.X, value.Y); } }
		}

		public Vector2 initialVelocity {
			get { return m_initialVelocity; }
			set { if(value != null) { m_initialVelocity = value; } }
		}

		public float maximumVelocity {
			get { return m_maximumVelocity; }
			set { m_maximumVelocity = value; }
		}

		public float acceleration {
			get { return m_acceleration; }
			set { m_acceleration = value; }
		}

		public float initialAcceleration {
			get { return m_initialAcceleration; }
			set { m_initialAcceleration = value; }
		}

		public float maximumAcceleration {
			get { return m_maximumAcceleration; }
			set { m_maximumAcceleration = value; }
		}

		public float speed {
			get { return (float) Math.Sqrt(Math.Pow(m_velocity.X, 2) + Math.Pow(m_velocity.Y, 2)); }
		}

		public float rotation {
			get { return m_rotation; }
			set { m_rotation = value; }
		}

		public float initialRotation {
			get { return m_initialRotation; }
			set { m_initialRotation = value; }
		}

		public float rotationSpeed {
			get { return m_rotationSpeed; }
			set { m_rotationSpeed = value; }
		}

		public float initialRotationSpeed {
			get { return m_initialRotationSpeed; }
			set { m_initialRotationSpeed = value; }
		}

		public float maximumRotationSpeed {
			get { return m_maximumRotationSpeed; }
			set { m_maximumRotationSpeed = value; }
		}

		public RotationDirection rotationDirection {
			get { return m_rotationDirection; }
			set { m_rotationDirection = value; }
		}

		public RotationDirection initialRotationDirection {
			get { return m_initialRotationDirection; }
			set { m_initialRotationDirection = value; }
		}

		public Vector2 size {
			get { return m_size; }
			set { if(value.X >= 0 && value.Y >= 0) { m_size = value; } }
		}

		public Vector2 scale {
			get { return m_scale; }
			set { if(value != null) { m_scale = new Vector2(value.X, value.Y); } }
		}

		public Vector2 initialScale {
			get { return m_initialScale; }
			set { if(value != null) { m_initialScale = value; } }
		}

		public float scaleSpeed {
			get { return m_scaleSpeed; }
			set { m_scaleSpeed = value; }
		}

		public float initialScaleSpeed {
			get { return m_initialScaleSpeed; }
			set { m_initialScaleSpeed = value; }
		}

		public ScaleDirection scaleDirection {
			get { return m_scaleDirection; }
			set { m_scaleDirection = value; }
		}

		public ScaleDirection initialScaleDirection {
			get { return m_initialScaleDirection; }
			set { m_initialScaleDirection = value; }
		}

		// change what the values are restored to on a reset
		public virtual void updateInitialValues() {
			m_initialPosition = new Vector2(m_position.X, m_position.Y);
			m_initialVelocity = new Vector2(m_velocity.X, m_velocity.Y);
			m_initialAcceleration = m_acceleration;
			m_initialRotation = m_rotation;
			m_initialRotationSpeed = m_rotationSpeed;
			m_initialRotationDirection = m_rotationDirection;
			m_initialScale = new Vector2(m_scale.X, m_scale.Y);
			m_initialScaleSpeed = m_scaleSpeed;
			m_initialScaleDirection = m_scaleDirection;
		}

		public virtual void update(GameTime gameTime) { }

		public virtual void handleInput(GameTime gameTime) { }

		// reset the object to its original state
		public virtual void reset() {
			m_position = new Vector2(m_initialPosition.X, m_initialPosition.Y);
			m_velocity = new Vector2(m_initialVelocity.X, m_initialVelocity.Y);
			m_acceleration = m_initialAcceleration;
			m_rotation = m_initialRotation;
			m_rotationSpeed = m_initialRotationSpeed;
			m_rotationDirection = m_initialRotationDirection;
			m_scale = new Vector2(m_initialScale.X, m_initialScale.Y);
			m_scaleSpeed = m_initialScaleSpeed;
			m_scaleDirection = m_initialScaleDirection;
		}

		public virtual void draw(SpriteBatch spriteBatch) {
			if(m_sprite == null) { return; }

			m_sprite.draw(spriteBatch, m_scale, m_rotation, m_position, SpriteEffects.None);
		}

		public virtual bool checkCollision(GameObject o) { return false; }
	}

}
