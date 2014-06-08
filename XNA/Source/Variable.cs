using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Asteroids {

	class Variable {

		public const int NO_CATEGORY = -1;
		private const char SEPARATOR_CHAR = '=';

		private int m_category = NO_CATEGORY; // refers to the index in the list of string categories in its parent variable system
		private string m_id = null;
		private string m_value = null;

		// default constructor
		public Variable() : this("", "", NO_CATEGORY) { }

		// create a variable with no category
		public Variable(string id, string value) : this(id, value, NO_CATEGORY) { }

		// create a variable with a specific category
		public Variable(string id, string value, int category) {
			m_category = (category < -1) ? NO_CATEGORY : category;
			m_id = (id == null) ? "" : id;
			m_value = (value == null) ? "" : value;
		}

		public int category {
			get { return m_category; }
			set { m_category = (value < -1) ? NO_CATEGORY : value; }
		}

		public string id {
			get { return m_id; }
			set { m_id = (value == null) ? "" : value; }
		}

		public string value {
			get { return m_value; }
			set { m_value = (value == null) ? "" : value; }
		}

		public void removeCategory() {
			m_category = NO_CATEGORY;
		}

		// parse a variable from a string
		public static Variable parseFrom(string data) {
			if(data == null) { return null; }
			string temp = data.Trim();
			if(temp.Length < 1) { return null; }

			int separatorIndex = temp.IndexOf(SEPARATOR_CHAR);
			if(separatorIndex == -1) { return null; }
			string id = temp.Substring(0, separatorIndex);
			string value = temp.Substring(separatorIndex + 1, temp.Length - separatorIndex - 1);

			return new Variable(id, value, NO_CATEGORY);
		}

		// print a variable to an output stream
		public bool writeTo(StreamWriter output) {
			if(output == null) { return false; }
			output.Write(m_id);
			output.Write(SEPARATOR_CHAR);
			output.Write(m_value);
			return true;
		}

		public override int GetHashCode() {
			return base.GetHashCode();
		}

		public override bool Equals(object o) {
			Variable v = o as Variable;
			if(v == null) { return false; }
			return m_id.Equals(v.m_id, StringComparison.OrdinalIgnoreCase) &&
				   m_category == v.m_category;
		}

		public override string ToString() {
			return string.Format("{0}={1}", m_id, m_value);
		}

	}

}
